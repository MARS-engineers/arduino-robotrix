#include "RobotrixI2cDriver.h"
#include "RobotrixCommand.h"
#include <Wire.h>
#include <cstddef>
#include <cstdint>

I2cCommandBus I2cDriver;
I2cCommandBus *I2cCommandBus::_instance = nullptr;

void I2cCommandBus::setup(uint8_t address) {
  _instance = this;
  CommandWire.begin(address);
  CommandWire.onReceive(onReceiveStatic);
}

void I2cCommandBus::send(uint8_t address, uint8_t *data, size_t size) {
  if (_instance) {
    CommandWire.writeAsync(address, data, size);
  }
}

void I2cCommandBus::onReceiveStatic(int len) {

  if (_instance) {
    _instance->onReceive(len);
  }
}

void I2cCommandBus::debugOn(bool debug) { _DebugOn = debug; }

void I2cCommandBus::onReceive(uint8_t len) {
  uint8_t buf[16];
  uint8_t i = 0;

  while (CommandWire.available() && i < sizeof(buf))
    buf[i++] = CommandWire.read();

  Remote.dispatch(buf, i);

  if (_DebugOn) {
    Serial.printf("bytes: %i, data: ", len);
    for (byte i = 0; i <= len; i++) {
      Serial.printf(" %02x", buf[i]);
    }
    Serial.println("");
  }
}
