/*
  coolant_control.c - coolant control methods
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2020 Roy van Dam

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"

#ifdef INVERT_COOLANT_FLOOD_PIN
constexpr static bool invert_flood_pin = true;
#else
constexpr static bool invert_flood_pin = false;
#endif

#ifdef INVERT_COOLANT_MIST_PIN
constexpr static bool invert_mist_pin = true;
#else
constexpr static bool invert_mist_pin = false;
#endif

using namespace board;

void coolant_init() {
    coolant::flood.init(); 
#ifdef ENABLE_M7
    coolant::mist.init();
#endif

    coolant_stop();
}

// Returns current coolant output state. Overrides may alter it from programmed state.
uint8_t
coolant_get_state() {
    uint8_t cl_state = COOLANT_STATE_DISABLE;

    if (coolant::flood.get() ^ invert_flood_pin) {
        cl_state |= COOLANT_STATE_FLOOD;
    }

#ifdef ENABLE_M7
    if (coolant::mist.get() ^ invert_mist_pin) {
        cl_state |= COOLANT_STATE_MIST;
    }
#endif

    return (cl_state);
}

// Directly called by coolant_init(), coolant_set_state(), and mc_reset(), which can be at
// an interrupt-level. No report flag set, but only called by routines that don't need it.
void coolant_stop() {
    coolant::flood.set(false ^ invert_flood_pin);
#ifdef ENABLE_M7
    coolant::mist.set(false ^ invert_mist_pin);
#endif
}

// Main program only. Immediately sets flood coolant running state and also mist coolant,
// if enabled. Also sets a flag to report an update to a coolant state.
// Called by coolant toggle override, parking restore, parking retract, sleep mode, g-code
// parser program end, and g-code parser coolant_sync().
void coolant_set_state(uint8_t mode) {
    // Block during abort.
    if (sys.abort) {
        return;
    }  

    if (mode == COOLANT_DISABLE) {
        coolant_stop();
    } else {
        if (mode & COOLANT_FLOOD_ENABLE) {
            coolant::flood.set(true ^ invert_flood_pin);
        }

#ifdef ENABLE_M7
        if (mode & COOLANT_MIST_ENABLE) {
            coolant::mist.set(true ^ invert_mist_pin);
        }
#endif
    }

    // Set to report change immediately
    sys.report_ovr_counter = 0;  
}

// G-code parser entry-point for setting coolant state. Forces a planner buffer sync and bails
// if an abort or check-mode is active.
void
coolant_sync(uint8_t mode) {
    if (sys.state == STATE_CHECK_MODE) {
        return;
    }
    // Ensure coolant turns on when specified in program.
    protocol_buffer_synchronize();
    coolant_set_state(mode);
}
