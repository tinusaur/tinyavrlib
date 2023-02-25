/**
 * COLSP - Functions to handle color space - transformations, etc.
 *
 * @created	2016-04-30
 * @author	Neven Boyanov
 * @version	2016-04-30 (last modified)
 *
 * This is part of the Tinusaur/TinyAVRLib project.
 *
 * Copyright (c) 2016 Neven Boyanov, Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Please, as a favor, retain the link http://tinusaur.org to The Tinusaur Project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/tinyavrlib
 *
 */

// ============================================================================

#ifndef COLSP_H
#define COLSP_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------


// ---- Definitions & Types ---------------------------------------------------

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} colsp_rgb;

typedef struct {
	uint8_t h;
	uint8_t s;
	uint8_t v;
} colsp_hsv;

// ---- Functions -------------------------------------------------------------

/* HSV to RGB conversion function with only integer math */
// REF: http://web.mit.edu/storborg/Public/hsvtorgb.c
void colsp_hsv2rgb(colsp_hsv hsv, colsp_rgb *rgb) {
	uint8_t region, fpart, p, q, t;
	if (hsv.s == 0) { /* color is a grayscale */
		(*rgb).r = (*rgb).g = (*rgb).b = hsv.v;
	} else {
		region = hsv.h / 43;	// Divide hue on 6 regions: 0-5
		fpart = (hsv.h - (region * 43)) * 6;	// Calculate the reminder (0-255)
		// calculate some temp vars, doing integer multiplication
		p = (hsv.v * (255 - hsv.s)) >> 8;
		q = (hsv.v * (255 - ((hsv.s * fpart) >> 8))) >> 8;
		t = (hsv.v * (255 - ((hsv.s * (255 - fpart)) >> 8))) >> 8;
		// Calculate RGB vars based on color cone region
		switch(region) {
			case 0: (*rgb).r = hsv.v; (*rgb).g = t; (*rgb).b = p; break;
			case 1: (*rgb).r = q; (*rgb).g = hsv.v; (*rgb).b = p; break;
			case 2: (*rgb).r = p; (*rgb).g = hsv.v; (*rgb).b = t; break;
			case 3: (*rgb).r = p; (*rgb).g = q; (*rgb).b = hsv.v; break;
			case 4: (*rgb).r = t; (*rgb).g = p; (*rgb).b = hsv.v; break;
			case 5: (*rgb).r = hsv.v; (*rgb).g = p; (*rgb).b = q; break;
		}
	}
}

// ----------------------------------------------------------------------------

#endif

// ============================================================================
