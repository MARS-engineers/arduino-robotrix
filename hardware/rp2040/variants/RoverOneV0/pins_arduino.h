#pragma once

// Pin definitions taken from:
//    https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf

#define RoverOne V0
#define HW_VERSION "0.0.5"

// LEDs
#define PIN_LED        (25u)

#define PIN_MOT_1_EA (21u)
#define PIN_MOT_1_EB (22u)
#define PIN_MOT_2_EA (2u)
#define PIN_MOT_2_EB (3u)
#define PIN_MOT_2_E (4u)
#define PIN_MOT_2_A (5u)
#define PIN_MOT_2_B (6u)
#define PIN_MOT_1_A (7u)
#define PIN_MOT_1_B (8u)
#define PIN_MOT_1_E (9u)
#define PIN_MOT_4_E (10u)
#define PIN_MOT_4_A (11u)
#define PIN_MOT_4_B (12u)
#define PIN_MOT_3_A (13u)
#define PIN_MOT_3_B (14u)
#define PIN_MOT_3_E (15u)
#define PIN_MOT_3_EA (16u)
#define PIN_MOT_3_EB (17u)
#define PIN_MOT_4_EA (18u)
#define PIN_MOT_4_EB (19u)
#define PIN_MOT_STBY (20u)


// Serial
#define PIN_SERIAL1_TX (0u)
#define PIN_SERIAL1_RX (1u)

//SERIAL2 WILL NOT WORK! it uses uart0, same as SERIAL1
#define PIN_SERIAL2_TX (-1)
#define PIN_SERIAL2_RX (-1)

// SPI
#define PIN_SPI0_MISO  (-1)
#define PIN_SPI0_MOSI  (-1)
#define PIN_SPI0_SCK   (-1)
#define PIN_SPI0_SS    (-1)

// Wire
#define PIN_WIRE0_SDA  (-1)
#define PIN_WIRE0_SCL  (-1)

#define PIN_WIRE1_SDA  (26u)
#define PIN_WIRE1_SCL  (27u)

#define InputSensorWire &Wire1
#define INPUT_SENSOR_ADDRESS 0x40
#define CommandWire Wire1
#define CRFSUart &Serial1

// Radio
#define PIN_RADIO_CE (-1)
#define PIN_RADIO_CSN (-1)
#define PIN_RADIO_IRQ (-1)

#define PIN_RGB_LEDS (-1)

#define SERIAL_HOWMANY (2u)
#define SPI_HOWMANY    (0u)
#define WIRE_HOWMANY   (1u)

#include "../common.h"