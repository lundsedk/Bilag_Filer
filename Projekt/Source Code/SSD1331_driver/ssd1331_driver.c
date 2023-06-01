#include <linux/spi/spi.h> 
#include <linux/platform_device.h>
#include <linux/gpio.h> 
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>

#define MAX_LEN_BUF 10

/* Char Driver Globals */
static struct spi_driver spi_drv_spi_driver;
struct file_operations ssd1331_drv_fops;
static struct class* ssd1331_drv_class;
static dev_t devno;
static struct cdev ss1331_drv_cdev;

/* Definition of SSD1331 device */
struct ssd1331 {
	struct spi_device* spi; // Pointer to SPI device
	int dc_gpio;			// D/C pin
	int rst_gpio;			// Reset pin
};

/* SSD1331 device and minor used for devices */
struct ssd1331 ssd1331_dev;
static int spi_minor = 0;
static int dc_minor = 1;
static int rst_minor = 2;

/* Macro to handle Errors */
#define ERRGOTO(label, ...)                     \
{                                             	\
	printk (__VA_ARGS__);                       \
	goto label;                                 \
} while(0)

/* Function to handle SPI transfer */
int spi_write_message(struct spi_device* spi, char* data, int len)
{
	int err;
	struct spi_transfer t[1]; /* Only one transfer */
	struct spi_message m;

	memset(t, 0, sizeof(t)); /* Init Memory */
	spi_message_init(&m); /* Init Msg */
	m.spi = spi;

	t[0].tx_buf = data; /* Set tx buffer */
	t[0].rx_buf = NULL;
	t[0].len = len; /* Transfer size in bytes */
	spi_message_add_tail(&t[0], &m); /* Add Msg to queue */
	err = spi_sync(m.spi, &m); /* Blocking Transmit */

	return err;
}

/**********************************************************
* CHARACTER DRIVER METHODS
**********************************************************/

/* Character Driver Module Init Method */
static int __init ssd1331_drv_init(void)
{
	int err = 0;

	printk("spi_drv driver initializing\n");

	/* Allocate major number and register fops*/
	err = alloc_chrdev_region(&devno, 0, 255, "spi_drv driver");
	if (MAJOR(devno) <= 0)
		ERRGOTO(err_no_cleanup, "Failed to register chardev\n");
	printk(KERN_ALERT "Assigned major no: %i\n", MAJOR(devno));

	cdev_init(&ss1331_drv_cdev, &ssd1331_drv_fops);
	err = cdev_add(&ss1331_drv_cdev, devno, 255);
	if (err)
		ERRGOTO(err_cleanup_chrdev, "Failed to create class");

	/* Polulate sysfs entries */
	ssd1331_drv_class = class_create(THIS_MODULE, "ssd1331_drv_class");
	if (IS_ERR(ssd1331_drv_class))
		ERRGOTO(err_cleanup_cdev, "Failed to create class\n");

	/* Register SPI Driver */
	err = spi_register_driver(&spi_drv_spi_driver);
	if (err)
		ERRGOTO(err_cleanup_class, "Failed SPI Registration\n");

	return 0;

	/* Errors during Initialization */
err_cleanup_class:
	class_destroy(ssd1331_drv_class);

err_cleanup_cdev:
	cdev_del(&ss1331_drv_cdev);

err_cleanup_chrdev:
	unregister_chrdev_region(devno, 255);

err_no_cleanup:
	return err;
}

/* Character Driver Module Exit Method */
static void __exit ssd1331_drv_exit(void)
{
	printk("spi_drv driver Exit\n");

	spi_unregister_driver(&spi_drv_spi_driver);
	class_destroy(ssd1331_drv_class);
	cdev_del(&ss1331_drv_cdev);
	unregister_chrdev_region(devno, 255);
}

/* Character Driver Write File Operations Method */
ssize_t ssd1331_drv_write(struct file* filep, const char __user* ubuf,
	size_t count, loff_t* f_pos)
{
	int minor = iminor(filep->f_inode);
	int len, value;
	char kbuf[MAX_LEN_BUF];

	printk(KERN_ALERT "Writing to spi_drv [Minor] %i \n", minor);

	if (minor == 0)
	{
		len = count;
		if (len > MAX_LEN_BUF) // If buffer to large for stack allocation
		{
			char* kbufData = kmalloc((sizeof(char) * len), GFP_KERNEL); // Allocate kbuf
			if (copy_from_user(kbufData, ubuf, len))
				return -EFAULT;

			spi_write_message(ssd1331_dev.spi, kbufData, len); // send spi message

			kfree(kbuf); // Deallocate kbuf
		}
		else
		{
			if (copy_from_user(kbuf, ubuf, len))
				return -EFAULT;

			spi_write_message(ssd1331_dev.spi, kbuf, len); // send spi message
		}

	}

	else {
		len = count < MAX_LEN_BUF ? count : MAX_LEN_BUF;
		if (copy_from_user(kbuf, ubuf, len))
			return -EFAULT;

		kbuf[len] = '\0'; // Pad null termination to string
		sscanf(kbuf, "%i", &value); // Convert string to int

		switch (minor) {
		case 1:
			gpio_set_value(ssd1331_dev.dc_gpio, value); // Set gpio-dc
			break;

		case 2:
			gpio_set_value(ssd1331_dev.rst_gpio, value); // Set gpio_reset
			break;

		default:
			break;
		}
	}

	*f_pos += len; // Move it the length actually written for compability

	return len; // return length actually written
}

