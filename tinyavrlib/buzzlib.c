/**
 * TinyAVRLib/BuzzLib - Library for playing sound effects on a buzzer
 * @author Neven Boyanov
 * This is part of the Tinusaur/TinyAVRLib project.
 * ----------------------------------------------------------------------------
 *  Copyright (c) 2021 Tinusaur (https://tinusaur.com). All rights reserved.
 *  Distributed as open source under the MIT License (see the LICENSE.txt file)
 *  Please, retain in your work a link to the Tinusaur project website.
 * ----------------------------------------------------------------------------
 * Source code available at: https://gitlab.com/tinusaur/tinyavrlib
 */

// ============================================================================

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "scheduler.h"
#include "buzzlib.h"

// ----------------------------------------------------------------------------

void buzzlib_init(void) {
	DDRB |= (1 << BUZZLIB_BUZZER_PORT);	// Set the port as output.
}

// ----------------------------------------------------------------------------

#define BUZZLIB_TONE_PERIOD	30	// the buzzer min tone period in microseconds
#define BUZZLIB_TONE_TICK1	(BUZZLIB_TONE_PERIOD >> 4)
#define BUZZLIB_TONE_TICK2	(BUZZLIB_TONE_PERIOD - BUZZLIB_TONE_TICK1)

// per,len - the period and the length of the signal
// NOTE: The value of per should never be 0, it will cause infinite while() loop.
// For per=255 Freq=100Hz, for per=1 Freq=17.9KHz
// For len=255 Duration=1282mS, for len=255 Duration=7.2mS
void buzzlib_tone(uint8_t per, uint8_t len) {
	int16_t num = (len << 7);	// This shift should not be more than 7, it will overflow the int16_t.
	while (num >= 0) {
		// Make sound with low duty-cycle
		PORTB |= (1 << BUZZLIB_BUZZER_PORT);
		for (uint8_t loop = per; loop > 0; loop--) _delay_us(BUZZLIB_TONE_TICK1);
		PORTB &= ~(1 << BUZZLIB_BUZZER_PORT);
		for (uint8_t loop = per; loop > 0; loop--) _delay_us(BUZZLIB_TONE_TICK2);
		num -= per;
	}
}

// rep - the number of repeats
// pause - the pause between repeats
// dev - the deviation in the period between repeats
void buzzlib_fx(uint8_t per, uint8_t len, uint8_t rep, uint8_t pause, int8_t dev) {
	for (; rep > 0; rep--) {
		int16_t num = (len << 7);	// This shift should not be more than 7, it will overflow the int16_t.
		while (num >= 0) {
			// Make sound with low duty-cycle
			PORTB |= (1 << BUZZLIB_BUZZER_PORT);
			for (uint8_t loop = per; loop > 0; loop--) _delay_us(BUZZLIB_TONE_TICK1);
			PORTB &= ~(1 << BUZZLIB_BUZZER_PORT);
			for (uint8_t loop = per; loop > 0; loop--) _delay_us(BUZZLIB_TONE_TICK2);
			num -= per;
		}
		for (uint8_t loop = pause; loop > 0; loop--) _delay_ms(1);
		if (per > dev) per -= dev;
	}
}

// ============================================================================
