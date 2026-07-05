#include "./RobotrixMotors.h"

Motor::Motor(pin_size_t pin_en, pin_size_t pin_a, pin_size_t pin_b) {
  _pin_en = pin_en;
  _pin_a = pin_a;
  _pin_b = pin_b;
}

void Motor::setup() {
  pinMode(_pin_en, OUTPUT);
  pinMode(_pin_a, OUTPUT);
  pinMode(_pin_b, OUTPUT);
}

void Motor::setSpeed(int16_t s) {
  uint32_t speed = map(abs(s), 0, _max_speed, 0, 255);
  //uint8_t speed = abs(s);
  bool d = s < 0;
  //Serial.printf("Set speed: %d, input %d\n", speed, s);
  analogWrite(_pin_en, speed);
  digitalWrite(_pin_a, d);
  digitalWrite(_pin_b, !d);
}

void Motor::stopSlow() {
  analogWrite(_pin_en, LOW);
}

void Motor::stop() {
  digitalWrite(_pin_a, LOW);
  digitalWrite(_pin_b, LOW);
}

void Motor::setMaxSpeed(uint8_t s){
  _max_speed = s;
}