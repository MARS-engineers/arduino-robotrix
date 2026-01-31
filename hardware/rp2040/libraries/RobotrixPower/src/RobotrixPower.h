#pragma once


#include <Arduino.h>
#include <Wire.h>
#include "./AdafruitINA219/Adafruit_INA219.h"


class PowerClass {
private:
public:
    void setup(void);
    float getVoltage(void);
    float getCurrent(void); 
    float getPower(void);
};

extern PowerClass Power;