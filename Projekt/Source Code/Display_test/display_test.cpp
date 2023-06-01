#include "display.h"

int main()
{
    Log logObj;
    PlanteID planteIDObj;
    images imagesObj(&logObj, &planteIDObj);
    display displayObj(&imagesObj);

    displayObj.turnOn();
    sleep(5);

    displayObj.show(START);
    sleep(5);

    planteIDObj.setPlanteType(TYPE_FLOWER);
    planteIDObj.setPlanteName("JOHN");
    displayObj.show(PLANT_DATA);
    sleep(5);

    int a, b, c, d;
    for (size_t i = 0; i < 12 * 24 * 7; i++)
    {
        a = 10;
        b = 20;
        c = 3;
        d = 4;

        logObj.setLog({ a,b,c,d });
    }

    planteIDObj.setPlanteType(TYPE_LEAF);
    displayObj.show(PLANT_DATA);
    sleep(5);
    imagesObj.setPosition(1);
    planteIDObj.setPlanteType(TYPE_CACTUS);
    displayObj.show(PLANT_DATA);
    sleep(5);
    imagesObj.setPosition(2);
    planteIDObj.setPlanteType(TYPE_CACTUS);
    displayObj.show(PLANT_DATA);
    sleep(5);
    imagesObj.setPosition(3);
    planteIDObj.setPlanteType(TYPE_CACTUS);
    displayObj.show(PLANT_DATA);
    sleep(5);

    imagesObj.setPosition(0);
    displayObj.show(PLANT);
    sleep(5);
    imagesObj.setPosition(1);
    displayObj.show(PLANT);
    sleep(5);

    imagesObj.setPosition(0);
    displayObj.show(SETUP);
    sleep(5);
    imagesObj.setPosition(1);
    displayObj.show(SETUP);
    sleep(5);

    imagesObj.setPosition(0);
    displayObj.show(SET_TYPE);
    sleep(5);
    imagesObj.setPosition(1);
    displayObj.show(SET_TYPE);
    sleep(5);
    imagesObj.setPosition(2);
    displayObj.show(SET_TYPE);
    sleep(5);

    imagesObj.setPosition(0);
    displayObj.show(SET_NAME);
    sleep(5);
    imagesObj.setPosition(1);
    displayObj.show(SET_NAME);
    sleep(5);
    imagesObj.setPosition(2);
    displayObj.show(SET_NAME);
    sleep(5);
    imagesObj.setPosition(3);
    displayObj.show(SET_NAME);
    sleep(5);
    imagesObj.setPosition(4);
    displayObj.show(SET_NAME);
    sleep(5);
    imagesObj.setPosition(5);
    displayObj.show(SET_NAME);
    sleep(5);
    imagesObj.setPosition(6);
    displayObj.show(SET_NAME);
    sleep(5);
    imagesObj.setPosition(7);
    displayObj.show(SET_NAME);
    sleep(5);

    displayObj.show(LOG_LIGHT);
    sleep(5);

    displayObj.show(LOG_HUMIDITY);
    sleep(5);

    displayObj.show(LOG_WEIGHT);
    sleep(5);

    displayObj.turnOff();

    return 0;
}