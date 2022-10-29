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

#ifndef SCHEDULER_H
#define SCHEDULER_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

//		Timer Pre-scaling
//		CS02 CS01 CS00 Description
//		---- ---- ---- --------------------------------------------------------
//		0    0    0    No clock source (Timer/Counter stopped)
//		0    0    1    clk I/O / (No prescaling)
//		0    1    0    clk I/O / 8 (From prescaler)
//		0    1    1    clk I/O / 64 (From prescaler)
//		1    0    0    clk I/O / 256 (From prescaler)
//		1    0    1    clk I/O / 1024 (From prescaler)
//		1    1    0    External clock source on T0 pin. Clock on falling edge.
//		1    1    1    External clock source on T0 pin. Clock on rising edge.

#define SCHEDULER_TCCR0B_0000	(0 << CS02) | (0 << CS01) | (0 << CS00)	// No clock source (Timer/Counter stopped)
#define SCHEDULER_TCCR0B_0001	(0 << CS02) | (0 << CS01) | (1 << CS00)	// 1 / 1 - No prescaling
#define SCHEDULER_TCCR0B_0008	(0 << CS02) | (1 << CS01) | (0 << CS00)	// 1 / 8
#define SCHEDULER_TCCR0B_0064	(0 << CS02) | (1 << CS01) | (1 << CS00)	// 1 / 64
#define SCHEDULER_TCCR0B_0256	(1 << CS02) | (0 << CS01) | (0 << CS00)	// 1 / 256
#define SCHEDULER_TCCR0B_1024	(1 << CS02) | (0 << CS01) | (1 << CS00)	// 1 / 1024
#define SCHEDULER_TCCR0B_XT0F	(1 << CS02) | (1 << CS01) | (0 << CS00)	// External clock source on T0 pin. Clock on falling edge.
#define SCHEDULER_TCCR0B_XT0R	(1 << CS02) | (1 << CS01) | (1 << CS00)	// External clock source on T0 pin. Clock on rising edge.

#define SCHEDULER_OCR0A_MIN			0	// Absolute minimum, roughly 1.024 ms ticks (976 Hz) at 1024 pre-scale. (1 MHz CPU)
#define SCHEDULER_OCR0A_DEFAULT		98	// Default, gives roughly 100.35 ms ticks (9.96 Hz) at 1024 pre-scale. (1 MHz CPU)
#define SCHEDULER_OCR0A_MAX			255	// Absolute maximum, roughly 262 ms ticks (3.81 Hz) at 1024 pre-scale. (1 MHz CPU)

// PERIOD_us = (PRESCALER * (COUNTER + 1)) / FREQ_CPU_hz
// FREQ_hz   = FREQ_CPU_hz / (PRESCALER * (COUNTER + 1))
// Useful TCCR0B/OCR0A combinations: 8/124 ==> 1.0ms (more precise)

#define SCHEDULER_TCCR0B			SCHEDULER_TCCR0B_1024
#define SCHEDULER_OCR0A				SCHEDULER_OCR0A_DEFAULT

// ----------------------------------------------------------------------------

// typedef struct {
//	uint32_t tick;
// } scheduler_status;
// NOTE: This structure may be extended in the future.
// NOTE: Not used at the moment.
// TODO: Remove the use of scheduler_status.
// typedef scheduler_status * scheduler_status_p;

typedef void (*scheduler_usertask_p)(void);

typedef union {
	scheduler_usertask_p usertask;
	void (*userproc)(void);
} scheduler_userproc;

// ----------------------------------------------------------------------------

void scheduler_init(void);
void scheduler_reinit(uint8_t, uint8_t);
void scheduler_usertask(scheduler_usertask_p usertask, uint8_t counter);
void scheduler_start(void);

// ----------------------------------------------------------------------------

#endif

// ============================================================================
