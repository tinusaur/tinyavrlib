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

// ----------------------------------------------------------------------------

#ifndef SOUNDLIB_NOTES_H
#define SOUNDLIB_NOTES_H

// ----------------------------------------------------------------------------

// Suffixes:
// N - natural
// S - Sharp ♯
// F - Flat ♭

// #define	NOTE_A0N	((8 << 8) | 142)	// Do not use these notes so the higher 5 bits
// #define	NOTE_A0S	((8 << 8) | 134)	// are available for other purposes, e.g. length.
#define	NOTE_B0N	((7 << 8) | 253)
#define	NOTE_C0N	((7 << 8) | 239)
#define	NOTE_C0S	((7 << 8) | 225)
#define	NOTE_D0N	((7 << 8) | 213)
#define	NOTE_D0S	((7 << 8) | 201)
#define	NOTE_E0N	((7 << 8) | 190)
#define	NOTE_F0N	((7 << 8) | 179)
#define	NOTE_F0S	((7 << 8) | 169)
#define	NOTE_G0N	((7 << 8) | 159)
#define	NOTE_G0S	((7 << 8) | 150)
#define	NOTE_A1N	((7 << 8) | 142)
#define	NOTE_A1S	((7 << 8) | 134)
#define	NOTE_B1N	((6 << 8) | 253)
#define	NOTE_C1N	((6 << 8) | 239)
#define	NOTE_C1S	((6 << 8) | 225)
#define	NOTE_D1N	((6 << 8) | 213)
#define	NOTE_D1S	((6 << 8) | 201)
#define	NOTE_E1N	((6 << 8) | 190)
#define	NOTE_F1N	((6 << 8) | 179)
#define	NOTE_F1S	((6 << 8) | 169)
#define	NOTE_G1N	((6 << 8) | 159)
#define	NOTE_G1S	((6 << 8) | 150)
#define	NOTE_A2N	((6 << 8) | 142)
#define	NOTE_A2S	((6 << 8) | 134)
#define	NOTE_B2N	((5 << 8) | 253)
#define	NOTE_C2N	((5 << 8) | 239)
#define	NOTE_C2S	((5 << 8) | 225)
#define	NOTE_D2N	((5 << 8) | 213)
#define	NOTE_D2S	((5 << 8) | 201)
#define	NOTE_E2N	((5 << 8) | 190)
#define	NOTE_F2N	((5 << 8) | 179)
#define	NOTE_F2S	((5 << 8) | 169)
#define	NOTE_G2N	((5 << 8) | 159)
#define	NOTE_G2S	((5 << 8) | 150)
#define	NOTE_A3N	((5 << 8) | 142)
#define	NOTE_A3S	((5 << 8) | 134)
#define	NOTE_B3N	((4 << 8) | 253)
#define	NOTE_C3N	((4 << 8) | 239)
#define	NOTE_C3S	((4 << 8) | 225)
#define	NOTE_D3N	((4 << 8) | 213)
#define	NOTE_D3S	((4 << 8) | 201)
#define	NOTE_E3N	((4 << 8) | 190)
#define	NOTE_F3N	((4 << 8) | 179)
#define	NOTE_F3S	((4 << 8) | 169)
#define	NOTE_G3N	((4 << 8) | 159)
#define	NOTE_G3S	((4 << 8) | 150)
#define	NOTE_A4N	((4 << 8) | 142)
#define	NOTE_A4S	((4 << 8) | 134)
#define	NOTE_B4N	((3 << 8) | 253)
#define	NOTE_C4N	((3 << 8) | 239)
#define	NOTE_C4S	((3 << 8) | 225)
#define	NOTE_D4N	((3 << 8) | 213)
#define	NOTE_D4S	((3 << 8) | 201)
#define	NOTE_E4N	((3 << 8) | 190)
#define	NOTE_F4N	((3 << 8) | 179)
#define	NOTE_F4S	((3 << 8) | 169)
#define	NOTE_G4N	((3 << 8) | 159)
#define	NOTE_G4S	((3 << 8) | 150)
#define	NOTE_A5N	((3 << 8) | 142)
#define	NOTE_A5S	((3 << 8) | 134)
#define	NOTE_B5N	((2 << 8) | 253)
#define	NOTE_C5N	((2 << 8) | 239)
#define	NOTE_C5S	((2 << 8) | 225)
#define	NOTE_D5N	((2 << 8) | 213)
#define	NOTE_D5S	((2 << 8) | 201)
#define	NOTE_E5N	((2 << 8) | 190)
#define	NOTE_F5N	((2 << 8) | 179)
#define	NOTE_F5S	((2 << 8) | 169)
#define	NOTE_G5N	((2 << 8) | 159)
#define	NOTE_G5S	((2 << 8) | 150)
#define	NOTE_A6N	((2 << 8) | 142)
#define	NOTE_A6S	((2 << 8) | 134)
#define	NOTE_B6N	((1 << 8) | 253)
#define	NOTE_C6N	((1 << 8) | 239)
#define	NOTE_C6S	((1 << 8) | 225)
#define	NOTE_D6N	((1 << 8) | 213)
#define	NOTE_D6S	((1 << 8) | 201)
#define	NOTE_E6N	((1 << 8) | 190)
#define	NOTE_F6N	((1 << 8) | 179)
#define	NOTE_F6S	((1 << 8) | 169)
#define	NOTE_G6N	((1 << 8) | 159)
#define	NOTE_G6S	((1 << 8) | 150)
#define	NOTE_A7N	((1 << 8) | 142)
#define	NOTE_A7S	((1 << 8) | 134)
#define	NOTE_B7N	((1 << 8) | 127)
#define	NOTE_C7N	((1 << 8) | 119)
#define	NOTE_C7S	((1 << 8) | 113)
#define	NOTE_D7N	((1 << 8) | 106)
#define	NOTE_D7S	((1 << 8) | 100)
#define	NOTE_E7N	((1 << 8) | 95)
#define	NOTE_F7N	((1 << 8) | 89)
#define	NOTE_F7S	((1 << 8) | 84)
#define	NOTE_G7N	((1 << 8) | 80)
#define	NOTE_G7S	((1 << 8) | 75)
#define	NOTE_A8N	((1 << 8) | 71)

// ----------------------------------------------------------------------------

#endif

// ----------------------------------------------------------------------------
