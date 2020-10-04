#pragma once

// Copyright 2020 Roy van Dam
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE

#include <gpio.h>
#include <config.h>

namespace board {

void init();

// Define debug LED output pins. 
constexpr static GPIO::Pin leds[] = {
    GPIO::Pin(1, 18, GPIO::Direction::Output),
    GPIO::Pin(1, 19, GPIO::Direction::Output),
    GPIO::Pin(1, 20, GPIO::Direction::Output),
    GPIO::Pin(1, 21, GPIO::Direction::Output)
};

// Define step related pins.
// NOTE: All pins within a bus must be on the same port.
// NOTE: The order is crucial, must be XYZA!
namespace step {
    // Define step pulse output pins. 
    constexpr static GPIO::Bus<N_AXIS> pulse(0, {
        GPIO::Pin(0, 0, GPIO::Direction::Output, GPIO::Pull::None, true), // X Axis
        GPIO::Pin(0, 1, GPIO::Direction::Output, GPIO::Pull::None, true), // Y Axis
        GPIO::Pin(0, 2, GPIO::Direction::Output, GPIO::Pull::None, true), // Z Axis
        // GPIO::Pin(0, 3, GPIO::Direction::Output, GPIO::Pull::None, true)  // A Axis
    });

    // Define step direction output pins.
    constexpr static GPIO::Bus<N_AXIS> direction(0, {
        GPIO::Pin(0,  5, GPIO::Direction::Output, GPIO::Pull::None, true), // X Axis
        GPIO::Pin(0, 11, GPIO::Direction::Output, GPIO::Pull::None, true), // Y Axis
        GPIO::Pin(0, 20, GPIO::Direction::Output, GPIO::Pull::None, true), // Z Axis
        // GPIO::Pin(0, 22, GPIO::Direction::Output, GPIO::Pull::None, true)  // A Axis
    });

    // Define stepper driver enable/disable output pins.
    constexpr static GPIO::Bus<N_AXIS> enable(0, {
        GPIO::Pin(0,  4, GPIO::Direction::Output, GPIO::Pull::None, true), // X Axis
        GPIO::Pin(0, 10, GPIO::Direction::Output, GPIO::Pull::None, true), // Y Axis
        GPIO::Pin(0, 19, GPIO::Direction::Output, GPIO::Pull::None, true), // Z Axis
        // GPIO::Pin(0, 21, GPIO::Direction::Output, GPIO::Pull::None, true)  // A Axis
    });
}

// Define homing/hard limit switch input pins 
// NOTE: All limit bit pins must be on the same port
// NOTE: The order is crucial, must be XYZA!
constexpr static GPIO::Bus<N_AXIS * 2> limit(1, {
    GPIO::Pin(1, 24, GPIO::Direction::Input, GPIO::Pull::Up, false, true), // X Min
    GPIO::Pin(1, 25, GPIO::Direction::Input, GPIO::Pull::Up, false, true), // X Max

    GPIO::Pin(1, 26, GPIO::Direction::Input, GPIO::Pull::Up, false, true), // Y Min
    GPIO::Pin(1, 27, GPIO::Direction::Input, GPIO::Pull::Up, false, true), // Y Max

    GPIO::Pin(1, 28, GPIO::Direction::Input, GPIO::Pull::Up, false, true), // Z Min
    GPIO::Pin(1, 29, GPIO::Direction::Input, GPIO::Pull::Up, false, true)  // Z Max
}); 

// Define probe input pin
constexpr static GPIO::Pin probe(1, 30, GPIO::Direction::Input, GPIO::Pull::Up, true, true);

// Define spindle control output pins
namespace spindle {
    constexpr static GPIO::Pin enable(2, 7, GPIO::Direction::Output);
    constexpr static GPIO::Pin direction(1, 22, GPIO::Direction::Output);
}

// Define flood and mist coolant enable output pins.
namespace coolant {
    constexpr static GPIO::Pin flood(2, 22, GPIO::Direction::Output, GPIO::Pull::None);
    constexpr static GPIO::Pin mist(2, 6, GPIO::Direction::Output, GPIO::Pull::None);
}

}

