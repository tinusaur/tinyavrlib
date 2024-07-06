/**
 * TinyAVRLib/COMTiny - Library for Single-wire communication
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

#ifndef COMTINY_H
#define COMTINY_H

// ----------------------------------------------------------------------------

#include <stdint.h>
#include <util/delay.h>

// ----------------------------------------------------------------------------
// COMTINY Library
// SW = Single-wire communication
// SW/SBE	- Single Bit Encoding, can handle only "0" or "1", the simplest form. Prefix: COMS
// SW/PWE	- Pulse Width Encoding, can handle one or more different commands. Prefix: COMW

// ==== COMTINY / SW-SBE ======================================================
// Single-wire / Single Bit Encoding
//   Can handle only "0" or "1", the simplest form.
//   Prefix: COMS
//   NOTE: The active level is "0", the inactive is "1".

#ifndef COMS_PIN
#define COMS_PIN	PB3		// Define the COMTINY/SW-SBE pin port
#endif

// ----------------------------------------------------------------------------

#define COMS_MSBY() { COMS__MINP(); COMS__HI(); } // Mode: Stand-by = mode-input + pull-up-on
#define COMS__MINP() { DDRB &= ~(1 << COMS_PIN); } // Mode: Input. (not for direct use)
#define COMS__MOUT() { DDRB |= (1 << COMS_PIN); } // Mode: Output. (not for direct use)
#define COMS__LO() { PORTB &= ~(1 << COMS_PIN); }	// Output: Low, set port to low. (not for direct use)
#define COMS__HI() { PORTB |= (1 << COMS_PIN); }	// Output: High, set port to high. (not for direct use)
#define COMS__DLY()	_delay_ms(5) // Standard signal length delay. (not for direct use)
#define COMS_CHK() (!(PINB & (1 << COMS_PIN)))	// Check pin port active level "0".
#define COMS_LSN() { COMS_MSBY(); while (!COMS_CHK()); while (COMS_CHK()); }	// Listen for input signal. NOTE: This is a blocking operation.

// Sending a signal: Set COM as output; Send 0 out; Delay; Send 1 out; Delay; (immediately) Go back to stand-by mode.
#define COMS_SIG() { COMS__MOUT(); COMS__LO(); COMS__DLY(); COMS__HI(); COMS__DLY(); COMS_MSBY(); }	// Send a signal out.

// NOTE: About port mode and initialization:
//   The port should always be initialized and kept in Stand-by mode.
//   When COMS_SIG uses the port, it sets it back to Stand-by after use.

// ============================================================================

#endif

// ============================================================================
