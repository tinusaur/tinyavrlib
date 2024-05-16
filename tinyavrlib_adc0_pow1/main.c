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
// NOTE: About F_CPU - it should be set either (1) in Makefile; or (2) in the IDE.

#include <stdlib.h>
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>

#include "owowod/owowod.h"
#include "owowod/debugging.h"
#include "tinyavrlib/adcxlib.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                   ATtiny85
//                 +----------+
// -------[ADC0]---+ RST  Vcc +---(+)--VCC--
// --------[PB3]---+ PB3  PB2 +---[ADC1]----
// -------BUZZER---+ PB4  PB1 +-------------
// --GND-----(-)---+ GND  PB0 +---LED-------
//                 +----------+
//                   Tinusaur
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Average - 4 values
uint16_t avgx4(uint16_t val) {
	static uint16_t vals[4];
	static uint8_t i = 0;
	uint16_t avg;
	vals[i] = val;
	uint16_t tot = vals[0] + vals[1] + vals[2] + vals[3];
	avg = tot >> 2;
	if (++i == 4) i = 0;
	return avg;
}

// Average - 8 values
uint16_t avgx8(uint16_t val) {
	static uint16_t vals[8];
	static uint8_t i = 0;
	uint16_t avg;
	vals[i] = val;
	uint16_t tot = vals[0] + vals[1] + vals[2] + vals[3] + vals[4] + vals[5] + vals[6] + vals[7];
	avg = tot >> 3;
	if (++i == 8) i = 0;
	return avg;
}

int main(void) {
	// ---- Initialization ----
	DEBUGGING_INIT();
	DEBUGGING_CRLF();
	DEBUGGING_STRINGLN("HELLO[TEST]");	// Not really needed
	adcx_init();

	// The following has no effect on the measurements.
	// DDRB &= ~(1 << PB5);		// Set the port as input.
	// PORTB &= ~(1 << PB5);	// Internal pull-up is OFF.
	// PORTB |= (1 << PB5);		// Internal pull-up is ON.

	// ---- Testing ----
	ADCX_ADCSEL(ADCX_SELECT_MASK_ADC0);
	// NOTE: For this to work ADMUX should have REFS2,REFS1,REFS0=110 - Internal 2.56V Voltage Reference
	// Possible values: ADCX_REFSEL_MASK_VCC, ADCX_REFSEL_MASK_INT11V, ADCX_REFSEL_MASK_INT256V
	ADCX_REFSEL(ADCX_REFSEL_MASK_INT256V);
	_delay_ms(ADCX_CHANGE_DELAY); // After change, small delay might be necessary for correct first ADC.
	ADCX_START();
	for (;;) {
		uint16_t adcx_result = adcx_read();
		DEBUGGING_VARU("adcx", adcx_result);
		DEBUGGING_VARU("avg/4", avgx4(adcx_result));
		DEBUGGING_VARU("avg/8", avgx8(adcx_result));
		_delay_ms(1000);
		DEBUGGING_CRLF();
	}

	return 0; // Return the mandatory for the "main" function int value. It is "0" for success.
}

// ============================================================================
