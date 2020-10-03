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
#include <cassert>
#include <array>

namespace GPIO {

enum struct Direction : uint32_t {
    Input, Output
};

enum struct Pull : uint32_t {
    Up, None, Down
};

struct Pin {
    uint32_t port;
    uint32_t index;
    uint32_t mask;

    struct Config {
        Direction direction;
        Pull pull;
        bool open_drain;
        uint32_t init_val;
    } config;

    constexpr Pin(uint32_t port, uint32_t index,
        Direction direction = Direction::Input,
        Pull pull = Pull::Up,
        bool open_drain = false,
        uint32_t init_val = 0UL
    )
        : port(port)
        , index(index)
        , mask(1 << index)
        , config({
            direction, pull,
            open_drain, init_val
        })
    {}

    void init() const;

    void set_pull(Pull pull) const;
    void set_direction(Direction direction) const;
    void set_open_drain(bool enabled) const;

    uint32_t get() const;
    void set(uint32_t value) const;
    void toggle() const;

    const Pin& operator=(uint32_t value) const;
    operator uint32_t() const;
};

namespace Detail {
    struct Bus {
        uint32_t mask;
        uint32_t port;

        void write(uint32_t value) const;
        uint32_t read() const;

        const Bus& operator=(uint32_t value) const;
        operator uint32_t() const;
    };
}

template<std::size_t N>
struct Bus : Detail::Bus {
    static_assert(N <= 32);
    std::array<Pin, N> pins;

    constexpr Bus(uint32_t port, std::array<Pin, N> pins)
        : Detail::Bus{0, port}
        , pins(pins)
    {
        for (auto& pin : pins) {
            assert(port == pin.port);
            mask |= pin.mask;
        }
    }

    void init() const {
        for (auto& pin : pins) {
            pin.init();
        }
    }
};

}