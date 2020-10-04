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
    uint8_t port;
    uint8_t index;
    uint32_t mask;

    struct Config {
        Direction direction;
        Pull pull;
        bool open_drain;
        bool inverted;
        uint32_t value;
    } config;

    /**
     * @brief Constexpr constructor allowing to define a pin and its
     * configuration during compile-time.
     * @param port Port number
     * @param index Pin number
     * @param direction Pin direction {Input, Output}
     * @param pull Pin pull mode {None Up, Down}
     * @param open_drain Configure pin as open-drain output
     * @param inverted Set pin logical state as inverted
     * @param value Initial configuration value
     */
    constexpr Pin(uint8_t port, uint8_t index,
        Direction direction = Direction::Input,
        Pull pull = Pull::Up,
        bool open_drain = false,
        bool inverted = false,
        uint32_t value = 0UL
    )
        : port(port)
        , index(index)
        , mask(1 << index)
        , config({
            direction, pull,
            open_drain, inverted,
            value
        })
    {}

    /**
     * @brief Runtime initialisation of the pin based on the compile-time
     * defined configuration
     */
    void init() const;

    /**
     * @brief Runtime configuration of the pin pull mode.
     * NOTE: The compile-time defined configuration is not updated.
     * @param pull Pin pull mode {None Up, Down}
     */
    void set_pull(Pull pull) const;

    /**
     * @brief Runtime configuration of the pin direction.
     * NOTE: The compile-time defined configuration is not updated.
     * @param direction Pin direction {Input, Output}
     */
    void set_direction(Direction direction) const;

    /**
     * @brief Runtime configuration of the pin open drain mode.
     * NOTE: The compile-time defined configuration is not updated.
     * @param open_drain Configure pin as open-drain output
     */
    void set_open_drain(bool enabled) const;

    /**
     * @brief Returns the logical state of the pin.
     * @return Pin logical state
     */
    uint32_t get() const;

    /**
     * @brief Set logical state of the pin.
     * @param value Pin logical state
     */
    void set(uint32_t value) const;

    /**
     * @brief Invert the current logical state of the pin
     */
    void toggle() const;

    /**
     * @brief Returns the logical state of the pin.
     * @return Pin logical state
     */
    operator uint32_t() const;

    /**
     * @brief Set logical state of the pin.
     * @param value Pin logical state
     */
    const Pin& operator=(uint32_t value) const;
};

namespace Detail {
    struct Bus {
        uint8_t port;
        uint32_t mask;
        uint32_t invert_mask;

        /**
         * @brief Returns the logical state of the pins in the bus.
         * @return Bus logical state
         */
        uint32_t read() const;

        /**
         * @brief Returns the logical state of the pins in the bus.
         * @return Bus logical state
         */
        operator uint32_t() const;

        /**
         * @brief Set logical state of the pins in the bus.
         * @param value Bus logical state
         */
        void write(uint32_t value) const;

        /**
         * @brief Set logical state of the pins in the bus.
         * @param value Bus logical state
         */
        const Bus& operator=(uint32_t value) const;
    };
}

template<std::size_t N>
struct Bus : Detail::Bus {
    static_assert(N <= 32);
    std::array<Pin, N> pins;

    /**
     * @brief Constexpr constructor allowing to define a bus and its
     * configuration during compile-time.
     * @param port Port number
     * @param pins Initializer list of constexpr pin instances.
     */
    constexpr Bus(uint8_t port, std::array<Pin, N> pins)
        : Detail::Bus{port, 0, 0}
        , pins(pins)
    {
        for (auto& pin : pins) {
            assert(port == pin.port);
            mask |= pin.mask;
            invert_mask |= pin.config.inverted
                ? pin.mask : 0;
        }
    }

    /**
     * @brief Runtime initialisation of the bus and its pins based on the
     * compile-time defined configuration
     */
    void init() const {
        for (auto& pin : pins) {
            pin.init();
        }
    }
};

}