/* Character Driver File Operations Structure */
struct file_operations ssd1331_drv_fops =
{
  .owner = THIS_MODULE,
  .write = ssd1331_drv_write,
};

/**********************************************************
 * LINUX DEVICE MODEL METHODS (spi)
 **********************************************************/

 /* spi_drv probe - called when a device with the name "spi_drv" is registered. */
static int ssd1331_drv_probe(struct spi_device* sdev)
{
	int err = 0;
	struct device* spi_drv_device;

	printk(KERN_DEBUG "New SPI device: %s using chip select: %i\n", sdev->modalias, sdev->chip_select);

	/* Configure bits_per_word, always 8-bit for RPI!!! */
	sdev->bits_per_word = 8;
	spi_setup(sdev);
	ssd1331_dev.spi = sdev;

	/* Device create for spi */
	spi_drv_device = device_create(ssd1331_drv_class, NULL,
		MKDEV(MAJOR(devno), spi_minor),
		NULL, "spi_drv%d", spi_minor);
	err = IS_ERR(spi_drv_device);
	if (err)
		ERRGOTO(err_no_clean, "Failed to create SPI0 device\n");
	printk(KERN_ALERT "Created spi_drv%i on major:%i, minor:%i\n",
		spi_minor, MAJOR(devno), spi_minor);

	/* Set GPIO numbers for D/C and RESET pin*/
	ssd1331_dev.dc_gpio = 13;
	ssd1331_dev.rst_gpio = 19;

	/* Request gpio for D/C and set direction*/
	err = gpio_request(ssd1331_dev.dc_gpio, "gpio_dc");
	if (err)
		ERRGOTO(err_clean_spi, "Failed gpio request for D/C pin\n");
	printk(KERN_ALERT "D/C requested on gpio%i\n", ssd1331_dev.dc_gpio);
	gpio_direction_output(ssd1331_dev.dc_gpio, 0);

	/* Device create for D/C */
	spi_drv_device = device_create(ssd1331_drv_class, NULL, MKDEV(MAJOR(devno), dc_minor), NULL, "gpio_dc");
	err = IS_ERR(spi_drv_device);
	if (err)
		ERRGOTO(err_free_gpio_dc, "Failed to create device for D/C gpio\n");
	printk(KERN_ALERT "Created gpio_dc on major:%i, minor:%i\n", MAJOR(devno), dc_minor);

	/* Request gpio for RESET and set direction*/
	err = gpio_request(ssd1331_dev.rst_gpio, "gpio_rst");
	if (err)
		ERRGOTO(err_clean_dev_dc, "Failed gpio request for reset pin\n");
	printk(KERN_ALERT "Reset requested on gpio%i\n", ssd1331_dev.rst_gpio);
	gpio_direction_output(ssd1331_dev.rst_gpio, 0); // GPIO direction; 

	/* Device create for RESET */
	spi_drv_device = device_create(ssd1331_drv_class, NULL, MKDEV(MAJOR(devno), rst_minor), NULL, "gpio_rst");
	err = IS_ERR(spi_drv_device);
	if (err)
		ERRGOTO(err_free_gpio_rst, "Failed to create device for reset gpio\n");
	printk(KERN_ALERT "Created gpio_rst on major:%i, minor:%i\n", MAJOR(devno), rst_minor);

	return 0;

	/* Errors during Probe */
err_free_gpio_rst:
	gpio_free(ssd1331_dev.rst_gpio);

err_clean_dev_dc:
	device_destroy(ssd1331_drv_class, MKDEV(MAJOR(devno), dc_minor));

err_free_gpio_dc:
	gpio_free(ssd1331_dev.dc_gpio);

err_clean_spi:
	device_destroy(ssd1331_drv_class, MKDEV(MAJOR(devno), spi_minor));

err_no_clean:
	return err;
}

/* spi_drv remove - called when the device is removed */
static int ssd1331_drv_remove(struct spi_device* sdev)
{
	printk(KERN_ALERT "Removing spi device\n");

	/* Destroy devices created in probe() */
	device_destroy(ssd1331_drv_class, MKDEV(MAJOR(devno), spi_minor));
	device_destroy(ssd1331_drv_class, MKDEV(MAJOR(devno), dc_minor));
	device_destroy(ssd1331_drv_class, MKDEV(MAJOR(devno), rst_minor));
	gpio_free(ssd1331_dev.dc_gpio);
	gpio_free(ssd1331_dev.rst_gpio);

	return 0;
}

/* SPI Driver Struct */
static const struct of_device_id of_spi_drv_spi_device_match[] = {
  {.compatible = "ase, ssd1331_drv", }, {},
};

static struct spi_driver spi_drv_spi_driver = {
	.probe = ssd1331_drv_probe,
	.remove = ssd1331_drv_remove,
	.driver = {
	.name = "ssd1331_drv",
	.bus = &spi_bus_type,
	.of_match_table = of_spi_drv_spi_device_match,
	.owner = THIS_MODULE,
  },
};

/**********************************************************
 * GENERIC LINUX DEVICE DRIVER STUFF
 **********************************************************/

 /* Assignment of module init/exit methods */
module_init(ssd1331_drv_init);
module_exit(ssd1331_drv_exit);

/* Assignment of author and license */
MODULE_AUTHOR("Anette Olesen Lihn");
MODULE_LICENSE("GPL");
