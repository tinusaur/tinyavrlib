/**
 * TinyAVRLib/ADCxLib - Testing scripts
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

#include "tinyavrlib/adcxlib.h"
#include "owowod/owowod.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                   ATtiny85
//   Temp [ADC4]   +----------+
// -------[ADC0]---+ RST  Vcc +---(+)-----VCC--
// -[DBG]-[ADC3]---+ PB3  PB2 +---[ADC1]-------
// -------[ADC2]---+ PB4  PB1 +---[AIN1]-------
// --GND-----(-)---+ GND  PB0 +---[AIN0/AREF]--
//                 +----------+
//                Tinusaur Board
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// REF: http://www.avrfreaks.net/forum/attiny85-temp-sensor
// REF: http://www.avrfreaks.net/forum/attiny25-and-internal-temp-sensor
// REF: ATtiny85 Datasheet, 17.12 Temperature Measurement
//      230 => -40'C	300 => +25'C	370 => +85'C
// ----------------------------------------------------------------------------

#define TESTING_DELAY 500

int main(void) {
	// ---- Initialization ----
	owowod_init();
	adcx_init();
	ADCX_START();
	ADCX_ADCSEL(ADCX_SELECT_MASK_ADC4);
	ADCX_REFSEL(ADCX_REFSEL_MASK_INT11V);	// OPT: VCC, INT11V, INT256V
	_delay_ms(ADCX_CHANGE_DELAY); // Small delay may be necessary for correct first ADC.

	// ---- Main Loop ----
	owowod_print_string("Testing: TinyAVRLib/ADCx Library\r\n");
	for (;;) {
		uint16_t adcx_result = adcx_read();
		// ---- Print values on the screen ----
		owowod_print_string("ADCx="); owowod_print_numdecup(adcx_result); owowod_print_string("\r\n");
		_delay_ms(TESTING_DELAY);
	}

	return 0; // Return the mandatory result value. It is "0" for success.
}

// ============================================================================
