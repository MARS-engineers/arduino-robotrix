#include "./RobotrixSonars.h"

#include "./OctoSonar/src/OctoSonar.h"

OctoSonar SonarSensors(SONAR_ADDRESS, PIN_SONAR_IRQ);

void SonarsClass::enable() { _sonarsEnable = true; }

void SonarsClass::disable() { _sonarsEnable = false; }

void SonarsClass::begin() {
  SonarSensors.begin(0xff); // initialize bus, pins etc
  attachInterrupt(digitalPinToInterrupt(PIN_SONAR_IRQ), dispatchCallback, FALLING);
}

void SonarsClass::doSonar() {
  if (_sonarsEnable)
    OctoSonar::doSonar(); // call every cycle, OctoSonar handles the spacing
}

uint8_t SonarsClass::readSonar(SonarDirections d) {
  uint8_t distance = 0;
  distance = SonarSensors.read((int)d);
  return distance;
}

void regitsterCallbackIRQ(IRQEvent Event) {
    RaiseEvent = Event;
}

void dispatchCallback(){
    RaiseEvent();
}

SonarsClass Sonars;