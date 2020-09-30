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
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255  // $1  msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STEPPING_INVERT_MASK 7     // $2  ZYX (e.g., 0x5 inverts Z and X stepper pulses)
  #define DEFAULT_DIRECTION_INVERT_MASK 7    // $3  ZYX (e.g., 0x2 inverts Y stepper direction)
  #define DEFAULT_INVERT_ST_ENABLE 1         // $4  bool (inverts stepper enable pin)
  #define DEFAULT_INVERT_LIMIT_PINS 1        // $5  bool (inverts limit switches to trigger on high)
  #define DEFAULT_INVERT_PROBE_PIN 1         // $6  bool (inverts probe to trigger on high)
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
  #define DEFAULT_SPINDLE_RPM_MAX 24000.0     // $30 RPM (spindle speed for max 5V PWM output)
  #define DEFAULT_SPINDLE_RPM_MIN 2500.0     // $31 RPM (spindle speed for min 20mV PWM output)
  #define DEFAULT_LASER_MODE 0               // $32 bool (adjusts spindle power with speed for lasers)
  #define DEFAULT_SPINDLE_PWM_FREQ 5000      // $33 Hz (PWM frequency for spindle)
  #define DEFAULT_SPINDLE_PWM_OFF_VALUE 1    // $34 % (% of PWM when spindle is off)
  #define DEFAULT_SPINDLE_PWM_MIN_VALUE 1    // $35 % (% of PWM when spindle is at lowest setting)
  #define DEFAULT_SPINDLE_PWM_MAX_VALUE 100  // $36 % (% of PWM when spindle is at highest setting)
  // Up to 4 HOMING_CYCLE_x can be defined (0-3), specifying which axes are homed and in which order
  #define HOMING_CYCLE_0 ((1<<X_AXIS)|(1<<Y_AXIS))
#endif // end of DEFAULTS_GENERIC

#ifdef DEFAULTS_K40
  // Description: K40 Lasercutter (typical chinese 40W CO2 laser cutter/engraver)
  #define DEFAULT_X_STEPS_PER_MM 160.0      // 200 stepps/rev. * 32 microstepps / 40mm/rev
  #define DEFAULT_Y_STEPS_PER_MM 160.0
  #define DEFAULT_Z_STEPS_PER_MM 160.0
  #define DEFAULT_A_STEPS_PER_MM 160.0
  #define DEFAULT_X_MAX_RATE 24000.0        // mm/min
  #define DEFAULT_Y_MAX_RATE 24000.0        // mm/min
  #define DEFAULT_Z_MAX_RATE 24000.0        // mm/min
  #define DEFAULT_A_MAX_RATE 24000.0        // mm/min
  #define DEFAULT_X_ACCELERATION (2500.0*60*60) // 2500*60*60 mm/min^2 = 2500 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (2500.0*60*60) // 2500*60*60 mm/min^2 = 2500 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (2500.0*60*60) // 2500*60*60 mm/min^2 = 2500 mm/sec^2
  #define DEFAULT_A_ACCELERATION (2500.0*60*60) // 2500*60*60 mm/min^2 = 2500 mm/sec^2
  #define DEFAULT_X_CURRENT 0.6             // amps
  #define DEFAULT_Y_CURRENT 0.6             // amps
  #define DEFAULT_Z_CURRENT 0.0             // amps
  #define DEFAULT_A_CURRENT 0.0             // amps
  #define DEFAULT_X_MAX_TRAVEL 300.0        // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 200.0        // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 50.0         // mm NOTE: Must be a positive value.
  #define DEFAULT_A_MAX_TRAVEL 100.0        // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000     // Hz (2000 - 20000)
  #define DEFAULT_SPINDLE_PWM_OFF_VALUE 0   // %
  #define DEFAULT_SPINDLE_PWM_MIN_VALUE 1   // %
  #define DEFAULT_SPINDLE_PWM_MAX_VALUE 100 // %
  #define DEFAULT_SPINDLE_RPM_MAX 1000.0    // rpm (S-value)
  #define DEFAULT_SPINDLE_RPM_MIN 0.0       // rpm (S-value)
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK 3   // 3 = invert X+Y
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255// msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 0      // WPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.01   // mm
  #define DEFAULT_ARC_TOLERANCE 0.002       // mm
  #define DEFAULT_REPORT_INCHES 0           // false
  #define DEFAULT_INVERT_ST_ENABLE 0        // false
  #define DEFAULT_INVERT_LIMIT_PINS 1       // true for microswitches / false for optical sensors
  #define DEFAULT_SOFT_LIMIT_ENABLE 1       // true
  #define DEFAULT_HARD_LIMIT_ENABLE 0       // false
  #define DEFAULT_INVERT_PROBE_PIN 0        // false
  #define DEFAULT_LASER_MODE 1              // true
  #define DEFAULT_HOMING_ENABLE 1           // true
  #define DEFAULT_HOMING_DIR_MASK 1         // move top/left
  #define DEFAULT_HOMING_FEED_RATE 50.0     // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 6000.0   // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 2.0        // mm
  #define HOMING_CYCLE_0 ((1<<X_AXIS)|(1<<Y_AXIS))
