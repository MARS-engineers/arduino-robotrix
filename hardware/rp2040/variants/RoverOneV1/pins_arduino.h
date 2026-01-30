#pragma once

// Pin definitions taken from:
//    https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf

#define PICO_RP2350A __PICO_RP2350A
#define RoverOne V1

// Motors encoders
#define PIN_MOT_4_EB (4u)
#define PIN_MOT_4_EA (5u)
#define PIN_MOT_3_EB (6u)
#define PIN_MOT_3_EA (7u)
#define PIN_MOT_2_EB (8u)
#define PIN_MOT_2_EA (9u)
#define PIN_MOT_1_EB (10u)
#define PIN_MOT_1_EA (11u)
// Motors
#define PIN_MOT_1_E (12u)
#define PIN_MOT_1_B (13u)
#define PIN_MOT_1_A (14u)
#define PIN_MOT_2_B (15u)
#define PIN_MOT_2_A (16u)
#define PIN_MOT_2_E (17u)
#define PIN_MOT_3_E (18u)
#define PIN_MOT_3_B (19u)
#define PIN_MOT_3_A (20u)
#define PIN_MOT_4_B (21u)
#define PIN_MOT_4_A (22u)
#define PIN_MOT_4_E (23u)
#define PIN_MOT_STBY (24u)

// LED
#define PIN_LED        (25u)

// Serial
#define PIN_SERIAL1_TX (28u)
#define PIN_SERIAL1_RX (29u)
// Serial2 will be same as Serial1 due to some errors
#define PIN_SERIAL2_TX (28u)
#define PIN_SERIAL2_RX (29u)

// SPI
#define PIN_SPI0_MISO  (32u)
#define PIN_SPI0_MOSI  (35u)
#define PIN_SPI0_SCK   (34u)
#define PIN_SPI0_SS    (17u)

// Wire
#define PIN_WIRE0_SDA  (36u)
#define PIN_WIRE0_SCL  (37u)

#define PIN_WIRE1_SDA  (26u)
#define PIN_WIRE1_SCL  (27u)

#define InputSensorWire &Wire1
#define INPUT_SENSOR_ADDRESS 0x40



#define PIN_RADIO_CE (31)
#define PIN_RADIO_CSN (33)
#define PIN_RADIO_IRQ (41)

#define PIN_RGB_LEDS (38)


#define SERIAL_HOWMANY (2u)
#define SPI_HOWMANY    (1u)
#define WIRE_HOWMANY   (2u)

#include "../common.h"