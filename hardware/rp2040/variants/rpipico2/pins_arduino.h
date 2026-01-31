#pragma once

// Pin definitions taken from:
//    https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf

#define PICO_RP2350A 1

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

// LEDs
#define PIN_LED        (25u)

// Serial
#define PIN_SERIAL1_TX (0u)
#define PIN_SERIAL1_RX (1u)

#define PIN_SERIAL2_TX (8u)
#define PIN_SERIAL2_RX (9u)

// SPI
#define PIN_SPI0_MISO  (16u)
#define PIN_SPI0_MOSI  (19u)
#define PIN_SPI0_SCK   (18u)
#define PIN_SPI0_SS    (17u)

#define PIN_SPI1_MISO  (12u)
#define PIN_SPI1_MOSI  (15u)
#define PIN_SPI1_SCK   (14u)
#define PIN_SPI1_SS    (13u)

// Wire
#define PIN_WIRE0_SDA  (4u)
#define PIN_WIRE0_SCL  (5u)

#define PIN_WIRE1_SDA  (26u)
#define PIN_WIRE1_SCL  (27u)

#define SERIAL_HOWMANY (3u)
#define SPI_HOWMANY    (2u)
#define WIRE_HOWMANY   (2u)

#define RoverOne
#define HW_VERSION "0.0.0"

#include "../common.h"