#endif // end of DEFAULTS_K40

#ifdef DEFAULTS_FABKIT
  // Paste default settings definitions here.
  #define DEFAULT_X_STEPS_PER_MM 80.0
  #define DEFAULT_Y_STEPS_PER_MM 80.0
  #define DEFAULT_Z_STEPS_PER_MM 640.0
  #define DEFAULT_A_STEPS_PER_MM 160.0
  #define DEFAULT_X_MAX_RATE 30000          // mm/min
  #define DEFAULT_Y_MAX_RATE 4500           // mm/min
  #define DEFAULT_Z_MAX_RATE 1200           // mm/min
  #define DEFAULT_A_MAX_RATE 24000.0        // mm/min
  #define DEFAULT_X_ACCELERATION (4000.0*60*60) // 4000*60*60 mm/min^2 = 4000 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (250.0*60*60)  // 250*60*60 mm/min^2 = 250 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (150.0*60*60)  // 150*60*60 mm/min^2 = 150 mm/sec^2
  #define DEFAULT_A_ACCELERATION (150.0*60*60)  // 150*60*60 mm/min^2 = 150 mm/sec^2
  #define DEFAULT_X_CURRENT 1.5             // amps
  #define DEFAULT_Y_CURRENT 1.5             // amps
  #define DEFAULT_Z_CURRENT 1.5             // amps
  #define DEFAULT_A_CURRENT 0.0             // amps
  #define DEFAULT_X_MAX_TRAVEL 680.0        // mm
  #define DEFAULT_Y_MAX_TRAVEL 460.0        // mm
  #define DEFAULT_Z_MAX_TRAVEL 150.0        // mm
  #define DEFAULT_A_MAX_TRAVEL 150.0        // mm
  #define DEFAULT_SPINDLE_PWM_FREQ 50000    // Hz
  #define DEFAULT_SPINDLE_PWM_OFF_VALUE 0   // %
  #define DEFAULT_SPINDLE_PWM_MIN_VALUE 0   // %
  #define DEFAULT_SPINDLE_PWM_MAX_VALUE 100 // %
  #define DEFAULT_SPINDLE_RPM_MAX 0.7       // rpm (S-value)
  #define DEFAULT_SPINDLE_RPM_MIN 0.08      // rpm (S-value)
  #define DEFAULT_STEP_PULSE_MICROSECONDS 1
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK 2   // 2 = invert Y
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255// msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 0      // WPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.01   // mm
  #define DEFAULT_ARC_TOLERANCE 0.002       // mm
  #define DEFAULT_REPORT_INCHES 0           // false
  #define DEFAULT_INVERT_ST_ENABLE 0        // false
  #define DEFAULT_INVERT_LIMIT_PINS 1       // true
  #define DEFAULT_SOFT_LIMIT_ENABLE 1       // true
  #define DEFAULT_HARD_LIMIT_ENABLE 0       // false
  #define DEFAULT_INVERT_PROBE_PIN 0        // false
  #define DEFAULT_LASER_MODE 1              // true
  #define DEFAULT_HOMING_ENABLE 1           // true
  #define DEFAULT_HOMING_DIR_MASK 1         // move top/left
  #define DEFAULT_HOMING_FEED_RATE 60.0     // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 6000.0   // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 2.0        // mm
  #define HOMING_CYCLE_0 (1<<Z_AXIS)
  #define HOMING_CYCLE_1 ((1<<X_AXIS)|(1<<Y_AXIS))
