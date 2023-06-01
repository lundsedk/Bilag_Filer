#include <linux/platform_device.h>
#include <linux/gpio.h> 
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/module.h>

//more includes
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/of.h>
#include <linux/delay.h>

//interupt
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/sched.h>


#define IRQF_TRIGGER_NONE 0x00000000
#define IRQF_TRIGGER_RISING 0x00000001
#define IRQF_TRIGGER_FALLING 0x00000002
#define IRQF_TRIGGER_HIGH 0x00000004
#define IRQF_TRIGGER_LOW 0x00000008

#define SIZE 12

const int first_minor = 0;
const int max_devices = 255;
static dev_t devno;
struct gpio_dev {
    int no;   // GPIO number
    char name[10]; //GPIO name
    int dir; // 0: in, 1: out
};
static struct gpio_dev gpio_devs[4] = { {18, "in_b18", 0}, {23, "in_b23", 0}, {17, "in_b17", 0}, {24, "in_b24", 0} };
static int gpios_len = 4;
static struct class* gpioDriver_class;
static struct cdev gpioDriver_cdev;
static struct device* gpioDriver_dev;



//interupt handler ***************************************************************************************

static DECLARE_WAIT_QUEUE_HEAD(wq17);
static int flag17 = 0;

static DECLARE_WAIT_QUEUE_HEAD(wq18);
static int flag18 = 0;

static DECLARE_WAIT_QUEUE_HEAD(wq23);
static int flag23 = 0;

static DECLARE_WAIT_QUEUE_HEAD(wq24);
static int flag24 = 0;

static irqreturn_t gpio_isr18(int irq, void* dev_id) {

   
    if (flag18 == 1)
        return IRQ_HANDLED;
    flag18 = 1;
    wake_up_interruptible(&wq18);
    return IRQ_HANDLED;
}

static irqreturn_t gpio_isr17(int irq, void* dev_id) {


    if (flag17 == 1)
        return IRQ_HANDLED;
    flag17 = 1;
    wake_up_interruptible(&wq17);


    return IRQ_HANDLED;
}


static irqreturn_t gpio_isr23(int irq, void* dev_id) {


    if (flag23 == 1)
        return IRQ_HANDLED;

    flag23 = 1;
    wake_up_interruptible(&wq23);


    return IRQ_HANDLED;
}

static irqreturn_t gpio_isr24(int irq, void* dev_id) {

    if (flag24 == 1)
        return IRQ_HANDLED;

    flag24 = 1;
    wake_up_interruptible(&wq24);

    return IRQ_HANDLED;
}



static int gpioDriver_probe(struct platform_device* pdev) {
    printk("hello from probe\n");
    int err = 0;
    for (int i = 0; i < gpios_len; i++)
    {
        err = gpio_request(gpio_devs[i].no, gpio_devs[i].name);
        if (err)
        {
            pr_err("Failed gpio request for %s\n", gpio_devs[i].name);
            goto Error;
        }
        if (gpio_devs[i].dir == 0)
        {
            gpio_direction_input(gpio_devs[i].no);
        }
        if (gpio_devs[i].dir == 1)
        {
            gpio_direction_output(gpio_devs[i].no, 0); // GPIO direction;
        }
        gpioDriver_dev = device_create(gpioDriver_class, NULL, MKDEV(MAJOR(devno), i), NULL, gpio_devs[i].name);
        if (IS_ERR(gpioDriver_dev))
        {
            pr_err("Failed gpio request for %s\n", gpio_devs[i].name);
            goto Error;
        }
    }
    return 0;
Error: for (int i = 0; i < gpios_len; i++)
{
    gpio_free(gpio_devs[i].no);
    device_destroy(gpioDriver_class, MKDEV(MAJOR(devno), i));
}
return err;

}
static int gpioDriver_remove(struct platform_device* pdev) {
    printk("hello from remove\n");
    for (int i = 0; i < gpios_len; i++)
    {
        gpio_free(gpio_devs[i].no);
        device_destroy(gpioDriver_class, MKDEV(MAJOR(devno), i));
    }
    return 0;
}
static const struct of_device_id gpioDriver_platform_device_match[] = {
    {.compatible = "ase, plat_drv",},
    {}
};
static struct platform_driver gpioDriver_platform_driver = {
    .probe = gpioDriver_probe,
    .remove = gpioDriver_remove,
    .driver = {
    .name = "gpio_platform_device_driver",
    .of_match_table = gpioDriver_platform_device_match,
    .owner = THIS_MODULE, }, };
int gpioDriver_open(struct inode* inode, struct file* filep)
{
    int major, minor;
    major = MAJOR(inode->i_rdev);
    minor = MINOR(inode->i_rdev);
    printk("Opening gpio Device [major], [minor]: %i, %i\n", major, minor);
    return 0;
}
int gpioDriver_release(struct inode* inode, struct file* filep)
{
    int minor, major;
    major = MAJOR(inode->i_rdev);
    minor = MINOR(inode->i_rdev);
    printk("Closing/Releasing gpio Device [major], [minor]: %i, %i\n", major, minor);
    return 0;
}

//

