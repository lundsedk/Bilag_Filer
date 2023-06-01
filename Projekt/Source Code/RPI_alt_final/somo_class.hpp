#ifndef _SOMO_CLASS_H_
#define _SOMO_CLASS_H_

#include <boost/asio.hpp>

using namespace boost;

class SoundModuleDriver {
public:
    SoundModuleDriver(const std::string& device);
    ~SoundModuleDriver();
    void playSound();
    void increaseVolume(int x);
    void decreaseVolume(int x);
    void sleep();
    void reset();
private:
    asio::io_context io_;
    asio::serial_port port_;
    std::string device_;
};

#endif
