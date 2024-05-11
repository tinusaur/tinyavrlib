/**
 * TinyAVRLib/Scheduler - Testing scripts
 * @author Neven Boyanov
 * This is part of the Tinusaur/TinyAVRLib project.
 * ----------------------------------------------------------------------------
 *  Copyright (c) 2021 Tinusaur (https://tinusaur.com). All rights reserved.
 *  Distributed as open source under the MIT License (see the LICENSE.txt file)
 *  Please, retain in your work a link to the Tinusaur project website.
 * ----------------------------------------------------------------------------
 * Source code available at: https://gitlab.com/tinusaur/tinyavrlib
 */

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "tinyavrlib/scheduler.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ATtiny85
//               +----------+    (-)--GND--
//      (RST)--> + PB5  Vcc +----(+)--VCC--
// ------LED3----+ PB3  PB2 +----LED2------
// ------LED4----+ PB4  PB1 +----LED1------
// -------(-)----+ GND  PB0 +----LED0------
//               +----------+
//                 Tinusaur
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define LED0_PORT PB0
#define LED1_PORT PB1
#define LED2_PORT PB2
#define LED3_PORT PB3
#define LED4_PORT PB4

// ----------------------------------------------------------------------------

void scheduler_task0(void) {
	PORTB ^= (1 << LED0_PORT);	// Flip the bit
}

void scheduler_task1(void) {
	PORTB ^= (1 << LED1_PORT);	// Flip the bit
}

void scheduler_task2(void) {
	PORTB ^= (1 << LED2_PORT);	// Flip the bit
}

void scheduler_task3(void) {
	PORTB ^= (1 << LED3_PORT);	// Flip the bit
}

// ----------------------------------------------------------------------------

int main(void) {
	// ---- Init ----
	scheduler_init();
	scheduler_reinit(SCHEDULER_TCCR0B_1024, SCHEDULER_OCR0A_MAX);
	scheduler_usertask(scheduler_task0, 0);
	scheduler_usertask(scheduler_task1, 1);
	scheduler_usertask(scheduler_task2, 2);
	scheduler_usertask(scheduler_task3, 3);
	
	// Setup LEDs, DDRB - Data Direction Register, Port B
	DDRB |= (1 << LED0_PORT); // Set port as LED output
	DDRB |= (1 << LED1_PORT); // Set port as LED output
	DDRB |= (1 << LED2_PORT); // Set port as LED output
	DDRB |= (1 << LED3_PORT); // Set port as LED output
	DDRB |= (1 << LED4_PORT); // Set port as LED output

	// Start the scheduler
	scheduler_start();

	// ---- Main Loop ----
	for (;;) { /* The infinite main loop */
		cli();
		PORTB ^= (1 << LED4_PORT);	// Flip the bit
		sei();
		_delay_ms(1000);
	}

	return 0; // Return the mandatory for the "main" function int value - "0" for success.
}

// ============================================================================
