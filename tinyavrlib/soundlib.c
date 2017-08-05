/**
 * Soundlib - Library for playing sounds, the TinyAVRLib Project.
 *
 * @created 2017-07-14
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

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "scheduler.h"
#include "soundlib.h"

// ----------------------------------------------------------------------------

soundlib_melody_data_t *soundlib_melody_data_p;
int soundlib_melody_data_size;
int soundlib_melody_data_index;

// ----------------------------------------------------------------------------

// Task to be executed by the system scheduler.
void soundlib_scheduler_task(scheduler_status_p);

// ----------------------------------------------------------------------------

void soundlib_init(void) {
	// Configure counter/timer1 for fast PWM on PB4
	GTCCR |= 
		// 1 << PWM1B |	// (done in play/stop routine) Enable PWM mode based on comparator OCR1B in Timer/Counter1.
		1 << COM1B1 | 1 << COM1B0;	// Comparator B Mode Select: Set the OC1B output line.
	TCCR1 |= 
		1 << COM1A1 | 1 << COM1A0;	// Comparator A Output Mode: Set the OC1A output line.
}

// Init the system scheduler with the library task.
void soundlib_scheduler(uint8_t counter) {
	scheduler_usertask(soundlib_scheduler_task, counter);
}

void soundlib_tone_play(uint16_t tone, uint8_t volume) {
	uint8_t sound_prescale = (tone >> 8) + 2; // Cut the prescale part of the note - the higher bits.
	TCCR1 = (TCCR1 & 0b11110000) | ((sound_prescale) & 0b00001111);
	uint8_t sound_pitch = tone & 0xff; // Mask the pitch part of the note - the lower bits.
	OCR1C = sound_pitch;
	uint8_t sound_volume = sound_pitch >> (8 - (volume & 7));	// 1...7 (7=lowest)
	OCR1B = sound_volume;
	GTCCR |= (1 << PWM1B);	// set the bit
}

void soundlib_tone_stop(void) {
	GTCCR &= ~(1 << PWM1B);	// clear the bit
}

void soundlib_melody_play(const uint16_t melody[], int size) {
	for (int i = 0; i < size; i++) {
		uint16_t melody_note = pgm_read_word(&melody[i]);
		soundlib_tone_play(melody_note, 7);
		_delay_ms(200);
	}
	soundlib_tone_stop();
}

void soundlib_melody_start(soundlib_melody_data_t *melody_data, int size) {
	soundlib_melody_data_p = melody_data;
	soundlib_melody_data_size = size;
	soundlib_melody_data_index = 0;
}

// Task to be executed by the system scheduler.
void soundlib_scheduler_task(scheduler_status_p scheduler) {
	if (soundlib_melody_data_p && ((*scheduler).tick & 0x0f) == 1) {
		uint16_t melody_note = pgm_read_word(&soundlib_melody_data_p[soundlib_melody_data_index]);
		soundlib_tone_play(melody_note, 7);
		soundlib_melody_data_index++;
		if (soundlib_melody_data_index > soundlib_melody_data_size - 1) soundlib_melody_data_index = 0;
	}
}

// ============================================================================
