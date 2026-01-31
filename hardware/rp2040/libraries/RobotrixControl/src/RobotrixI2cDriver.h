#pragma once
#include <Arduino.h>

class I2cCommandBus {
public:
  void setup(uint8_t address);

private:
  static void onReceiveStatic(int len);
  void onReceive(uint8_t len);

  static I2cCommandBus* _instance;
};

extern I2cCommandBus I2cDriver;
