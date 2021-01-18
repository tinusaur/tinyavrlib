/**
 * BuzzLib - Library for playing sounds, the TinyAVRLib Project.
 *
 * @author Neven Boyanov
 *
 * This is part of the Tinusaur/TinyAVRLib project.
 *
 * Copyright (c) 2020 Neven Boyanov, The Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Retain in your source code the link http://tinusaur.org to the Tinusaur project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/tinyavrlib
 *
 */

// ============================================================================

#ifndef BUZZLIB_H
#define BUZZLIB_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

#define BUZZLIB_BUZZER_PORT	PB4	// Define the BUZZER I/O port

// ----------------------------------------------------------------------------

#define BUZZLIB_BEEP0()	buzzlib_fx(16, 1, 1, 0, 0)
#define BUZZLIB_BEEP1()	buzzlib_fx(16, 32, 1, 0, 0)
#define BUZZLIB_BEEP2()	buzzlib_fx(16, 32, 2, 20, 0)
#define BUZZLIB_BEEP3()	buzzlib_fx(16, 32, 3, 20, 0)
#define BUZZLIB_ALARM()	buzzlib_fx(48, 1, 60, 3, 0)
#define BUZZLIB_SIREN()	buzzlib_fx(144, 2, 60, 0, 1)
#define BUZZLIB_CREAK()	buzzlib_fx(64, 1, 20, 0, 5)
#define BUZZLIB_PHONE()	buzzlib_fx(32, 6, 30, 8, 0)

// ----------------------------------------------------------------------------

void buzzlib_init(void);

void buzzlib_tone(uint8_t per, uint8_t len);
void buzzlib_fx(uint8_t per, uint8_t len, uint8_t rep, uint8_t pause, int8_t div);

// ----------------------------------------------------------------------------

#endif

// ============================================================================
