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

#include <cstdint>

namespace GPIO {

enum struct Direction {
    Input, Output
};

enum struct Pull {
    None, Up, Down
};

struct Pin {
    uint8_t port;
    uint8_t number;
    Direction direction;
    Pull pull;
    bool open_drain;
    bool initial;

    void init() const;

    bool get() const;
    void set(bool value) const;
    void toggle() const;

    const Pin& operator=(bool value) const;
    operator bool() const;
};

constexpr Pin static Configure(
    uint8_t port, uint8_t number,
    Direction direction = Direction::Input,
    Pull pull = Pull::Up,
    bool open_drain = false,
    bool initial = false)
{
    return Pin {
        .port = port,
        .number = number,
        .direction = direction,
        .pull = pull,
        .open_drain = open_drain,
        .initial = initial
    };
}

}