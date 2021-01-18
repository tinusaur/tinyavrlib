/**
 * TinyAVRLib/Soundlib Project
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

#ifndef ODE_TO_JOY_H
#define ODE_TO_JOY_H

// ----------------------------------------------------------------------------

#include <avr/pgmspace.h>

#include "tinyavrlib/soundlib.h"
#include "tinyavrlib/soundlib_notes.h"

// ----------------------------------------------------------------------------

/**
 * "ODE TO JOY"
 */

soundlib_melody_data_t ode_to_joy_notes[] PROGMEM = {
    NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_F4N, NOTE_04TH | NOTE_G4N,
    NOTE_04TH | NOTE_G4N, NOTE_04TH | NOTE_F4N, NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_D4N,
    NOTE_04TH | NOTE_C4N, NOTE_04TH | NOTE_C4N, NOTE_04TH | NOTE_D4N, NOTE_04TH | NOTE_E4N,
    NOTE_04TD | NOTE_E4N, NOTE_08TH | NOTE_D4N, NOTE_02TH | NOTE_D4N,
	
    NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_F4N, NOTE_04TH | NOTE_G4N,
    NOTE_04TH | NOTE_G4N, NOTE_04TH | NOTE_F4N, NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_D4N,
    NOTE_04TH | NOTE_C4N, NOTE_04TH | NOTE_C4N, NOTE_04TH | NOTE_D4N, NOTE_04TH | NOTE_E4N,
    NOTE_04TD | NOTE_D4N, NOTE_08TH | NOTE_C4N, NOTE_02TH | NOTE_C4N,
	
    NOTE_04TH | NOTE_D4N, NOTE_04TH | NOTE_D4N, NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_C4N,
    NOTE_04TH | NOTE_D4N, NOTE_08TH | NOTE_E4N, NOTE_08TH | NOTE_F4N, NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_C4N,
    NOTE_04TH | NOTE_D4N, NOTE_08TH | NOTE_E4N, NOTE_08TH | NOTE_F4N, NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_D4N,
    NOTE_04TH | NOTE_C4N, NOTE_04TH | NOTE_D4N, NOTE_02TH | NOTE_G3N, NOTE_04TH | NOTE_E4N,
	
    NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_F4N, NOTE_04TH | NOTE_G4N,
    NOTE_04TH | NOTE_G4N, NOTE_04TH | NOTE_F4N, NOTE_04TH | NOTE_E4N, NOTE_04TH | NOTE_D4N,
    NOTE_04TH | NOTE_C4N, NOTE_04TH | NOTE_C4N, NOTE_04TH | NOTE_D4N, NOTE_04TH | NOTE_E4N,
    NOTE_04TD | NOTE_D4N, NOTE_08TH | NOTE_C4N, NOTE_02TH | NOTE_C4N
};

// ----------------------------------------------------------------------------

#endif

// ----------------------------------------------------------------------------
