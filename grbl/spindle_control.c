/*
  spindle_control.c - spindle control methods
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2020      Roy van Dam

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
#include "pwm_driver.h"

using namespace board;

#ifdef INVERT_SPINDLE_ENABLE_PIN
const static bool invert_spindle_enable = true;
#else
const static bool invert_spindle_enable = false;
#endif

#ifdef VARIABLE_SPINDLE
  static float pwm_gradient; // Precalculated value to speed up rpm to PWM conversions.
  float spindle_pwm_period;
  float spindle_pwm_off_value;
  float spindle_pwm_min_value;
  float spindle_pwm_max_value;
#endif

void spindle_init() {
  spindle::enable.init();
  spindle::direction.init();

  #ifdef VARIABLE_SPINDLE
    spindle_pwm_period = (SystemCoreClock / settings.spindle_pwm_freq);
    spindle_pwm_off_value = (spindle_pwm_period * settings.spindle_pwm_off_value / 100);
    spindle_pwm_min_value = (spindle_pwm_period * settings.spindle_pwm_min_value / 100);
    spindle_pwm_max_value = (spindle_pwm_period * settings.spindle_pwm_max_value / 100);
    pwm_init(&SPINDLE_PWM_CHANNEL, SPINDLE_PWM_USE_PRIMARY_PIN, SPINDLE_PWM_USE_SECONDARY_PIN, spindle_pwm_period, 0);
    pwm_enable(&SPINDLE_PWM_CHANNEL);

    pwm_gradient = (spindle_pwm_max_value-spindle_pwm_min_value)/(settings.rpm_max-settings.rpm_min);
  #endif

  spindle_stop();
}

bool spindle_get_enabled() {
	#ifdef VARIABLE_SPINDLE
    // TODO(roda): use PWM driver instead of enable pin
    // Check if PWM is enabled
    return (spindle::enable.get() ^ invert_spindle_enable);
  #else
    return (spindle::enable.get() ^ invert_spindle_enable);
  #endif
}

uint8_t spindle_get_direction() {
  return spindle::direction.get() ? SPINDLE_STATE_CCW : SPINDLE_STATE_CW;
}

uint8_t spindle_get_state()
{
  return spindle_get_enabled()
    ? spindle_get_direction()
    : SPINDLE_STATE_DISABLE;
}


// Disables the spindle and sets PWM output to zero when PWM variable spindle speed is enabled.
// Called by various main program and ISR routines. Keep routine small, fast, and efficient.
// Called by spindle_init(), spindle_set_speed(), spindle_set_state(), and mc_reset().
void spindle_stop()
{
  #ifdef VARIABLE_SPINDLE
    pwm_set_width(&SPINDLE_PWM_CHANNEL, 0);
  #endif
  spindle::enable.set(false ^ invert_spindle_enable);
}

#ifdef VARIABLE_SPINDLE
  // Sets spindle speed PWM output and enable pin, if configured. Called by spindle_set_state()
  // and stepper ISR. Keep routine small and efficient.
  void spindle_set_speed(uint32_t pwm_value) {
    pwm_set_width(&SPINDLE_PWM_CHANNEL, pwm_value);
  }

  // Called by spindle_set_state() and step segment generator. Keep routine small and efficient.
  uint32_t spindle_compute_pwm_value(float rpm) {
    uint32_t pwm_value;
    rpm *= (0.010*sys.spindle_speed_ovr); // Scale by spindle speed override value.
    if (rpm <= 0) {
      sys.spindle_speed = 0;
      pwm_value = spindle_pwm_off_value;
    }
    else if (rpm <= settings.rpm_min) {
      sys.spindle_speed = settings.rpm_min;
      pwm_value = spindle_pwm_min_value;
    }
    else if (rpm >= settings.rpm_max) {
      sys.spindle_speed = settings.rpm_max;
      pwm_value = spindle_pwm_max_value - 1;
    }
    else {
      sys.spindle_speed = rpm;
      pwm_value = floor((rpm - settings.rpm_min) * pwm_gradient) + spindle_pwm_min_value;
      if(pwm_value >= spindle_pwm_max_value)
        pwm_value = spindle_pwm_max_value - 1;
    }
    return(pwm_value);
  }
#endif


// Immediately sets spindle running state with direction and spindle rpm via PWM, if enabled.
// Called by g-code parser spindle_sync(), parking retract and restore, g-code program end,
// sleep, and spindle stop override.
#ifdef VARIABLE_SPINDLE
  void spindle_set_state(uint8_t state, float rpm)
#else
  void _spindle_set_state(uint8_t state)
#endif
{
  // Block during abort.
  if (sys.abort) {
    return;
  }

  switch (state) {
    case SPINDLE_DISABLE:
      spindle_stop();
#ifdef VARIABLE_SPINDLE
      sys.spindle_speed = 0.0;
#endif
      break;
    
    case SPINDLE_STATE_CW:
    case SPINDLE_STATE_CCW:
#ifdef VARIABLE_SPINDLE
      // NOTE: Assumes all calls to this function is when Grbl is not moving or must remain off.
      if (settings.flags & BITFLAG_LASER_MODE) { 
        if (state == SPINDLE_ENABLE_CCW) { rpm = 0.0; } // TODO: May need to be rpm_min*(100/MAX_SPINDLE_SPEED_OVERRIDE);
      }
      spindle_set_speed(spindle_compute_pwm_value(rpm));
#endif

      spindle::direction = (state == SPINDLE_ENABLE_CCW);
      spindle::enable = true ^ invert_spindle_enable;
      leds[0] = true;
      break;
  }
  
  sys.report_ovr_counter = 0; // Set to report change immediately
}


// G-code parser entry-point for setting spindle state. Forces a planner buffer sync and bails 
// if an abort or check-mode is active.
#ifdef VARIABLE_SPINDLE
  void spindle_sync(uint8_t state, float rpm)
  {
    if (sys.state == STATE_CHECK_MODE) { return; }
    protocol_buffer_synchronize(); // Empty planner buffer to ensure spindle is set when programmed.
    spindle_set_state(state,rpm);
  }
#else
  void _spindle_sync(uint8_t state)
  {
    if (sys.state == STATE_CHECK_MODE) { return; }
    protocol_buffer_synchronize(); // Empty planner buffer to ensure spindle is set when programmed.
    _spindle_set_state(state);
  }
#endif