#define STEP_DDR        LPC_GPIO2->FIODIR
#define STEP_PORT       LPC_GPIO2->FIOPIN
#define X_STEP_BIT      0
#define Y_STEP_BIT      1
#define Z_STEP_BIT      2
#define A_STEP_BIT      3
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<A_STEP_BIT)) // All step bits

#define DIRECTION_DDR     LPC_GPIO0->FIODIR
#define DIRECTION_PORT    LPC_GPIO0->FIOPIN
#define X_DIRECTION_BIT   5
#define Y_DIRECTION_BIT   11
#define Z_DIRECTION_BIT   20
#define A_DIRECTION_BIT   22
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)|(1<<A_DIRECTION_BIT)) // All direction bits

#define STEPPERS_DISABLE_DDR    LPC_GPIO0->FIODIR
#define STEPPERS_DISABLE_PORT   LPC_GPIO0->FIOPIN
#define X_DISABLE_BIT           4
#define Y_DISABLE_BIT           10
#define Z_DISABLE_BIT           19
#define A_DISABLE_BIT           21
#define STEPPERS_DISABLE_MASK   ((1<<X_DISABLE_BIT)|(1<<Y_DISABLE_BIT)|(1<<Z_DISABLE_BIT)|(1<<A_DISABLE_BIT))

// The LPC17xx has 6 PWM channels. Each channel has 2 pins. It can drive both pins simultaneously to the same value.
//
// PWM Channel      PWM1_CH1  PWM1_CH2  PWM1_CH3  PWM1_CH4  PWM1_CH5  PWM1_CH6
// Primary pin      P1.18     P1.20     P1.21     P1.23     P1.24     P1.26
// Secondary pin    P2.0      P2.1      P2.2      P2.3      P2.4      P2.5
#define SPINDLE_PWM_CHANNEL           PWM1_CH6    // BED MOSFET (P2.5)
#define SPINDLE_PWM_USE_PRIMARY_PIN   false
#define SPINDLE_PWM_USE_SECONDARY_PIN true

// #define ENABLE_M7           // enables COOLANT MIST

// Define user-control controls (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_DDR       LPC_GPIO1->FIODIR
#define CONTROL_PIN       LPC_GPIO1->FIOPIN
#define CONTROL_PORT      LPC_GPIO1->FIOPIN
#define CONTROL_RESET_BIT         NotUsed  // Not needed as there is a special RESET pin on the Smoothiebaord
#define CONTROL_FEED_HOLD_BIT     22  // P1.22
#define CONTROL_CYCLE_START_BIT   23  // P1.23
#define CONTROL_SAFETY_DOOR_BIT   22  // P1.22 NOTE: Safety door is shared with feed hold. Enabled by config define.
#define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT1_vect
#define CONTROL_PCMSK     NotUsed // Pin change interrupt register
#define CONTROL_MASK      ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK   CONTROL_MASK // May be re-defined to only invert certain control pins.

// Stepper current control
#define CURRENT_I2C Driver_I2C1       // I2C driver for current control. Comment out to disable (for C3d boards!)
#define CURRENT_MCP44XX_ADDR 0b0101100  // Address of MCP44XX
#define CURRENT_WIPERS {0, 1, 6, 7};    // Wiper registers (X, Y, Z, A)
#define CURRENT_FACTOR 113.33           // Convert amps to digipot value

// Variable spindle configuration below. Do not change unless you know what you are doing.
// NOTE: Only used when variable spindle is enabled.
#define SPINDLE_PWM_MAX_VALUE     255 // Don't change. 328p fast PWM mode fixes top value as 255.
#ifndef SPINDLE_PWM_MIN_VALUE
  #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
#endif

