/**
 * TinyAVRLib/COMTiny - Testing scripts
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

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "tinyavrlib/buzzlib.h"
#include "tinyavrlib/comtiny.h"

// ============================================================================
//		K1 - Tinusaur Board (Shield EDUx3IO)
//               +------------+
//               +        Vcc +---(+)-------
//       (RST)---+ PB5    Vcc +---(+)-------
// --------COM---+ PB3    PB2 +---PHOTO-----
// --------BUZ---+ PB4    PB1 +---SERVO-----
// --------(-)---+ GND    PB0 +---LED1------
//               +------------+
// ----------------------------------------------------------------------------
//		K2 - Tinusaur Board (Shield LEDx2)
//               +------------+
//               +        Vcc +---(+)-------
//       (RST)---+ PB5    Vcc +---(+)-------
// --------COM---+ PB3    PB2 +---SERVO-----
// --------EXT---+ PB4    PB1 +---LED2------
// --------(-)---+ GND    PB0 +---LED1------
//               +------------+
// ----------------------------------------------------------------------------
//		K3 - Tinusaur Board (Shield LEDx3)
//               +------------+
//               +        Vcc +---(+)-------
//       (RST)---+ PB5    Vcc +---(+)-------
// --------COM---+ PB3    PB2 +---LED3------
// ------SERVO---+ PB4    PB1 +---LED2------
// --------(-)---+ GND    PB0 +---LED1------
//               +------------+
// ============================================================================

#define LED1_PORT	PB0	// Define the LED port
#define LED2_PORT	PB1	// Define the LED port
#define LED3_PORT	PB2	// Define the LED port
#define SENS_PORT	PB2	// Define the SENS port
#define EXT_PORT	PB4	// Define the EXT port
#define BUZ_PORT	PB4	// Define the BUZ port

// ----------------------------------------------------------------------------

#define K1_BUILD

int main(void) {

	// ---- Initialization ----
	// Setup common ports.
	COMS_MSBY();

#ifdef K1_BUILD
	DDRB |= (1 << LED1_PORT);	// LED port as output
	DDRB &= ~(1 << SENS_PORT);	// Set the port as input
	PORTB |= (1 << SENS_PORT);	// Set pull-up
	buzzlib_init();
#endif
#ifdef K2_BUILD
	DDRB |= (1 << LED1_PORT);	// LED port as output
	DDRB |= (1 << LED2_PORT);	// LED port as output
	DDRB &= ~(1 << EXT_PORT);	// Set the port as input
	PORTB |= (1 << EXT_PORT);	// Set pull-up
#endif
#ifdef K3_BUILD
	DDRB |= (1 << LED1_PORT);	// LED port as output
	DDRB |= (1 << LED2_PORT);	// LED port as output
	DDRB |= (1 << LED3_PORT);	// LED port as output
#endif

	int8_t count = 0;
	for (;;) { // The infinite main loop

// SPLIT for K1, K2 and K3
#ifdef K1_BUILD
		// ---- K1 ----
		// (1) Sending a sequence of 5 signals (using counter) to the other two devices.
		//     If counter is decreased, will send more signals.
		if (count < 5) {
			BUZZLIB_BEEP0();
			COMS_SIG();	// Send a signal out.
			_delay_ms(1000);
			count++;
		} else {
			// (2) Waiting for a signal from another device - that will decrease the counter by 2.
			//     If there's a sensor event, will send 1 signal out.
			COMS_MSBY(); // Mode: Stand-by
			while (!COMS_CHK()) { // Wait for start of signal
				// Also, Check SENS port
				if (!(PINB & (1 << SENS_PORT))) {
					BUZZLIB_BEEP1();
					COMS_SIG();	// Send a signal out.
					_delay_ms(100);
				}
			}
			while (COMS_CHK()); // Wait for end of signal
			BUZZLIB_BEEP2();
			count -= 2;
			_delay_ms(1000);
		}
#endif
#ifdef K2_BUILD
		// ---- K2 ----
		// (1) Waiting for a signal from another device - that will switch LEDs.
		//     If there is an event on the EXT port, will send 1 signal out.
		// NOTE: The counter is used for the LED switching patterns.
		COMS_MSBY(); // Mode: Stand-by
		while (!COMS_CHK()) { // Wait for start of signal
			// Also, Check EXT port
			if (!(PINB & (1 << EXT_PORT))) {
				_delay_ms(1000);
				COMS_SIG();	// Send a signal out.
				_delay_ms(100);
			}
		}
		while (COMS_CHK()); // Wait for end of signal
		PORTB |= (1 << LED1_PORT);	// LED on.
		_delay_ms(100);
		PORTB &= ~(1 << LED1_PORT);	// LED off.
		if (count == 1) PORTB |= (1 << LED2_PORT);	// LED on.
		if (count == 2) PORTB &= ~(1 << LED2_PORT);	// LED off.
		count++;
		if (count > 2) count = 0;
#endif
#ifdef K3_BUILD
		// ---- K3 ----
		// (1) Waiting for a signal from another device - that will switch LEDs.
		// NOTE: The counter is used for the LED switching patterns.
		COMS_MSBY(); // Mode: Stand-by
		COMS_LSN(); // Listen for input signal. NOTE: This is a blocking operation.
		PORTB |= (1 << LED1_PORT);	// LED on.
		_delay_ms(100);
		PORTB &= ~(1 << LED1_PORT);	// LED off.
		if (count == 1) PORTB |= (1 << LED2_PORT);	// LED on.
		if (count == 2) PORTB |= (1 << LED3_PORT);	// LED on.
		if (count == 3) PORTB &= ~(1 << LED2_PORT);	// LED off.
		if (count == 4) PORTB &= ~(1 << LED3_PORT);	// LED off.
		count++;
		if (count > 4) count = 0;
#endif
	}

	return 0; // Return the mandatory result value.
}

// ============================================================================
