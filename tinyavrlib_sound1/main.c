/**
 * TinyAVRLib/Soundlib - Testing scripts
 *
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
// NOTE: About F_CPU - it should be set in either (1) Makefile; or (2) the IDE.

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "tinyavrlib/soundlib.h"
#include "tinyavrlib/soundlib_notes.h"

#include "prelude_in_c.h"

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
	soundlib_init();

	// ---- Main Loop ----
	for (;;) { // The infinite main loop
		soundlib_melody_play_sync(prelude_in_c_notes, sizeof(prelude_in_c_notes) / sizeof(prelude_in_c_notes[0]), 7);
		_delay_ms(1000);
	}

	return 0; // Return the mandatory for the "main" function int value. It is "0" for success.
}

// ============================================================================