#endif // end of DEFAULTS_FABKIT

#ifdef DEFAULTS_SHERLINE_5400
  // Description: Sherline 5400 mill with three NEMA 23 Keling  KL23H256-21-8B 185 oz-in stepper motors,
  // driven by three Pololu A4988 stepper drivers with a 30V, 6A power supply at 1.5A per winding.
  #define MICROSTEPS 2
  #define STEPS_PER_REV 200.0
  #define MM_PER_REV (0.050*MM_PER_INCH) // 0.050 inch/rev leadscrew
  #define DEFAULT_X_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_Y_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_Z_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_X_MAX_RATE 635.0 // mm/min (25 ipm)
  #define DEFAULT_Y_MAX_RATE 635.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 635.0 // mm/min
  #define DEFAULT_X_ACCELERATION (50.0*60*60) // 50*60*60 mm/min^2 = 50 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (50.0*60*60) // 50*60*60 mm/min^2 = 50 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (50.0*60*60) // 50*60*60 mm/min^2 = 50 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 225.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 125.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 170.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000 // Hz
  #define DEFAULT_SPINDLE_RPM_MAX 2800.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK ((1<<Y_AXIS)|(1<<Z_AXIS))
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.01 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // true
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 50.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 635.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif // end of DEFAULTS_SHERLINE_5400

#ifdef DEFAULTS_SHAPEOKO
  // Description: Shapeoko CNC mill with three NEMA 17 stepper motors, driven by Synthetos
  // grblShield with a 24V, 4.2A power supply.
  #define MICROSTEPS_XY 8
  #define STEP_REVS_XY 400
  #define MM_PER_REV_XY (0.08*18*MM_PER_INCH) // 0.08 in belt pitch, 18 pulley teeth
  #define MICROSTEPS_Z 2
  #define STEP_REVS_Z 400
  #define MM_PER_REV_Z 1.250 // 1.25 mm/rev leadscrew
  #define DEFAULT_X_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Y_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Z_STEPS_PER_MM (MICROSTEPS_Z*STEP_REVS_Z/MM_PER_REV_Z)
  #define DEFAULT_X_MAX_RATE 1000.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 1000.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 1000.0 // mm/min
  #define DEFAULT_X_ACCELERATION (15.0*60*60) // 15*60*60 mm/min^2 = 15 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (15.0*60*60) // 15*60*60 mm/min^2 = 15 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (15.0*60*60) // 15*60*60 mm/min^2 = 15 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 200.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 200.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 200.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000 // Hz
  #define DEFAULT_SPINDLE_RPM_MAX 10000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK ((1<<Y_AXIS)|(1<<Z_AXIS))
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.02 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 250.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif // end of DEFAULTS_SHAPEOKO

#ifdef DEFAULTS_SHAPEOKO_2
  // Description: Shapeoko CNC mill with three NEMA 17 stepper motors, driven by Synthetos
  // grblShield at 28V.
  #define MICROSTEPS_XY 8
  #define STEP_REVS_XY 200
  #define MM_PER_REV_XY (2.0*20) // 2mm belt pitch, 20 pulley teeth
  #define MICROSTEPS_Z 2
  #define STEP_REVS_Z 200
  #define MM_PER_REV_Z 1.250 // 1.25 mm/rev leadscrew
  #define DEFAULT_X_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Y_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Z_STEPS_PER_MM (MICROSTEPS_Z*STEP_REVS_Z/MM_PER_REV_Z)
  #define DEFAULT_X_MAX_RATE 5000.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 5000.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 500.0 // mm/min
  #define DEFAULT_X_ACCELERATION (250.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (250.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (50.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 290.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 290.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 100.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000 // Hz
  #define DEFAULT_SPINDLE_RPM_MAX 10000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK ((1<<X_AXIS)|(1<<Z_AXIS))
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.02 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 250.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif // end of DEFAULTS_SHAPEOKO_2

