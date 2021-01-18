/**
 * TinyAVRLib/Soundlib - Testing scripts
 *
 * @created 2017-07-13
 * @author Neven Boyanov
 *
 * This is part of the Tinusaur/TinyAVRLib project.
 *
 * Copyright (c) 2017 Neven Boyanov, The Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Retain in your source code the link http://tinusaur.org to the Tinusaur project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/tinyavrlib
 *
 */

// ============================================================================

// #define F_CPU 1000000UL
// NOTE: The F_CPU (CPU frequency) should not be defined in the source code.
//       It should be defined in either (1) Makefile; or (2) in the IDE. 

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "tinyavrlib/scheduler.h"
#include "tinyavrlib/soundlib.h"
#include "tinyavrlib/soundlib_notes.h"

#include "ode_to_joy.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ATtiny85
//               +----------+   (-)--GND--
//       (RST)---+ PB5  Vcc +---(+)--VCC--
// ---[OWOWOD]---+ PB3  PB2 +-------------
// ---[Buzzer]---+ PB4  PB1 +-------------
// --------(-)---+ GND  PB0 +-------------
//               +----------+
//              Tinusaur Board
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ----------------------------------------------------------------------------

int main(void) {

	// ---- Initialization ----

	scheduler_init(SCHEDULER_USERFUNC_NULL);
	scheduler_reinit(SCHEDULER_TCCR0B_1024, SCHEDULER_OCR0A_MIN);	// Adjust, if necessary
	scheduler_start();

	soundlib_init();
	soundlib_scheduler();

	// ---- Testing: Buzzer ----

	soundlib_melody_play(ode_to_joy_notes, sizeof(ode_to_joy_notes) / sizeof(ode_to_joy_notes[0]), 7);
	scheduler_start();	// Start the scheduler

	for (;;) { /* Infinite main loop */ }

	// Return the mandatory for the "main" function int value. It is "0" for success.
	return 0;
}

// ============================================================================
