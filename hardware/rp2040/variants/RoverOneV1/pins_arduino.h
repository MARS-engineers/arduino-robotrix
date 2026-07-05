#pragma once

// Pin definitions taken from:
//    https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf

#define PICO_RP2350A __PICO_RP2350A
#define RoverOne(V1)
#define HW_VERSION "0.1.0"

// Motors encoders
#define PIN_MOT_4_EB (21u)
#define PIN_MOT_4_EA (23u)
#define PIN_MOT_3_EB (20u)
#define PIN_MOT_3_EA (22u)
#define PIN_MOT_2_EB (7u)
#define PIN_MOT_2_EA (5u)
#define PIN_MOT_1_EB (6u)
#define PIN_MOT_1_EA (4u)
// Motors
#define PIN_MOT_1_E (8u)
#define PIN_MOT_1_B (10u)
#define PIN_MOT_1_A (9u)
#define PIN_MOT_2_B (11u)
#define PIN_MOT_2_A (12u)
#define PIN_MOT_2_E (13u)
#define PIN_MOT_3_E (14u)
#define PIN_MOT_3_B (16u)
#define PIN_MOT_3_A (15u)
#define PIN_MOT_4_B (17u)
#define PIN_MOT_4_A (18u)
#define PIN_MOT_4_E (19u)
#define PIN_MOT_STBY (24u)

// LED
#define PIN_LED (26u)

// Serial0
#define PIN_SERIAL1_TX (32u)
#define PIN_SERIAL1_RX (33u)

// Serial1
#define PIN_SERIAL2_TX (36u)
#define PIN_SERIAL2_RX (37u)

// Sonars
#define PIN_SONAR_IRQ (30u)
#define SONAR_ADDRESS 0x20
enum SonarDirections : uint8_t { // Directions of sonars, channel
  Front = 0,
  Front_L = 1,
  Left = 2,
  Back = 3,
  Front_R = 4,
  Right = 5,
  Aux_A = 6,
  Aux_B = 7
};

// SPI
#define PIN_SPI0_MISO (44u)
#define PIN_SPI0_MOSI (43u)
#define PIN_SPI0_SCK (42u)
#define PIN_SPI0_SS (-1u)

// Wire
#define PIN_WIRE0_SDA (26u)
#define PIN_WIRE0_SCL (27u)

#define PIN_WIRE1_SDA (28u)
#define PIN_WIRE1_SCL (29u)

#define InputSensorWire &Wire1
#define INPUT_SENSOR_ADDRESS 0x40

#define CommandWire &Wire1
#define CRFSUart &Serial2

#define PIN_RADIO_CE (46)
#define PIN_RADIO_CSN (47)
#define PIN_RADIO_IRQ (45)

#define PIN_RGB_LEDS (31)

#define SERIAL_HOWMANY (2u)
#define SPI_HOWMANY (1u)
#define WIRE_HOWMANY (2u)

#include "../common.h"