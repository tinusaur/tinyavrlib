/*
 * NUM2STR - Functions to handle the conversion of numeric vales to strings.
 *
 * @created: 2014-12-18
 * @author: Neven Boyanov
 *
 * Source code available at: https://bitbucket.org/tinusaur/owowod
 *
 */

#ifndef NUM2STR_H
#define NUM2STR_H

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

#define USINT2DECASCII_MAX_DIGITS 5

// ----------------------------------------------------------------------------

uint8_t usint2decascii(uint16_t, char *);

// ----------------------------------------------------------------------------

#endif

