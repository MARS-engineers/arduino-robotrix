#pragma once
#include <Arduino.h>
#include <cstdint>

class I2cCommandBus {
public:

  void setup(uint8_t address = 0x55);
  void send(uint8_t address, uint8_t *data, size_t size);
  void debugOn(bool debug = true);
private:
  static void onReceiveStatic(int len);
  void onReceive(uint8_t len);

  static I2cCommandBus *_instance;
  bool _DebugOn = false;
};

extern I2cCommandBus I2cDriver;
