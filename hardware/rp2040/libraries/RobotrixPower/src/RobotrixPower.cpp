#include "./RobotrixPower.h"

Adafruit_INA219 InputSensor(INPUT_SENSOR_ADDRESS);

/*!
 *  @brief  Setup power sensor
 *          
 */
void PowerClass::setup(void){
    InputSensor.begin(InputSensorWire); // Setup sensor on given IIC interface
}

/*!
 *  @brief  Get volatge from sensor
 *  @return Voltage U[V]
 *          float value
 */
float PowerClass::getVoltage(){
    return InputSensor.getBusVoltage_V();
}

/*!
 *  @brief  Get current from sensor
 *  @return Current I[mA]
 *          float value
 */
float PowerClass::getCurrent(){
    return InputSensor.getCurrent_mA();
}

/*!
 *  @brief  Get power from sensor
 *  @return Power P[mW]
 *          float value
 */
float PowerClass::getPower(){
    return InputSensor.getPower_mW();
}

PowerClass Power;