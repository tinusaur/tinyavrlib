/**
 * TinyAVRLib/BuzzLib - Library for playing sound effects on a buzzer
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

#ifndef BUZZLIB_H
#define BUZZLIB_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

#define BUZZLIB_BUZZER_PORT	PB4	// Define the BUZZER I/O port

// ----------------------------------------------------------------------------
//   -> Parameters: Period, Length, Repeats, Pause, Div
#define BUZZLIB_BEEP0()	buzzlib_fx(12, 1, 1, 0, 0)
#define BUZZLIB_BEEP1()	buzzlib_fx(24, 16, 1, 0, 0)
#define BUZZLIB_BEEP2()	buzzlib_fx(24, 16, 2, 20, 0)
#define BUZZLIB_BEEP3()	buzzlib_fx(24, 16, 3, 20, 0)
#define BUZZLIB_ALARM()	buzzlib_fx(32, 1, 32, 4, 0)
#define BUZZLIB_SIREN()	buzzlib_fx(48, 4, 24, 0, 1)
#define BUZZLIB_CREAK()	buzzlib_fx(96, 1, 32, 0, 6)
#define BUZZLIB_PHONE()	buzzlib_fx(48, 6, 24, 8, 0)
#define BUZZLIB_ZAP()	buzzlib_fx(2, 2, 12, 1, -6)

// ----------------------------------------------------------------------------

void buzzlib_init(void);

void buzzlib_tone(uint8_t per, uint8_t len);
void buzzlib_fx(uint8_t per, uint8_t len, uint8_t rep, uint8_t pause, int8_t div);

// ----------------------------------------------------------------------------

typedef void (*buzzlib_fx_callback_p)(uint8_t rep);

void buzzlib_fx_callback(buzzlib_fx_callback_p callback);

// ----------------------------------------------------------------------------

#endif

// ============================================================================