#ifdef DEFAULTS_SHAPEOKO_3
  // Description: Shapeoko CNC mill with three NEMA 23 stepper motors, driven by CarbideMotion
  #define MICROSTEPS_XY 8
  #define STEP_REVS_XY 200
  #define MM_PER_REV_XY (2.0*20) // 2mm belt pitch, 20 pulley teeth
  #define MICROSTEPS_Z 8
  #define STEP_REVS_Z 200
  #define MM_PER_REV_Z (2.0*20) // 2mm belt pitch, 20 pulley teeth
  #define DEFAULT_X_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Y_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Z_STEPS_PER_MM (MICROSTEPS_Z*STEP_REVS_Z/MM_PER_REV_Z)
  #define DEFAULT_X_MAX_RATE 5000.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 5000.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 5000.0 // mm/min
  #define DEFAULT_X_ACCELERATION (400.0*60*60) // 400*60*60 mm/min^2 = 400 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (400.0*60*60) // 400*60*60 mm/min^2 = 400 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (400.0*60*60) // 400*60*60 mm/min^2 = 400 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 425.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 465.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 80.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000 // Hz
  #define DEFAULT_SPINDLE_RPM_MAX 10000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK ((1<<X_AXIS)|(1<<Z_AXIS))
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.02 // mm
  #define DEFAULT_ARC_TOLERANCE 0.01 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 100.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 1000.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 25 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 5.0 // mm
#endif // end of DEFAULTS_SHAPEOKO_3

#ifdef DEFAULTS_X_CARVE_500MM
  // Description: X-Carve 3D Carver CNC mill with three 200 step/rev motors driven by Synthetos
  // grblShield at 24V.
  #define MICROSTEPS_XY 8
  #define STEP_REVS_XY 200
  #define MM_PER_REV_XY (2.0*20) // 2mm belt pitch, 20 pulley teeth
  #define MICROSTEPS_Z 2
  #define STEP_REVS_Z 200
  #define MM_PER_REV_Z 2.117 // ACME 3/8-12 Leadscrew
  #define DEFAULT_X_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Y_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Z_STEPS_PER_MM (MICROSTEPS_Z*STEP_REVS_Z/MM_PER_REV_Z)
  #define DEFAULT_X_MAX_RATE 8000.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 8000.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 500.0 // mm/min
  #define DEFAULT_X_ACCELERATION (500.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (500.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (50.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 290.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 290.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 100.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000 // Hz
  #define DEFAULT_SPINDLE_RPM_MAX 10000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK ((1<<X_AXIS)|(1<<Y_AXIS))
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.02 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 3 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 750.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif // end of DEFAULTS_X_CARVE_500MM

#ifdef DEFAULTS_X_CARVE_1000MM
  // Description: X-Carve 3D Carver CNC mill with three 200 step/rev motors driven by Synthetos
  // grblShield at 24V.
  #define MICROSTEPS_XY 8
  #define STEP_REVS_XY 200
  #define MM_PER_REV_XY (2.0*20) // 2mm belt pitch, 20 pulley teeth
  #define MICROSTEPS_Z 2
  #define STEP_REVS_Z 200
  #define MM_PER_REV_Z 2.117 // ACME 3/8-12 Leadscrew
  #define DEFAULT_X_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Y_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
  #define DEFAULT_Z_STEPS_PER_MM (MICROSTEPS_Z*STEP_REVS_Z/MM_PER_REV_Z)
  #define DEFAULT_X_MAX_RATE 8000.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 8000.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 500.0 // mm/min
  #define DEFAULT_X_ACCELERATION (500.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (500.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (50.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 740.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 790.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 100.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000 // Hz
  #define DEFAULT_SPINDLE_RPM_MAX 10000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK ((1<<X_AXIS)|(1<<Y_AXIS))
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.02 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 3 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 750.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif // end of DEFAULTS_X_CARVE_1000MM

