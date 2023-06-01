#include "somo_class.hpp"

using namespace boost;

SoundModuleDriver::SoundModuleDriver(const std::string& device)
        : io_(), port_(io_), device_(device)
    {
        // Open the serial port
        port_.open(device_);

        // Set the baud rate to 9600
        port_.set_option(asio::serial_port_base::baud_rate(9600));
}

SoundModuleDriver::~SoundModuleDriver() {
        // Close the serial port
        port_.close();
}

void SoundModuleDriver::playSound() {
        // Send the command to play a sound
        uint8_t play[] = {0x7E, 0x0D, 0x00, 0x00, 0x00, 0xFF, 0xF3, 0xEF};
        asio::write(port_, asio::buffer(play, sizeof(play)));
}

void SoundModuleDriver::increaseVolume(int x) {
       // For-loop increasing sound x times
       for(int i=0;i<x;i++)
       {
            // Send the command to increase the volume
            uint8_t increase[] = {0x7E, 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0xEF};
            asio::write(port_, asio::buffer(increase, sizeof(increase)));
      }
}

void SoundModuleDriver::decreaseVolume(int x) {
        // For-loop decreasing sound x times
        for(int i=0;i<x;i++)
        {
            // Send the command to decrease the volume
            uint8_t decrease[] = {0x7E, 0x05, 0x00, 0x00, 0x00, 0xFF, 0xFB, 0xEF};
            asio::write(port_, asio::buffer(decrease, sizeof(decrease)));
        }
}

void SoundModuleDriver::sleep() {
        // Send the command to put the SOMO into a sleep state
        uint8_t sleep[] = {0x7E, 0x0A, 0x00, 0x00, 0x00, 0xFF, 0xF6, 0xEF};
        asio::write(port_, asio::buffer(sleep, sizeof(sleep)));
}

void SoundModuleDriver::reset() {
        // Send the command to reset the SOMO to be in power-on state
        uint8_t reset[] = {0x7E, 0x0C, 0x00, 0x00, 0x00, 0xFF, 0xF4, 0xEF};
        asio::write(port_, asio::buffer(reset, sizeof(reset)));
}
