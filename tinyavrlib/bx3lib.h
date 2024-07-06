/**
 * TinyAVRLib/Bx3Lib - Library for working with 3 button on 1 ADC input
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

#ifndef BX3LIB_H
#define BX3LIB_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ---- Bx3Lib: Initialization ---------------------------------------------------
// Initialization sequence: (note: some lines might be optional - if already done)
//  adcx_init();                                                        	(if necessary)
//  ADCX_ADCSEL(ADCX_SELECT_MASK_ADC3); // Select ADC input port.       	(if necessary)
//  ADCX_REFSEL(ADCX_REFSEL_MASK_VCC);  // Select reference voltage.    	(if necessary)
//  ADCX_START(); // Start ADC conversion.                              	(if necessary)
//  _delay_ms(4); // Small delay may be necessary for correct first ADC.	(if necessary)

// ---- Bx3Lib: bx3_click --------------------------------------------------
// NOTE: BLOCKING - Waits until a button(s) is(are) pressed AND released.
// RETURN: 3 bits for each of the 3 buttons.

uint8_t bx3_click(void) {
	uint8_t buttons;
	uint8_t pressed = 0;
	do {} while (((adcx_read()) >> 5) == 0);	// Wait until at least one button is pressed.
	do {					// Wait for all buttons to be released.
		buttons = (adcx_read()) >> 5;
		pressed |= buttons;	// Catch any button that is pressed.
	} while (buttons != 0);	// Quit when all buttons are released.
	return pressed;
}

// ----------------------------------------------------------------------------

#endif

// ============================================================================
