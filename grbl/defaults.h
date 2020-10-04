/*
  defaults.h - defaults settings configuration file
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

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

/* The defaults.h file serves as a central default settings selector for different machine
   types, from DIY CNC mills to CNC conversions of off-the-shelf machines. The settings
   files listed here are supplied by users, so your results may vary. However, this should
   give you a good starting point as you get to know your machine and tweak the settings for
   your nefarious needs.
   NOTE: Ensure one and only one of these DEFAULTS_XXX values is defined in config.h */

#ifndef defaults_h

#ifdef DEFAULTS_GENERIC
  // Grbl generic default settings. Should work across different machines.
  // See https://github.com/gnea/grbl/wiki/Grbl-v1.1-Configuration for setting descriptions.
  #define DEFAULT_X_STEPS_PER_MM 26.64       // $100 steps (X steps per mm)
  #define DEFAULT_Y_STEPS_PER_MM 26.64       // $101 steps (Y steps per mm)
  #define DEFAULT_Z_STEPS_PER_MM 200         // $102 steps (Z steps per mm)
  #define DEFAULT_A_STEPS_PER_MM 160.0       // $103 steps (A steps per mm)
  #define DEFAULT_X_MAX_RATE 20000.0           // $110 mm/min (X max speed)
  #define DEFAULT_Y_MAX_RATE 20000.0           // $111 mm/min (Y max speed)
  #define DEFAULT_Z_MAX_RATE 1000.0           // $112 mm/min (Z max speed)
  #define DEFAULT_A_MAX_RATE 500.0           // $113 mm/min (A max speed)
  #define DEFAULT_X_ACCELERATION (250.0*60*60)         // $120 mm/min^2 (X max acceleration)
  #define DEFAULT_Y_ACCELERATION (250.0*60*60)        // $121 mm/min^2 (Y max acceleration)
  #define DEFAULT_Z_ACCELERATION (50.0*60*60)          // $122 mm/min^2 (Z max acceleration)
  #define DEFAULT_A_ACCELERATION (10.0*60*60)// $123 mm/min^2 (A max acceleration)
  #define DEFAULT_X_MAX_TRAVEL 3000.0         // $130 mm (X max travel; must be positive)
  #define DEFAULT_Y_MAX_TRAVEL 3000.0         // $131 mm (Y max travel; must be positive)
  #define DEFAULT_Z_MAX_TRAVEL 150.0         // $132 mm (Z max travel; must be positive)
  #define DEFAULT_A_MAX_TRAVEL 1.0           // $133 mm (A max travel; must be positive)
  #define DEFAULT_X_CURRENT 0.6              // $140 amps (X stepper current [disabled])
  #define DEFAULT_Y_CURRENT 0.6              // $141 amps (Y stepper current [disabled])
  #define DEFAULT_Z_CURRENT 0.0              // $142 amps (Z stepper current [disabled])
  #define DEFAULT_A_CURRENT 0.0              // $143 amps (A stepper current [disabled])

  #define DEFAULT_STEP_PULSE_MICROSECONDS 10 // $0  usec (stepper pulse time)
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255 // $1  msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 0       // $10 bits (Reports: [0=WPos or 1=MPos] and [2=Buffer])
  #define DEFAULT_JUNCTION_DEVIATION 0.01    // $11 mm (determines machine speed through corners)
  #define DEFAULT_ARC_TOLERANCE 0.002        // $12 mm (error tolerance on arcs/cicles)
  #define DEFAULT_REPORT_INCHES 0            // $13 bool (sets position reporting to inches)
  #define DEFAULT_SOFT_LIMIT_ENABLE 0        // $20 bool (prevents moves outside *_MAX_TRAVEL; requires $23=1)
  #define DEFAULT_HARD_LIMIT_ENABLE 0        // $21 bool ([ignored] stops moving when limit switches triggered)
  #define DEFAULT_HOMING_ENABLE 0            // $22 bool (enables homing on startup)
  #define DEFAULT_HOMING_DIR_MASK 0          // $23 ZYX (e.g., 0x3 reverses XY homing to negative direction)
  #define DEFAULT_HOMING_FEED_RATE 25.0      // $24 mm/min (homing precision location speed)
  #define DEFAULT_HOMING_SEEK_RATE 500.0     // $25 mm/min (homing search speed)
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250  // $26 msec (homing switch debounce: 0-65k)
  #define DEFAULT_HOMING_PULLOFF 5.0         // $27 mm (retracts this far from homing switch)
  #define DEFAULT_SPINDLE_RPM_MAX 24000.0    // $30 RPM (spindle speed for max 5V PWM output)
  #define DEFAULT_SPINDLE_RPM_MIN 2500.0     // $31 RPM (spindle speed for min 20mV PWM output)
  #define DEFAULT_LASER_MODE 0               // $32 bool (adjusts spindle power with speed for lasers)
  #define DEFAULT_SPINDLE_PWM_FREQ 5000      // $33 Hz (PWM frequency for spindle)
  #define DEFAULT_SPINDLE_PWM_OFF_VALUE 1    // $34 % (% of PWM when spindle is off)
  #define DEFAULT_SPINDLE_PWM_MIN_VALUE 1    // $35 % (% of PWM when spindle is at lowest setting)
  #define DEFAULT_SPINDLE_PWM_MAX_VALUE 100  // $36 % (% of PWM when spindle is at highest setting)
#endif // end of DEFAULTS_GENERIC

#endif
