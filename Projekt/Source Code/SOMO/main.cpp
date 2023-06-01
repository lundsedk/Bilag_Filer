#include "somo_class.hpp"
#include <boost/asio.hpp>

using namespace boost;


int main() {
    // Create an instance of the SoundModuleDriver and specify the device name
    SoundModuleDriver driver("/dev/ttyS0");

    // Play a sound using the driver
    driver.playSound();
    //driver.increaseVolume(20);
    //driver.sleep();
    return 0;
}
