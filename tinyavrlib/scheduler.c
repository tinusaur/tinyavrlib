/**
 * TinyAVRLib/Scheduler - Library to schedule time tasks
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

#include "scheduler.h"

// ----------------------------------------------------------------------------

static scheduler_userproc __scheduler_userprocs[4];
static uint8_t __scheduler_counters[4];
static uint8_t __scheduler_countdowns[4];

static uint8_t __scheduler_tccr0b = SCHEDULER_TCCR0B_DEFAULT;
static uint8_t __scheduler_ocr0a = SCHEDULER_OCR0A_DEFAULT;

void scheduler_init() {
	// Setup the Timer
	TCCR0A |= (1 << WGM01);	// set timer in CTC mode
	TIMSK |= (1 << OCIE0A); // set Bit 4 – OCIE0A: Timer/Counter0 Output Compare Match A Interrupt Enable
}

void scheduler_reinit(uint8_t new_tccr0b, uint8_t new_ocr0a) {
	__scheduler_tccr0b = new_tccr0b;
	__scheduler_ocr0a = new_ocr0a;
}

// Add a User Task to the list of scheduled tasks, up to 4 tasks.
// The counter is 8-bit variable that will be decremented on each 
// system scheduler tick, when 0 the task will be executed.
// TODO: Return error code if the number of maximum task is exceeded.
void scheduler_usertask(scheduler_usertask_p usertask, uint8_t counter) {
	static uint8_t i;	// Static - initial value is 0.
	if (i > 3) return;	// Check boundaries.
	__scheduler_userprocs[i].usertask = usertask;
	__scheduler_counters[i] = counter;
	__scheduler_countdowns[i] = counter;
	i++;
}

void scheduler_start(void) {
	// IMPORTANT: Requires TIMER0_COMPA_vect to be setup.
	sei(); // Enable global interrupts
	OCR0A = __scheduler_ocr0a; // Set value for OCR0A - Output Compare Register A
	TCCR0B &= 0b11111000; // Clear the bits before applying the OR operation.
    TCCR0B |= __scheduler_tccr0b; // Prescale and start timer. Ex.: 1/1024-th
}

// Define interrupt vector
ISR(TIMER0_COMPA_vect) {
	for (uint8_t i = 0; i < 4; i++) {
		if (__scheduler_userprocs[i].userproc) {
			if (__scheduler_countdowns[i] == 0) {
				(*__scheduler_userprocs[i].usertask)();
				__scheduler_countdowns[i] = __scheduler_counters[i]; // Reset the countdown to its initial value.
			} else {
				__scheduler_countdowns[i]--; // Decrement the countdown.
			}
		} // ELSE: continue;
	}
   	// Note: No need to clear flags in TIFR - done automatically
}
// TODO: Implement again (if necessary) the Scheduler Tick Counter, getting its value with a separate function.
// static scheduler_status __scheduler_status;
// __scheduler_status.tick++; // IMPORTANT: It is not guaranteed that the "increment" operation will be atomic.

// ============================================================================
