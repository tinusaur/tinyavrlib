/**
 * TinyAVRLib/BuzzLib - Testing scripts
 * @author Neven Boyanov
 * This is part of the Tinusaur/TinyAVRLib project.
 * ----------------------------------------------------------------------------
 *  Copyright (c) 2024 Tinusaur (https://tinusaur.com). All rights reserved.
 *  Distributed as open source under the MIT License (see the LICENSE.txt file)
 *  Please, retain in your work a link to the Tinusaur project website.
 * ----------------------------------------------------------------------------
 * Source code available at: https://gitlab.com/tinusaur/tinyavrlib
 */

// ============================================================================

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "tinyavrlib/buzzlib.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ATtiny85
//               +----------+    (-)--GND--
//      (RST)--> + PB5  Vcc +----(+)--VCC--
//   [OWOWOD]--> + PB3  PB2 +--------------
// --[Buzzer]----+ PB4  PB1 +--------------
// -------(-)----+ GND  PB0 +--------------
//               +----------+
//                 Tinusaur
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define TESTING_DELAY 2000

int main(void) {
	// ---- Init ----
	buzzlib_init();

	// ---- Main Loop ----
	for (;;) { // The infinite main loop
		buzzlib_fx(224, 4, 40, 1, 6);
		_delay_ms(TESTING_DELAY);

		BUZZLIB_BEEP0();
		_delay_ms(TESTING_DELAY);
		BUZZLIB_BEEP1();
		_delay_ms(TESTING_DELAY);
		BUZZLIB_BEEP2();
		_delay_ms(TESTING_DELAY);
		BUZZLIB_BEEP3();
		_delay_ms(TESTING_DELAY);
		BUZZLIB_ALARM();
		_delay_ms(TESTING_DELAY);
		BUZZLIB_SIREN();
		_delay_ms(TESTING_DELAY);
		BUZZLIB_CREAK();
		_delay_ms(TESTING_DELAY);
		BUZZLIB_PHONE();
		_delay_ms(TESTING_DELAY);
		BUZZLIB_ZAP();
		_delay_ms(TESTING_DELAY);
	}

	return 0; // Return the mandatory result value.
}

// ============================================================================
