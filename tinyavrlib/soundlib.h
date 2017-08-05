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

#ifndef SOUNDLIB_H
#define SOUNDLIB_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

typedef const uint16_t soundlib_melody_data_t;

// ----------------------------------------------------------------------------

void soundlib_init(void);
void soundlib_scheduler(uint8_t);
void soundlib_tone_play(uint16_t, uint8_t);
void soundlib_tone_stop(void);
void soundlib_melody_play(const uint16_t[], int);
void soundlib_melody_start(soundlib_melody_data_t *, int);

// ----------------------------------------------------------------------------

#endif

// ============================================================================
