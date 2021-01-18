/**
 * ADCxLib - Simple library to work with ADC
 *
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

#ifndef ADCXLIB_H
#define ADCXLIB_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------
//                 +----------+
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
// NOTE from Datasheet: The device requires a supply voltage of 3V in order to generate 2.56V reference voltage.

// ----------------------------------------------------------------------------

#define ADCX_ADCSEL(MASK)	ADMUX = (ADMUX & 0b11110000) | (MASK)	// Select ADC source
#define ADCX_REFSEL(MASK)	ADMUX = (ADMUX & 0b00101111) | (MASK)	// Select voltage reference

// ----------------------------------------------------------------------------

void adcx_init(void);
void adcx_select(uint8_t mask);
void adcx_start(void);
uint16_t adcx_read(void);

// ----------------------------------------------------------------------------

#endif

// ============================================================================
