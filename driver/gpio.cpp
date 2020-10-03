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

extern "C" {
    #include <PIN_LPC17xx.h>
    #include <GPIO_LPC17xx.h>
}

namespace GPIO {

void Pin::init() const
{
    uint8_t pull_value = 0;
    switch (pull) {
        case Pull::None:
            pull_value = PIN_PINMODE_TRISTATE;
            break;
        case Pull::Up:
            pull_value = PIN_PINMODE_PULLUP;
            break;
        case Pull::Down:
            pull_value = PIN_PINMODE_PULLDOWN;
            break;
    }

    uint8_t open_drain_value = open_drain
        ? PIN_PINMODE_OPENDRAIN
        : PIN_PINMODE_NORMAL;

    PIN_Configure(port, number, 0, pull_value, open_drain_value);

    switch (direction) {
        case Direction::Input:
            GPIO_SetDir(port, number, GPIO_DIR_INPUT);
            break;
        case Direction::Output:
            GPIO_SetDir(port, number, GPIO_DIR_OUTPUT);
            break;
    }

    set(initial);
}

bool Pin::get() const {
    return GPIO_PinRead(port, number);
}

void Pin::set(bool value) const {
    GPIO_PinWrite(port, number, value);
}

void Pin::toggle() const {
    set(!get());
}

const Pin& Pin::operator=(bool value) const {
    set(value);
    return *this;
}

Pin::operator bool() const {
    return get();
}

}