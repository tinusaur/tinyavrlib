/**
 * TinyAVRLib/Soundlib - Testing scripts
 * @author Neven Boyanov
 * This is part of the Tinusaur/TinyAVRLib project.
 * ----------------------------------------------------------------------------
 *  Copyright (c) 2023 Tinusaur (https://tinusaur.com). All rights reserved.
 *  Distributed as open source under the MIT License (see the LICENSE.txt file)
 *  Please, retain in your work a link to the Tinusaur project website.
 * ----------------------------------------------------------------------------
 * Source code available at: https://gitlab.com/tinusaur/tinyavrlib
 */

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "tinyavrlib/scheduler.h"
#include "tinyavrlib/soundlib.h"
#include "tinyavrlib/soundlib_notes.h"
#include "ode_to_joy.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                  ATtiny85
//                +----------+    (-)--GND--
//       (RST)--> + PB5  Vcc +----(+)--VCC--
//   [OWOWOD]--<--+ PB3  PB2 +--------------
//  -[Buzzer]-----+ PB4  PB1 +--------------
//  --GND--(-)----+ GND  PB0 +--------------
//                +----------+
//                  Tinusaur
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(void) {
	// ---- Init ----
	scheduler_init();
	scheduler_start();
	soundlib_init();
	soundlib_scheduler(SOUNDLIB_TEMPO);

	// ---- Testing: Melody ----
	soundlib_melody_play(ode_to_joy_notes, sizeof(ode_to_joy_notes) / sizeof(ode_to_joy_notes[0]), 7);
	scheduler_start();	// Start the scheduler
	for (;;) { /* The infinite main loop (NOTING TO DO) */ }

	return 0; // Return the mandatory for the "main" function int value - "0" for success.
}

// ============================================================================
