#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>


class Motor {
private:
  pin_size_t _pin_en;
  pin_size_t _pin_a;
  pin_size_t _pin_b;
  uint8_t _max_speed = 255;

public:
  Motor(pin_size_t pin_en, pin_size_t pin_a, pin_size_t pin_b);
  void setup(void);
  void setSpeed(int16_t s = 0);
  void stop(void);
  void stopSlow(void);
  void setMaxSpeed(uint8_t s = 255);
};

#endif