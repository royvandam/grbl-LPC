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

#include "LPC17xx.h"

#define LPC_GPIO(port)            ((LPC_GPIO_TypeDef *)(LPC_GPIO0_BASE + (0x00020 * port)))

#define LPC_REG_OFFSET(port, pin) ((2 * port) + (pin >= 16))
#define LPC_PIN_OFFSET(pin)       (pin - (16 * (pin >= 16)))

#define LPC_PINSEL(port, pin)     (*((volatile uint32_t *) (&(LPC_PINCON->PINSEL0)     + LPC_REG_OFFSET(port, pin))))
#define LPC_PINMODE(port, pin)    (*((volatile uint32_t *) (&(LPC_PINCON->PINMODE0)    + LPC_REG_OFFSET(port, pin))))
#define LPC_PINMODE_OD(port)      (*((volatile uint32_t *) (&(LPC_PINCON->PINMODE_OD0) + port)))

// LPC pin modes
#define LPC_PINMODE_PULLUP   ((uint32_t)(0))
#define LPC_PINMODE_REPEATER ((uint32_t)(1))
#define LPC_PINMODE_TRISTATE ((uint32_t)(2))
#define LPC_PINMODE_PULLDOWN ((uint32_t)(3))

namespace GPIO {

void Pin::init() const {
    // Reset pin function to GPIO
    LPC_PINSEL(port, index) &= ~(0x03UL << (LPC_PIN_OFFSET(index) * 2));

    // Configure pull, open-drain and direction
    set_pull(config.pull);
    set_open_drain(config.open_drain);
    set_direction(config.direction);

    set(config.init_val);
}

void Pin::set_pull(Pull pull) const {
    LPC_PINMODE(port, index) &= ~(0x03UL << (LPC_PIN_OFFSET(index) * 2));
    switch (config.pull) {
        case Pull::Up:
            LPC_PINMODE(port, index) |= LPC_PINMODE_PULLUP << (LPC_PIN_OFFSET(index) * 2);
            break;
        case Pull::None:
            LPC_PINMODE(port, index) |= LPC_PINMODE_TRISTATE << (LPC_PIN_OFFSET(index) * 2);
            break;
        case Pull::Down:
            LPC_PINMODE(port, index) |= LPC_PINMODE_PULLDOWN << (LPC_PIN_OFFSET(index) * 2);
            break;
    }
};

void Pin::set_direction(Direction direction) const {
    LPC_GPIO(port)->FIODIR = (direction == Direction::Input)
        ? LPC_GPIO(port)->FIODIR | mask
        : LPC_GPIO(port)->FIODIR & ~mask;
};

void Pin::set_open_drain(bool enabled) const {
    enabled
        ? LPC_PINMODE_OD(port) |= mask
        : LPC_PINMODE_OD(port) &= ~mask;
}

uint32_t Pin::get() const {
    return LPC_GPIO(port)->FIOPIN & mask;
}

void Pin::set(uint32_t value) const {
    value
        ? LPC_GPIO(port)->FIOSET = mask
        : LPC_GPIO(port)->FIOCLR = mask;
}

void Pin::toggle() const {
    (LPC_GPIO(port)->FIOPIN & mask)
        ? LPC_GPIO(port)->FIOCLR = mask
        : LPC_GPIO(port)->FIOSET = mask;
}

const Pin& Pin::operator=(uint32_t value) const {
    set(value);
    return *this;
}

Pin::operator uint32_t() const {
    return get();
}

namespace Detail {

void Bus::write(uint32_t value) const {
    // Naive non-atomic implementation 
    // uint32_t temp = gpio_port_0 | (mask & value);
    // gpio_port_0 = temp & (~mask | value);

    // The LCP however supports a masked write to the port...
    LPC_GPIO(port)->FIOMASK = ~mask;
    LPC_GPIO(port)->FIOPIN |= value;
    LPC_GPIO(port)->FIOMASK = 0;
}

uint32_t Bus::read() const {
    return LPC_GPIO(port)->FIOPIN & mask;
}

const Bus& Bus::operator=(uint32_t value) const {
    write(value);
    return *this;
}

Bus::operator uint32_t() const {
    return read();
}

} // namespace Detail
} // namespace GPIO