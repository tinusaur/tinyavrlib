/**
 * Scheduler - Testing script.
 *
 * @created 2016-05-15
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

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

#include "tinyavrlib/scheduler.h"

#include "owowod/owowod.h"
#include "owowod/debugging.h"

//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ATtiny
//                25/45/85
//              +----------+   (-)--GND--
//      (RST)---+ PB5  Vcc +---(+)--VCC--
// --[OWOWOD]---+ PB3  PB2 +-------LED3--
// --LED5-------+ PB4  PB1 +-------LED2--
// -------(-)---+ GND  PB0 +-------LED1--
//              +----------+
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

// ----------------------------------------------------------------------------

#define LED1_PORT PB0
#define LED2_PORT PB1
#define LED3_PORT PB2
// #define LED4_PORT PB3	// NOTE: Used by the OWOWOD library
#define LED5_PORT PB4

// ----------------------------------------------------------------------------

void scheduler_func0(uint32_t scheduler_tick) {
	DEBUGGING_NUMDECUP(scheduler_tick);
	uint8_t tick = scheduler_tick & 0b00000011;	// Mask the lower 2 bits.
	DEBUGGING_NUMDECUP(tick);
	switch (tick) {
		case 0:
			PORTB ^= (1 << LED1_PORT);	// Flip the bit
		break;
		case 1:
			PORTB ^= (1 << LED2_PORT);	// Flip the bit
		break;
		case 2:
			PORTB ^= (1 << LED3_PORT);	// Flip the bit
		break;
		case 3:
			PORTB ^= (1 << LED5_PORT);	// Flip the bit
		break;
	}
	DEBUGGING_CRLF();
}

// ----------------------------------------------------------------------------

int main(void) {

	// ---- Initialization ----
	DEBUGGING_INIT();
	DEBUGGING_CRLF(); DEBUGGING_STRINGLN("HELLO[SCHEDULER]");	// Not really needed

	scheduler_init(scheduler_func0);
	scheduler_reinit(SCHEDULER_TCCR0B_1024, SCHEDULER_OCR0A_MAX);
	
	// Setup LED, DDRB - Data Direction Register, Port B
	DDRB |= (1 << LED1_PORT); // Set port as LED output
	DDRB |= (1 << LED2_PORT); // Set port as LED output
	DDRB |= (1 << LED3_PORT); // Set port as LED output
	// DDRB |= (1 << LED4_PORT); // 	// NOTE: Used by the OWOWOD library
	DDRB |= (1 << LED5_PORT); // Set port as LED output

	// Start the scheduler
	scheduler_start();

	// ---- Main Loop ----
	for (;;) {
		/* NOTING TO DO HERE */
	}

	return 0;
}

// ============================================================================
