/*
  boosterpack_map.h - An embedded CNC Controller with rs274/ngc (g-code) support

  Driver code for ESP32

  Part of grblHAL

  Copyright (c) 2020-2024 Terje Io

  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.
*/
#if N_ABC_MOTORS > 0
#error "Axis configuration is not supported!"
#endif

#define BOARD_NAME "CNC BoosterPack"
#define BOARD_URL "https://github.com/terjeio/CNC_Boosterpack"

#if TRINAMIC_ENABLE
#ifdef TRINAMIC_MIXED_DRIVERS
#undef TRINAMIC_MIXED_DRIVERS
#endif
#define TRINAMIC_MIXED_DRIVERS 0
#ifdef TRINAMIC_I2C
#undef TRINAMIC_I2C
#endif
#define TRINAMIC_I2C 1
#endif

#if !EEPROM_ENABLE
//#undef EEPROM_ENABLE
//#define EEPROM_ENABLE 1 // I2C EEPROM (24LC16) support.
#endif

#if !IOEXPAND_ENABLE
#undef IOEXPAND_ENABLE
#define IOEXPAND_ENABLE 1 // I2C IO expander for some output signals.
#endif

// Define step pulse output pins.
#define X_STEP_PIN              GPIO_NUM_26
#define Y_STEP_PIN              GPIO_NUM_27
#define Z_STEP_PIN              GPIO_NUM_14

// Define step direction output pins.
#define X_DIRECTION_PIN         GPIO_NUM_2
#define Y_DIRECTION_PIN         GPIO_NUM_15
#define Z_DIRECTION_PIN         GPIO_NUM_12

// Define stepper driver enable/disable output pin(s).
#define STEPPERS_ENABLE_PIN    IOEXPAND

// Define homing/hard limit switch input pins and limit interrupt vectors.
#define X_LIMIT_PIN             GPIO_NUM_4
#define Y_LIMIT_PIN             GPIO_NUM_16
#define Z_LIMIT_PIN             GPIO_NUM_32

// Define driver spindle pins

#if DRIVER_SPINDLE_PWM_ENABLE
#define SPINDLE_PWM_PIN         GPIO_NUM_17
#else
#define AUXOUTPUT0_PIN          GPIO_NUM_17
#endif

#if DRIVER_SPINDLE_DIR_ENABLE
#define SPINDLE_DIRECTION_PIN   IOEXPAND
#endif

#if DRIVER_SPINDLE_ENABLE
#define SPINDLE_ENABLE_PIN      IOEXPAND
#endif

// Define flood and mist coolant enable output pins.
#define COOLANT_FLOOD_PIN       IOEXPAND
#define COOLANT_MIST_PIN        IOEXPAND

#ifdef ADD_SERIAL1
#define SERIAL1_PORT
#define UART1_RX_PIN            GPIO_NUM_33
#else
#define AUXINPUT0_PIN           GPIO_NUM_33
#endif
#define AUXINPUT1_PIN           GPIO_NUM_34
#define AUXINPUT2_PIN           GPIO_NUM_13

// Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
#define RESET_PIN               GPIO_NUM_35
#define FEED_HOLD_PIN           GPIO_NUM_39
#define CYCLE_START_PIN         GPIO_NUM_36

// Define probe switch input pin.
#if PROBE_ENABLE
#define PROBE_PIN               AUXINPUT2_PIN
#endif

#if SAFETY_DOOR_ENABLE
#define SAFETY_DOOR_PIN         AUXINPUT1_PIN
#endif

#if I2C_STROBE_ENABLE && defined(AUXINPUT0_PIN)
#define I2C_STROBE_PIN          AUXINPUT0_PIN
#endif

#if NEOPIXELS_ENABLE && !I2C_STROBE_ENABLE && defined(AUXINPUT0_PIN)
#define NEOPIXELS_PIN           AUXINPUT0_PIN
#define NEOPIXELS_NUM           NEOPIXELS_ENABLE
#endif

#ifdef ADD_SERIAL1
#if MPG_ENABLE == 1
#define MPG_ENABLE_PIN          GPIO_NUM_25
#else
#define UART1_TX_PIN            GPIO_NUM_25
#endif
#if MODBUS_ENABLE & MODBUS_RTU_DIR_ENABLED
#define MODBUS_DIRECTION_PIN    GPIO_NUM_25 //??
#endif
#else
//#define AUXOUTPUT0_PIN          GPIO_NUM_25
#endif

#define NEOPIXELS_NUM       2
#define NEOPIXELS_PIN       GPIO_NUM_25

// Define I2C port/pins
#define I2C_PORT                I2C_NUM_1
#define I2C_SDA                 GPIO_NUM_21
#define I2C_SCL                 GPIO_NUM_22
#define I2C_CLOCK               100000

#if SDCARD_ENABLE
// Pin mapping when using SPI mode.
// With this mapping, SD card can be used both in SPI and 1-line SD mode.
// Note that a pull-up on CS line is required in SD mode.
#define PIN_NUM_MISO        GPIO_NUM_19
#define PIN_NUM_MOSI        GPIO_NUM_23
#define PIN_NUM_CLK         GPIO_NUM_18
#define PIN_NUM_CS          GPIO_NUM_5
#endif

#if IOEXPAND_ENABLE
typedef union {
    uint8_t mask;
    struct {
        uint8_t stepper_enable_z :1,
                stepper_enable_y :1,
                mist_on          :1,
                flood_on         :1,
                reserved         :1,
                spindle_dir      :1,
                stepper_enable_x :1,
                spindle_on       :1;
    };
} ioexpand_t;
#endif

