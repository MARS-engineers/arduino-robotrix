#include "RobotrixI2cDriver.h"
#include "RobotrixCommand.h"
#include <Wire.h>

I2cCommandBus I2cDriver;
I2cCommandBus* I2cCommandBus::_instance = nullptr;

void I2cCommandBus::setup(uint8_t address) {
  _instance = this;
  Wire.begin(address);
  Wire.onReceive(onReceiveStatic);
}

void I2cCommandBus::onReceiveStatic(int len) {
  if (_instance)
    _instance->onReceive(len);
}

void I2cCommandBus::onReceive(uint8_t len) {
  uint8_t buf[16];
  uint8_t i = 0;

  while (Wire.available() && i < sizeof(buf))
    buf[i++] = Wire.read();

  Remote.dispatch(buf, i);
}