#ifdef DEFAULTS_ZEN_TOOLWORKS_7x7
  // Description: Zen Toolworks 7x7 mill with three Shinano SST43D2121 65oz-in NEMA 17 stepper motors.
  // Leadscrew is different from some ZTW kits, where most are 1.25mm/rev rather than 8.0mm/rev here.
  // Driven by 30V, 6A power supply and TI DRV8811 stepper motor drivers.
  #define MICROSTEPS 8
  #define STEPS_PER_REV 200.0
  #define MM_PER_REV 8.0 // 8 mm/rev leadscrew
  #define DEFAULT_X_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_Y_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_Z_STEPS_PER_MM (STEPS_PER_REV*MICROSTEPS/MM_PER_REV)
  #define DEFAULT_X_MAX_RATE 6000.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 6000.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 6000.0 // mm/min
  #define DEFAULT_X_ACCELERATION (600.0*60*60) // 600*60*60 mm/min^2 = 600 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (600.0*60*60) // 600*60*60 mm/min^2 = 600 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (600.0*60*60) // 600*60*60 mm/min^2 = 600 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 190.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 180.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 150.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000 // Hz
  #define DEFAULT_SPINDLE_RPM_MAX 10000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK ((1<<Y_AXIS))
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.02 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 250.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif // end of DEFAULTS_ZEN_TOOLWORKS_7x7

#ifdef DEFAULTS_OXCNC
  // Grbl settings for OpenBuilds OX CNC Machine
  // http://www.openbuilds.com/builds/openbuilds-ox-cnc-machine.341/
  #define DEFAULT_X_STEPS_PER_MM 26.670
  #define DEFAULT_Y_STEPS_PER_MM 26.670
  #define DEFAULT_Z_STEPS_PER_MM 50
  #define DEFAULT_X_MAX_RATE 500.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 500.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 500.0 // mm/min
  #define DEFAULT_X_ACCELERATION (10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (10.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 500.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 750.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 80.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000 // Hz
  #define DEFAULT_SPINDLE_RPM_MAX 1000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK 0
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.02 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 500.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif // end of DEFAULTS_OXCNC

#ifdef DEFAULTS_SIMULATOR
  // Settings only for Grbl Simulator (www.github.com/grbl/grbl-sim)
  // Grbl generic default settings. Should work across different machines.
  #define DEFAULT_X_STEPS_PER_MM 1000.0
  #define DEFAULT_Y_STEPS_PER_MM 1000.0
  #define DEFAULT_Z_STEPS_PER_MM 1000.0
  #define DEFAULT_X_MAX_RATE 1000.0 // mm/min
  #define DEFAULT_Y_MAX_RATE 1000.0 // mm/min
  #define DEFAULT_Z_MAX_RATE 1000.0 // mm/min
  #define DEFAULT_X_ACCELERATION (100.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (100.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (100.0*60*60) // 10*60*60 mm/min^2 = 10 mm/sec^2
  #define DEFAULT_X_MAX_TRAVEL 1000.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 1000.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 1000.0 // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000 // Hz
  #define DEFAULT_SPINDLE_RPM_MAX 1000.0 // rpm
  #define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK 0
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 25 // msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.01 // mm
  #define DEFAULT_ARC_TOLERANCE 0.002 // mm
  #define DEFAULT_REPORT_INCHES 0 // false
  #define DEFAULT_INVERT_ST_ENABLE 0 // false
  #define DEFAULT_INVERT_LIMIT_PINS 0 // false
  #define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
  #define DEFAULT_HARD_LIMIT_ENABLE 0  // false
  #define DEFAULT_INVERT_PROBE_PIN 0 // false
  #define DEFAULT_LASER_MODE 0 // false
  #define DEFAULT_HOMING_ENABLE 0  // false
  #define DEFAULT_HOMING_DIR_MASK 0 // move positive dir
  #define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 500.0 // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 1.0 // mm
#endif // end of DEFAULTS_SIMULATOR

