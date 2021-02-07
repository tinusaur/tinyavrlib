/**
 * TinyAVRLib/Soundlib - Testing melody
 * @author Neven Boyanov
 * This is part of the Tinusaur/TinyAVRLib project.
 * ----------------------------------------------------------------------------
 *  Copyright (c) 2021 Tinusaur (https://tinusaur.com). All rights reserved.
 *  Distributed as open source under the MIT License (see the LICENSE.txt file)
 *  Please, retain in your work a link to the Tinusaur project website.
 * ----------------------------------------------------------------------------
 * Source code available at: https://gitlab.com/tinusaur/tinyavrlib
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
