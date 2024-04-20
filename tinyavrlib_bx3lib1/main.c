/**
 * TinyAVRLib/ADCxLib - Testing scripts
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

#include "tinyavrlib/adcxlib.h"
#include "tinyavrlib/buzzlib.h"
#include "tinyavrlib/bx3lib.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                   ATtiny85
//                 +----------+
// -------[ADC0]---+ RST  Vcc +---(+)-----VCC--
// -------[ADC3]---+ PB3  PB2 +---[ADC1]-------
// -------[ADC2]---+ PB4  PB1 +---[AIN1]-------
// --GND-----(-)---+ GND  PB0 +---[AIN0/AREF]--
//                 +----------+
//                Tinusaur Board
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SIMU_LED1 PB0	// Define the LED1 (RED) I/O port
#define SIMU_LED2 PB1	// Define the LED2 (GRE) I/O port
#define SIMU_LED3 PB2	// Define the LED3 (BLU) I/O port
#define SIMU_BUZZ PB4	// Define the BUZZ (Buzzer) I/O port

#define LED_MASK	0b00000111

// ----------------------------------------------------------------------------

void leds_set(uint8_t leds) {
	PORTB &= ~LED_MASK;
	PORTB |= (leds & LED_MASK);
}

// ----------------------------------------------------------------------------

int main(void) {

	// ---- Initialization ----
	DDRB |= (1 << SIMU_LED1)
		| (1 << SIMU_LED2) 
		| (1 << SIMU_LED3)
		| (1 << SIMU_BUZZ);
	buzzlib_init();

	adcx_init();
	ADCX_ADCSEL(ADCX_SELECT_MASK_ADC3);
	ADCX_START();
	_delay_ms(4); // Small delay may be necessary for correct first ADC.

	// ---- Main Loop ----
	leds_set(0);	// All LEDs off.
	for (;;) {
		uint8_t bc = bx3_click();	// Get a Button click from 1 of the 3 Buttons.
		leds_set(bc);	// Turn On/Off the LEDs
		buzzlib_tone(40 + (bc << 3), 20);
		_delay_ms(100);
		leds_set(0);	// Turn On/Off the LEDs
	}

	return 0; // Return the mandatory result value. It is "0" for success.
}

// ============================================================================
