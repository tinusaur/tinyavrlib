/**
 * TinyAVRLib/ADCxLib - Library to work with the ADC inputs
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

#ifndef ADCXLIB_H
#define ADCXLIB_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
//   Temp=[ADC4]   +----------+
//  --(RST/ADC0)---+ PB5  Vcc +---(+)--VCC--
//  ------[ADC3]---+ PB3  PB2 +---[ADC1]----
//  ------[ADC2]---+ PB4  PB1 +-------------
//  ---------(-)---+ GND  PB0 +---[AREF]----
//                 +----------+
//     Temp=ADC4     ATtiny85
// ----------------------------------------------------------------------------

#define ADCX_SELECT_MASK_ADC0	0b0000	// PB5 (RST)
#define ADCX_SELECT_MASK_ADC1	0b0001	// PB2
#define ADCX_SELECT_MASK_ADC2	0b0010	// PB4
#define ADCX_SELECT_MASK_ADC3	0b0011	// PB3
#define ADCX_SELECT_MASK_ADC4	0b1111	// Internal temperature sensor

#define ADCX_REFSEL_MASK_VCC		(				(0 << REFS1) | (0 << REFS0))	// Vcc used as Voltage Reference, disconnected from PB0 (AREF).
#define ADCX_REFSEL_MASK_EXTPB0		(				(0 << REFS1) | (1 << REFS0))	// External Voltage Reference at PB0 (AREF) pin, Internal Voltage Reference turned off.
#define ADCX_REFSEL_MASK_INT11V		((0 << REFS2) | (1 << REFS1) | (0 << REFS0))	// Internal 1.1V Voltage Reference.
#define ADCX_REFSEL_MASK_RESERVED	((0 << REFS2) | (1 << REFS1) | (1 << REFS0))	// Reserved
#define ADCX_REFSEL_MASK_INT256V	((1 << REFS2) | (1 << REFS1) | (0 << REFS0))	// Internal 2.56V Voltage Reference without external bypass capacitor, disconnected from PB0 (AREF).
#define ADCX_REFSEL_MASK_INT256VXBP	((1 << REFS2) | (1 << REFS1) | (1 << REFS0))	// Internal 2.56V Voltage Reference with external bypass capacitor at PB0 (AREF) pin.
// NOTE from Datasheet: The device requires a supply voltage of at least 3V in order to generate 2.56V reference voltage.
// NOTE from Datasheet: Whenever these bits are changed, the next conversion will take 25 ADC clock cycles.
//						For Prescale 1/128th at 1MHz, 25 ADC clock cycles are 0.0032 sec.
#define ADCX_CHANGE_DELAY		4	// Small delay (in ms) might be necessary for correct first ADC, and after changes.

// ----------------------------------------------------------------------------

#define ADCX_ADCSEL(MASK)	ADMUX = (ADMUX & 0b11110000) | (MASK & 0b00001111)	// Select ADC source
#define ADCX_REFSEL(MASK)	ADMUX = (ADMUX & 0b00101111) | (MASK & 0b11010000)	// Select voltage reference
#define ADCX_START()		ADCSRA |= (1 << ADSC)	// Set start conversions

// ----------------------------------------------------------------------------

void adcx_init(void);
uint16_t adcx_read(void);

// ----------------------------------------------------------------------------

#endif

// ============================================================================
