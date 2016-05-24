/**
 * Scheduler - Library to schedule time tasks
 *
 * @created 2014-07-18
 * @author Neven Boyanov
 *
 * This is part of the Tinusaur/TinyAVRLib project.
 *
 * Copyright (c) 2016 Neven Boyanov, Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Please, as a favor, retain the link http://tinusaur.org to The Tinusaur Project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/tinyavrlib
 *
 */

// ============================================================================

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "scheduler.h"

// ----------------------------------------------------------------------------

scheduler_userfunc_p __scheduler_userfunc;

// TODO: Add list of user functions.
// TODO: Implement scheduler_add that adds user function to the list.
// TODO: Call all user functions within the TIMER0_COMPA_vect.

static uint8_t __scheduler_tccr0b = SCHEDULER_TCCR0B;
static uint8_t __scheduler_ocr0a = SCHEDULER_OCR0A;

void scheduler_init(scheduler_userfunc_p userfunc) {
	__scheduler_userfunc = userfunc;
	// Setup Timer
	TCCR0A |= (1 << WGM01);	// set timer in CTC mode
	TIMSK |= (1 << OCIE0A); // set Bit 4 – OCIE0A: Timer/Counter0 Output Compare Match A Interrupt Enable
}

void scheduler_reinit(uint8_t new_tccr0b, uint8_t new_ocr0a) {
	__scheduler_tccr0b = new_tccr0b;
	__scheduler_ocr0a = new_ocr0a;
}

void scheduler_start(void) {
	// IMPORTANT: Requires TIMER0_COMPA_vect to be setup.
	sei(); //  Enable global interrupts
	// set value for OCR0A - Output Compare Register A
	OCR0A = __scheduler_ocr0a;
	// Prescale and start timer: 1/1024-th
    TCCR0B |= __scheduler_tccr0b;
}

// Define interrupt vector
ISR(TIMER0_COMPA_vect)
{
	static uint32_t __scheduler_tick;
	(*__scheduler_userfunc)(__scheduler_tick++);
	// IMPORTANT: It is not guaranteed that the "increment" operation will be atomic.
   	// Note: No need to clear flags in TIFR - done automatically
}

// ============================================================================
