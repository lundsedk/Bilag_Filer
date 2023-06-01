/*****************************************************************************
*
* File                : main.cpp
* Hardware Environment: Raspberry Pi (Zero)
* Build Environment   : g++
* Version             : V1.0
* Author              : A. Lihn
*
******************************************************************************/

#include <iostream>
#include <pthread.h>
#include "display.h"
#include "iPotWifi.h"
#include "somo_class.hpp"

#define DATA_DELAY 10

static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

Log logObj;
PlanteID planteIDObj;
images imagesObj(&logObj, &planteIDObj);
display displayObj(&imagesObj);
SoundModuleDriver alarmObj("/dev/ttyS0");

bool displayStatus_; //true=on, false=off

void* button_power(void* arg)
{
    char buffer[10];

    int fd = open("/dev/in_b17", O_RDONLY);
    if (fd == -1) {
        std::cout << "Unable to open the device file." << std::endl;
        return NULL;
    }

    while (1)
    {
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead == -1) {
            std::cout << "Error reading from device file." << std::endl;
            close(fd);
            return NULL;
        }
        std::cout << "Interrupt power" << std::endl;

        pthread_mutex_lock(&m);
        if (displayStatus_)
        {
            displayObj.turnOff();
            displayStatus_ = false;
            imagesObj.setPosition(0);
        }
        else
        {
            if (planteIDObj.isEmpty())
            {
                displayObj.turnOn();
                displayStatus_ = true;

                displayObj.show(START);
                sleep(2);
                displayObj.show(SETUP);
            }
            else
            {
                displayObj.turnOn();
                displayStatus_ = true;

                displayObj.show(START);
                sleep(2);
                displayObj.show(PLANT_DATA);
            }
        }
        pthread_mutex_unlock(&m);

    }

    close(fd);
    return NULL;
}

void* button_enter(void* arg)
{
    char buffer[10];
    char type;
    std::string name;

    int fd = open("/dev/in_b18", O_RDONLY);
    if (fd == -1) {
        std::cout << "Unable to open the device file." << std::endl;
        return NULL;
    }

    while (1)
    {
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead == -1) {
            std::cout << "Error reading from device file." << std::endl;
            close(fd);
            return NULL;
        }
        std::cout << "Interrupt enter" << std::endl;

        pthread_mutex_lock(&m);

        if (displayStatus_)
        {
            switch (imagesObj.getImage()) {
            case PLANT_DATA:
                if (logObj.isEmpty())
                {
                    imagesObj.setPosition(0);
                    displayObj.show(SETUP);
                }
                else
                {
                    switch (imagesObj.getPosition())
                    {
                    case 0: // Light log
                        imagesObj.setPosition(0);
                        displayObj.show(LOG_LIGHT);
                        break;

                    case 1: // Weight log
                        imagesObj.setPosition(0);
                        displayObj.show(LOG_WEIGHT);
                        break;

                    case 2: // Humidity log
                        imagesObj.setPosition(0);
                        displayObj.show(LOG_HUMIDITY);
                        break;

                    case 3: // Setup new plant
                        imagesObj.setPosition(0);
                        displayObj.show(SETUP);
                        break;

                    default:
                        break;
                    }
                }
                break;

            case LOG_HUMIDITY:
            case LOG_LIGHT:
            case LOG_WEIGHT:
                imagesObj.setPosition(0);
                displayObj.show(PLANT_DATA); //return to plant data
                break;

            case SETUP:
                switch (imagesObj.getPosition())
                {
                case 0: //ok
                    type = planteIDObj.getPlanteType();
                    name = planteIDObj.getPlanteName();
                    imagesObj.setPosition(0);
                    displayObj.show(SET_TYPE); //Set type of plant
                    break;

                case 1: // return
                    imagesObj.setPosition(0);
                    if (planteIDObj.isEmpty())
                    {
                        displayObj.turnOff();
                        displayStatus_ = false;
                    }
                    else
                    {
                        displayObj.show(PLANT_DATA); //return to plant data
                    }
                    break;

                default:
                    break;
                }
                break;

            case SET_TYPE:
                // Save type
                switch (imagesObj.getPosition())
                {
                case 0:
                    planteIDObj.setPlanteType(TYPE_FLOWER);
                    break;

                case 1:
                    planteIDObj.setPlanteType(TYPE_LEAF);
                    break;

                case 2:
                    planteIDObj.setPlanteType(TYPE_CACTUS);
                    break;

                default:
                    break;
                }

                imagesObj.setPosition(0);
                displayObj.show(SET_NAME); //Go to set name
                break;

            case SET_NAME:
                switch (imagesObj.getPosition())
                {
                case 0:
                    planteIDObj.setPlanteName("ROSA");
                    break;

                case 1:
                    planteIDObj.setPlanteName("ULLA");
                    break;

                case 2:
                    planteIDObj.setPlanteName("IBEN");
                    break;

                case 3:
                    planteIDObj.setPlanteName("LILY");
                    break;

                case 4:
                    planteIDObj.setPlanteName("BENT");
                    break;

                case 5:
                    planteIDObj.setPlanteName("ADAM");
                    break;

                case 6:
                    planteIDObj.setPlanteName("LARS");
                    break;

                case 7:
                    planteIDObj.setPlanteName("ASKE");
                    break;
                }

                // Save name
                imagesObj.setPosition(0);
                displayObj.show(PLANT); //Go to plant
                break;

            case PLANT:
                switch (imagesObj.getPosition())
                {
                case 0: //ok
                    //save temp plantdata to plantdata class
                    logObj.logClear();
                    imagesObj.setPosition(0);
                    displayObj.show(PLANT_DATA);
                    break;

                case 1: // not ok
                    planteIDObj.setPlanteName(name);
                    planteIDObj.setPlanteType(type);
                    imagesObj.setPosition(0);
                    displayObj.show(SETUP);
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }

        pthread_mutex_unlock(&m);
    }

    close(fd);
    return NULL;
}

void* button_up(void* arg)
{
    char buffer[10];

    int fd = open("/dev/in_b23", O_RDONLY);
    if (fd == -1) {
        std::cout << "Unable to open the device file." << std::endl;
        return NULL;
    }

    while (1)
    {

        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead == -1) {
            std::cout << "Error reading from device file." << std::endl;
            close(fd);
            return NULL;
        }
        std::cout << "Interrupt up" << std::endl;

        pthread_mutex_lock(&m);

        if (displayStatus_)
        {
            imagesObj.setPosition(imagesObj.getPosition() - 1);
            displayObj.show(imagesObj.getImage());
        }

        pthread_mutex_unlock(&m);
    }

    close(fd);
    return NULL;
}

