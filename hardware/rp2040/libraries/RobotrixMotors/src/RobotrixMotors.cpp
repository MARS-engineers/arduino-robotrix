#include "./RobotrixMotors.h"

Motor::Motor(int pin_en, int pin_a, int pin_b) {
  _pin_en = pin_en;
  _pin_a = pin_a;
  _pin_b = pin_b;
}

void Motor::setup() {
#ifdef RoverOne
  pinMode(_pin_en, OUTPUT);
  pinMode(_pin_a, OUTPUT);
  pinMode(_pin_b, OUTPUT);
#endif
}

void Motor::SetSpeed(int8_t s) {
#ifdef RoverOne
  byte speed = map(abs(s), 0, 127, 0, 255);
  bool d = s < 0;
  // DEBUG_DEBUG("Set speed: %d, input %d", speed, s);
  analogWrite(_pin_en, speed);
  digitalWrite(_pin_a, d);
  digitalWrite(_pin_b, !d);
#endif
}

void Motor::stopSlow() {
#ifdef RoverOne
  analogWrite(_pin_en, LOW);
#endif
}

void Motor::stop() {
#ifdef RoverOne
  digitalWrite(_pin_a, LOW);
  digitalWrite(_pin_b, LOW);
#endif
}