#ifdef DEFAULTS_JONAS
  // Description: K40 Lasercutter (typical chinese 40W CO2 laser cutter/engraver)
  #define DEFAULT_X_STEPS_PER_MM 160.0      // 200 stepps/rev. * 32 microstepps / 40mm/rev
  #define DEFAULT_Y_STEPS_PER_MM 160.0
  #define DEFAULT_Z_STEPS_PER_MM 160.0
  #define DEFAULT_A_STEPS_PER_MM 160.0
  #define DEFAULT_X_MAX_RATE 24000.0        // mm/min
  #define DEFAULT_Y_MAX_RATE 24000.0        // mm/min
  #define DEFAULT_Z_MAX_RATE 24000.0        // mm/min
  #define DEFAULT_A_MAX_RATE 24000.0        // mm/min
  #define DEFAULT_X_ACCELERATION (2500.0*60*60) // 2500*60*60 mm/min^2 = 2500 mm/sec^2
  #define DEFAULT_Y_ACCELERATION (2500.0*60*60) // 2500*60*60 mm/min^2 = 2500 mm/sec^2
  #define DEFAULT_Z_ACCELERATION (2500.0*60*60) // 2500*60*60 mm/min^2 = 2500 mm/sec^2
  #define DEFAULT_A_ACCELERATION (2500.0*60*60) // 2500*60*60 mm/min^2 = 2500 mm/sec^2
  #define DEFAULT_X_CURRENT 0.6             // amps
  #define DEFAULT_Y_CURRENT 0.6             // amps
  #define DEFAULT_Z_CURRENT 0.0             // amps
  #define DEFAULT_A_CURRENT 0.0             // amps
  #define DEFAULT_X_MAX_TRAVEL 300.0        // mm NOTE: Must be a positive value.
  #define DEFAULT_Y_MAX_TRAVEL 200.0        // mm NOTE: Must be a positive value.
  #define DEFAULT_Z_MAX_TRAVEL 50.0         // mm NOTE: Must be a positive value.
  #define DEFAULT_A_MAX_TRAVEL 100.0        // mm NOTE: Must be a positive value.
  #define DEFAULT_SPINDLE_PWM_FREQ 5000     // Hz (2000 - 20000)
  #define DEFAULT_SPINDLE_PWM_OFF_VALUE 0   // %
  #define DEFAULT_SPINDLE_PWM_MIN_VALUE 1   // %
  #define DEFAULT_SPINDLE_PWM_MAX_VALUE 100 // %
  #define DEFAULT_SPINDLE_RPM_MAX 1000.0    // rpm (S-value)
  #define DEFAULT_SPINDLE_RPM_MIN 0.0       // rpm (S-value)
  #define DEFAULT_STEP_PULSE_MICROSECONDS 10
  #define DEFAULT_STEPPING_INVERT_MASK 0
  #define DEFAULT_DIRECTION_INVERT_MASK 3   // 3 = invert X+Y
  #define DEFAULT_STEPPER_IDLE_LOCK_TIME 255// msec (0-254, 255 keeps steppers enabled)
  #define DEFAULT_STATUS_REPORT_MASK 0      // WPos enabled
  #define DEFAULT_JUNCTION_DEVIATION 0.01   // mm
  #define DEFAULT_ARC_TOLERANCE 0.002       // mm
  #define DEFAULT_REPORT_INCHES 0           // false
  #define DEFAULT_INVERT_ST_ENABLE 0        // false
  #define DEFAULT_INVERT_LIMIT_PINS 1       // true for microswitches / false for optical sensors
  #define DEFAULT_SOFT_LIMIT_ENABLE 1       // true
  #define DEFAULT_HARD_LIMIT_ENABLE 0       // false
  #define DEFAULT_INVERT_PROBE_PIN 0        // false
  #define DEFAULT_LASER_MODE 1              // true
  #define DEFAULT_HOMING_ENABLE 1           // true
  #define DEFAULT_HOMING_DIR_MASK 1         // move top/left
  #define DEFAULT_HOMING_FEED_RATE 50.0     // mm/min
  #define DEFAULT_HOMING_SEEK_RATE 6000.0   // mm/min
  #define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
  #define DEFAULT_HOMING_PULLOFF 2.0        // mm
  #define HOMING_CYCLE_0 (1<<Z_AXIS)  // First home Z to clear workspace
  #define HOMING_CYCLE_1 (1<<X_AXIS)  // Then home X
  #define HOMING_CYCLE_2 (1<<Y_AXIS)  // Then home Y
#endif // end of DEFAULTS_JONAS

#endif
