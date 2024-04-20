/**
 * TinyAVRLib/ADCxLib - Library to work with the ADC inputs
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

#include "adcxlib.h"

// ----------------------------------------------------------------------------
// DEFAULTS:
//	Voltage Reference:	VCC
//	Result Alignment:	Right
//	Mode:				Free-running
void adcx_init(void) {
	// ---- Initialize ADC ----
	ADMUX =
	    (0 << REFS2) | (0 << REFS1) | (0 << REFS0) |	// Set to VCC (DEFAULT)
	    (0 << ADLAR);	// Set/Clear left shift result	(by default it is 0)
	ADCSRA =
	    (1 << ADEN) |	// Enable ADC
	    (0 << ADEN) |	// ADC Start Conversion (0 - should not start at init)
	    (1 << ADATE) |	// Enable auto trigger enable (Q: Is it used in free running mode?)
		// (1 << ADIE) |	// Enable ADC interrupt
	    // Setup ADC Prescaler
	    // 001=1: 1/2nd ... 1MHz / 2 = 500KHz
	    // 011=3: 1/8th ... 1MHz / 8 = 125KHz
	    // 111=7: 1/128th ... 1MHz / 128 = 7812Hz
	    (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// Set prescaler
	ADCSRB =
	    (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);	// Set mode, 000 = free running mode
}

// TODO: Implement "stop" function or macros.

uint16_t adcx_read(void) {
	union adcx_result {
		uint16_t data16;
		struct {
			uint8_t lo;
			uint8_t hi;
		};
	} adcx_result;
	// NOTE (from datasheet): When ADCL register is read, 
	// the ADC Data Register is not updated until ADCH is read.
	adcx_result.lo = ADCL;
	adcx_result.hi = ADCH;
	return adcx_result.data16;
}

// ============================================================================