ssize_t gpioDriver_read(struct file* filep, char __user* buf,
    size_t count, loff_t* f_pos)
{

    if (iminor(filep->f_inode) == 0)
    {
        wait_event_interruptible(wq18, flag18 == 1);
        msleep(200);
        flag18 = 0;
    }

    if (iminor(filep->f_inode) == 1)
    {
        wait_event_interruptible(wq23, flag23 == 1);
        msleep(200);
        flag23 = 0;
    }

    if (iminor(filep->f_inode) == 2)
    {
        wait_event_interruptible(wq17, flag17 == 1);
        msleep(200);
        flag17 = 0;
    }

    if (iminor(filep->f_inode) == 3)
    {
        wait_event_interruptible(wq24, flag24 == 1);
        msleep(200);
        flag24 = 0;
    }

    char kbuf[12];
    int len, value, err, minorNum;
    minorNum = iminor(filep->f_inode);
    value = gpio_get_value(gpio_devs[minorNum].no);

    len = count < 12 ? count : 12; /* Truncate to smallest */
    len = snprintf(kbuf, len, "%i", value); /* Create string */
    err = copy_to_user(buf, kbuf, ++len); /* Copy to user */
    if (err)
        printk("Unable to copy all bytes to user");

    *f_pos += len;
    return len;
}
ssize_t gpioDriver_write(struct file* filep, const char __user* ubuf,
    size_t count, loff_t* f_pos)
{
    int len, value, minorNum, err = 0;
    minorNum = iminor(filep->f_inode);
    char kbuf[12];
    len = count < 12 ? count : 12; /* Truncate to smaller buffer size */

    err = copy_from_user(kbuf, ubuf, len);
    if (err < 0)
        return -EFAULT;
    err = sscanf(kbuf, "%d", &value);
    if (err == -1)
        pr_err("Error converting string to int\n");
    gpio_set_value(gpio_devs[minorNum].no, value);
    pr_info("Wrote %i from minor %i\n", value, iminor(filep->f_inode));

    return count;
}
struct file_operations gpioDriver_fops = {
   .owner = THIS_MODULE,
   .open = gpioDriver_open,
   .release = gpioDriver_release,
   .read = gpioDriver_read,
   .write = gpioDriver_write };
static int gpioDriver_init(void)
{
    // Alloker Major/Minor
    int err = alloc_chrdev_region(&devno, first_minor, max_devices, "gpio driver");
    if (MAJOR(devno) <= 0)
    {
        pr_err("Failed to register chardev\n");
        goto fail_chrdev;
    }

    // Class Create
    gpioDriver_class = class_create(THIS_MODULE, "gpio driver class");
    if (IS_ERR(gpioDriver_class))
    {
        pr_err("Failed to create class");
        goto fail_class;
    }

    cdev_init(&gpioDriver_cdev, &gpioDriver_fops); // Cdev Init
    err = cdev_add(&gpioDriver_cdev, devno, max_devices); // Add Cdev
    if (err)
    {
        pr_err("Failed to add cdev");
        goto fail_cdev;
    }
    err = platform_driver_register(&gpioDriver_platform_driver);
    if (err)
    {
        pr_err("Failed platform driver register");
        goto fail_platform;
    }



    // interupt request ********************************************************************************************


    err = request_irq(gpio_to_irq(gpio_devs[0].no), gpio_isr18, IRQF_TRIGGER_FALLING, gpio_devs[0].name, NULL);
    if (err)
    {
        pr_err("Failed to make interupts");
        goto fail_interupt;
    }
    err = request_irq(gpio_to_irq(gpio_devs[1].no), gpio_isr23, IRQF_TRIGGER_FALLING, gpio_devs[1].name, NULL);
    if (err)
    {
        pr_err("Failed to make interupts");
        goto fail_interupt;
    }

    err = request_irq(gpio_to_irq(gpio_devs[2].no), gpio_isr17, IRQF_TRIGGER_FALLING, gpio_devs[2].name, NULL);
    if (err)
    {
        pr_err("Failed to make interupts");
        goto fail_interupt;
    }

    err = request_irq(gpio_to_irq(gpio_devs[3].no), gpio_isr24, IRQF_TRIGGER_FALLING, gpio_devs[3].name, NULL);
    if (err)
    {
        pr_err("Failed to make interupts");
        goto fail_interupt;
    }

    return 0;

fail_platform:  platform_driver_unregister(&gpioDriver_platform_driver);
fail_cdev:      class_destroy(gpioDriver_class); // Class Destroy
fail_class:     unregister_chrdev_region(devno, max_devices);// Unregister Device
fail_chrdev:
fail_interupt:
    return err;
}
static void gpioDriver_exit(void)
{
    platform_driver_unregister(&gpioDriver_platform_driver);
    cdev_del(&gpioDriver_cdev); // Delete Cdev
    unregister_chrdev_region(devno, max_devices);// Unregister Device
    class_destroy(gpioDriver_class); // Class Destroy

    // dealocate interupt


    free_irq(gpio_to_irq(17), NULL);
    free_irq(gpio_to_irq(18), NULL);
    free_irq(gpio_to_irq(23), NULL);
    free_irq(gpio_to_irq(24), NULL);

}
module_init(gpioDriver_init);
module_exit(gpioDriver_exit);
MODULE_AUTHOR("Szymon P");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver for gpio");