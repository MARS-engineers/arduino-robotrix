#ifndef RoverOne
#error "This code is intended to run on MARS-Engineers Robotrix Rover board and compilled using https://github.com/MARS-engineers/arduino-boards/ pacakge"
#endif

#include <RobotrixPower.h>

// Example use of RobotrixPower.h

void setup() {
  Power.setup();
}

void loop() {
  float busvoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  busvoltage = Power.getVoltage();
  current_mA = Power.getCurrent();
  power_mW = Power.getPower();

  Serial.print("Bus Voltage:   ");
  Serial.print(busvoltage);
  Serial.println(" V");
  Serial.print("Current:       ");
  Serial.print(current_mA);
  Serial.println(" mA");
  Serial.print("Power:         ");
  Serial.print(power_mW);
  Serial.println(" mW");
  delay(1000);
}
