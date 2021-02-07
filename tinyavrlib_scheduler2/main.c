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

#include "tinyavrlib/scheduler.h"

// NOTE: To remove the use of the DEBUGGING: (1) remove its use from this file; (2) remove it (owowod and num2str) from the Makefile.
// #include "owowod/owowod.h"
// #include "owowod/debugging.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                 ATtiny85
//               +----------+    (-)--GND--
//      (RST)--> + PB5  Vcc +----(+)--VCC--
//   [OWOWOD]--> + PB3  PB2 +----LED2------
// ------LED4----+ PB4  PB1 +----LED1------
// -------(-)----+ GND  PB0 +----LED0------
//               +----------+
//                 Tinusaur
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define LED0_PORT PB0
#define LED1_PORT PB1
#define LED2_PORT PB2
// #define LED3_PORT PB3	// NOTE: Used by the OWOWOD library
#define LED4_PORT PB4

// ----------------------------------------------------------------------------

void scheduler_func0(uint32_t scheduler_tick) {
	// DEBUGGING_VARU("userfunc, tick", scheduler_tick); DEBUGGING_CRLF();
	PORTB ^= (1 << LED4_PORT);	// Flip the bit
}

void scheduler_task1(scheduler_status_p scheduler) {
	// DEBUGGING_VARU("task1, tick", (*scheduler).tick); DEBUGGING_CRLF();
	PORTB ^= (1 << LED0_PORT);	// Flip the bit
}

void scheduler_task2(scheduler_status_p scheduler) {
	// DEBUGGING_VARU("task2, tick", (*scheduler).tick); DEBUGGING_CRLF();
	PORTB ^= (1 << LED1_PORT);	// Flip the bit
}

void scheduler_task3(scheduler_status_p scheduler) {
	// DEBUGGING_VARU("task3, tick", (*scheduler).tick); DEBUGGING_CRLF();
	PORTB ^= (1 << LED2_PORT);	// Flip the bit
}

// ----------------------------------------------------------------------------

int main(void) {
	// ---- Init ----
	// DEBUGGING_INIT();
	// DEBUGGING_CRLF(); DEBUGGING_STRINGLN("HELLO[SCHEDULER]");	// Not really needed
	scheduler_init(scheduler_func0);
	scheduler_usertask(scheduler_task1, 1);
	scheduler_usertask(scheduler_task2, 2);
	scheduler_usertask(scheduler_task3, 3);
	scheduler_reinit(SCHEDULER_TCCR0B_1024, SCHEDULER_OCR0A_MAX);
	
	// Setup LEDs, DDRB - Data Direction Register, Port B
	DDRB |= (1 << LED0_PORT); // Set port as LED output
	DDRB |= (1 << LED1_PORT); // Set port as LED output
	DDRB |= (1 << LED2_PORT); // Set port as LED output
	// DDRB |= (1 << LED3_PORT); // 	// NOTE: Used by the OWOWOD library
	DDRB |= (1 << LED4_PORT); // Set port as LED output

	// Start the scheduler
	scheduler_start();

	// ---- Main Loop ----
	for (;;) { /* The infinite main loop (NOTING TO DO) */ }

	return 0; // Return the mandatory for the "main" function int value - "0" for success.
}

// ============================================================================
