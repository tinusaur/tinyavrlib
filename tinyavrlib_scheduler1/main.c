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
//   [OWOWOD]--> + PB3  PB2 +--------------
// --------------+ PB4  PB1 +--------------
// -------(-)----+ GND  PB0 +----LED0------
//               +----------+
//                 Tinusaur
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define LED0_PORT PB0

// ----------------------------------------------------------------------------

void scheduler_task(void) {
	PORTB ^= (1 << LED0_PORT);	// Flip the bit
}

// ----------------------------------------------------------------------------

int main(void) {
	// ---- Init ----
	scheduler_init();
	scheduler_usertask(scheduler_task, 0);
	scheduler_reinit(SCHEDULER_TCCR0B_1024, SCHEDULER_OCR0A_MAX);
	// TCCR0B_1024 OCR0A_MAX Count=0 ==> period=262ms freq=3.81Hz (CPU:1MHz)
	// TCCR0B_1024 OCR0A_DEF Count=0 ==> period=100ms freq=10Hz   (CPU:1MHz)
	// TCCR0B_1024 OCR0A_MIN Count=0 ==> period=1ms   freq=976Hz (CPU:1MHz)
	// TCCR0B_0064 OCR0A=156 Count=0 ==> period=10ms  freq=100Hz  (CPU:1MHz)
	// TCCR0B_0008 OCR0A=124 Count=0 ==> period=1ms   freq=1000Hz (CPU:1MHz)
	
	// Setup LEDs, DDRB - Data Direction Register, Port B
	DDRB |= (1 << LED0_PORT); // Set port as LED output

	// Start the scheduler
	scheduler_start();

	// ---- Main Loop ----
	for (;;) { /* The infinite main loop (NOTING TO DO) */ }

	return 0; // Return the mandatory for the "main" function int value - "0" for success.
}

// ============================================================================