void* button_down(void* arg)
{
    char buffer[10];

    int fd = open("/dev/in_b24", O_RDONLY);
    if (fd == -1) {
        std::cout << "Unable to open the device file." << std::endl;
        return NULL;
    }

    while (1)
    {
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead == -1) {
            std::cout << "Error reading from device file." << std::endl;
            close(fd);
            return NULL;
        }
        std::cout << "Interrupt down" << std::endl;

        pthread_mutex_lock(&m);

        if (displayStatus_)
        {
            imagesObj.setPosition(imagesObj.getPosition() + 1);
            displayObj.show(imagesObj.getImage());
        }

        pthread_mutex_unlock(&m);
    }

    close(fd);
    return NULL;
}

void* wifi_func(void* arg)
{
    iPotWifi& wifiObj = iPotWifi::getInstance();
    uint16_t const* data[4];
    while (1)
    {
        if (planteIDObj.isEmpty())
        {
        }
        else
        {
            auto data = wifiObj.getData();
            if (data == NULL)
            {
                std::cout << "No wifi connection" << std::endl;
            }
            else
            {
                pthread_mutex_lock(&m);
                logObj.setLog({ static_cast<int>(data[0]),static_cast<int>(data[1]),static_cast<int>(data[2]),static_cast<int>(data[3]) });
                if (imagesObj.getImage() == PLANT_DATA) //update plant data on screen
                    displayObj.show(PLANT_DATA);
                if (data[1] == 0) // if waterlevel low, sound alarm
                    alarmObj.playSound();
                pthread_mutex_unlock(&m);
            }
        }

        sleep(DATA_DELAY); //5 minutes
    }
    return NULL;
}

int main()
{
    displayObj.init();

    pthread_t btn_power, btn_up, btn_down, btn_enter, wifi;

    int s = pthread_create(&btn_power, NULL, button_power, NULL);
    if (s == 0)
        std::cout << "Power button thread created successfully" << std::endl;

    s = pthread_create(&btn_enter, NULL, button_enter, NULL);
    if (s == 0)
        std::cout << "Enter button thread created successfully" << std::endl;

    s = pthread_create(&btn_up, NULL, button_up, NULL);
    if (s == 0)
        std::cout << "Up button thread created successfully" << std::endl;

    s = pthread_create(&btn_down, NULL, button_down, NULL);
    if (s == 0)
        std::cout << "Down button thread created successfully" << std::endl;

    s = pthread_create(&wifi, NULL, wifi_func, NULL);
    if (s == 0)
        std::cout << "Down button thread created successfully" << std::endl;

    pthread_join(btn_power, NULL);
    pthread_join(btn_enter, NULL);
    pthread_join(btn_up, NULL);
    pthread_join(btn_down, NULL);
    pthread_join(wifi, NULL);

    return 0;
}