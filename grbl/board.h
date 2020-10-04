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
    // GPIO::Pin(1, 18, GPIO::Direction::Output), // 1.18 Unavailable used by USB driver
    GPIO::Pin(1, 19, GPIO::Direction::Output),
    GPIO::Pin(1, 20, GPIO::Direction::Output),
    GPIO::Pin(1, 21, GPIO::Direction::Output)
};

// Define step related pins.
// NOTE: All pins within a bus must be on the same port.
// NOTE: The order is crucial, must be XYZA!
namespace step {
    // Define step output pins. 
    constexpr static GPIO::Bus<N_AXIS> step(2, {
        GPIO::Pin(2, 0, GPIO::Direction::Output, GPIO::Pull::None, true, true), // X Axis
        GPIO::Pin(2, 1, GPIO::Direction::Output, GPIO::Pull::None, true, true), // Y Axis
        GPIO::Pin(2, 2, GPIO::Direction::Output, GPIO::Pull::None, true, true), // Z Axis
        // GPIO::Pin(0, 3, GPIO::Direction::Output, GPIO::Pull::None, true, true)  // A Axis
    });

    // Define stepper driver enable/disable output pins.
    constexpr static GPIO::Bus<N_AXIS> enable(0, {
        GPIO::Pin(0,  4, GPIO::Direction::Output, GPIO::Pull::None, false, true), // X Axis
        GPIO::Pin(0, 10, GPIO::Direction::Output, GPIO::Pull::None, false, true), // Y Axis
        GPIO::Pin(0, 19, GPIO::Direction::Output, GPIO::Pull::None, false, true), // Z Axis
        // GPIO::Pin(0, 21, GPIO::Direction::Output, GPIO::Pull::None, true, true)  // A Axis
    });

    // Define step direction output pins.
    constexpr static GPIO::Bus<N_AXIS> direction(0, {
        GPIO::Pin(0,  5, GPIO::Direction::Output, GPIO::Pull::None, true, true), // X Axis
        GPIO::Pin(0, 11, GPIO::Direction::Output, GPIO::Pull::None, true, true), // Y Axis
        GPIO::Pin(0, 20, GPIO::Direction::Output, GPIO::Pull::None, true, true), // Z Axis
        // GPIO::Pin(0, 22, GPIO::Direction::Output, GPIO::Pull::None, true, true)  // A Axis
    });
}

// Define homing/hard limit switch input pins 
// NOTE: All limit bit pins must be on the same port
// NOTE: The order is crucial, must be XYZA!
constexpr static GPIO::Bus<N_AXIS * 2> limit(1, {
    GPIO::Pin(1, 24, GPIO::Direction::Input, GPIO::Pull::Up, true), // X Min
    GPIO::Pin(1, 25, GPIO::Direction::Input, GPIO::Pull::Up, true), // X Max

    GPIO::Pin(1, 26, GPIO::Direction::Input, GPIO::Pull::Up, true), // Y Min
    GPIO::Pin(1, 27, GPIO::Direction::Input, GPIO::Pull::Up, true), // Y Max

    GPIO::Pin(1, 28, GPIO::Direction::Input, GPIO::Pull::Up, true), // Z Min
    GPIO::Pin(1, 29, GPIO::Direction::Input, GPIO::Pull::Up, true)  // Z Max
}); 

// Define probe input pin
constexpr static GPIO::Pin probe(0, 27, GPIO::Direction::Input, GPIO::Pull::Up, true);

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

namespace control {
    constexpr static GPIO::Pin feed_hold(3, 28, GPIO::Direction::Input, GPIO::Pull::Up, true);
    constexpr static GPIO::Pin cycle_start(3, 29, GPIO::Direction::Input, GPIO::Pull::Up, true);
}

}

// The LPC17xx has 6 PWM channels. Each channel has 2 pins. It can drive both pins simultaneously to the same value.
//
// PWM Channel      PWM1_CH1  PWM1_CH2  PWM1_CH3  PWM1_CH4  PWM1_CH5  PWM1_CH6
// Primary pin      P1.18     P1.20     P1.21     P1.23     P1.24     P1.26
// Secondary pin    P2.0      P2.1      P2.2      P2.3      P2.4      P2.5
#define SPINDLE_PWM_CHANNEL           PWM1_CH6    // BED MOSFET (P2.5)
#define SPINDLE_PWM_USE_PRIMARY_PIN   false
#define SPINDLE_PWM_USE_SECONDARY_PIN true

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

