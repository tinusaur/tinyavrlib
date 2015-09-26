/*
 * BUFFIO - Functions to handle cyclic buffered input/output.
 *
 * @created	2015-04-18
 * @author	Neven Boyanov
 *
 * This is part of the TinyAVRLib project.
 *
 * Copyright (c) 2015 Neven Boyanov, Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Please, as a favour, retain the link http://tinusaur.org to The Tinusaur Project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/tinyavrlib
 *
 */

// ----------------------------------------------------------------------------

#include "buffio.h"

// ============================================================================

// #include <stdio.h>
// #define DEBUGGING_PRINT_CHAR(ch) putchar(ch)

// ----------------------------------------------------------------------------

int8_t buffio_head = 0;
int8_t buffio_tail = 0;
char buffio_data[BUFFIO_DATA_SIZE];

// ----------------------------------------------------------------------------

void buffio_init(void)
{
	buffio_reset();
	
	// This is not necessary, at all.
    // for (int i = 0; i < sizeof (buffio_data); i++) buffio_data[i] = 0;
}

void buffio_reset(void)
{
    buffio_head = buffio_tail = 0;  // This isn't really necessary except in some specific cases.
}

void buffio_put(char ch)
{
    buffio_data[buffio_head & BUFFIO_DATA_MASK] = ch;
    buffio_head++;
}

char buffio_get()
{
    if (buffio_head - buffio_tail > BUFFIO_DATA_MASK)
    {
        buffio_tail = buffio_head - BUFFIO_DATA_MASK - 1;
    }
    char ch = buffio_data[buffio_tail & BUFFIO_DATA_MASK];
    buffio_tail++;
    return ch;
}

#define BUFFIO_HAS_MORE() (buffio_head != buffio_tail)
int buffio_has_more() { return BUFFIO_HAS_MORE(); }

// ----------------------------------------------------------------------------

int8_t buffio_skip_until(char *kw)
{
    char *kwp = kw;
	for (;;)
    {
        uint8_t ch = buffio_ids_receive();	// Receive 1 byte of data. (This may wait for the data to come)
        // DEBUGGING_PRINT_CHAR(ch);
		// Note: Received data is not stored.
        if (*kwp != ch) kwp = kw;
        if (*kwp == ch) kwp++;
        if (*kwp == '\0') return 1;
        // if (!buffio_ids_has_more()) return -1;
    }
}

int8_t buffio_receive_until(char *kw)
{
    char *kwp = kw;
	for (;;)
    {
		uint8_t ch = buffio_ids_receive();	// Receive 1 byte of data. (This may wait for the data to come)
		// DEBUGGING_PRINT_CHAR(ch);
		buffio_put(ch);	// Store received data.
		if (*kwp != ch) kwp = kw;
		if (*kwp == ch) kwp++;
		if (*kwp == '\0') return 1;
		// if (!buffio_ids_has_more()) return -1;
    }
}

int8_t buffio_receive_until2(char *kw1, char *kw2)
{
    char *kw1p = kw1;
    char *kw2p = kw2;
	for (;;)
    {
		uint8_t ch = buffio_ids_receive();	// Receive 1 byte of data.
		// NOTE: This may wait for the data to come)
		// DEBUGGING_PRINT_CHAR(ch);
		buffio_put(ch);	// Store received data.
		// Check for the keyword #1.
		if (*kw1p != ch) kw1p = kw1;
		if (*kw1p == ch) kw1p++;
		if (*kw1p == '\0') return 1;
		// Check for the keyword #2.
		if (*kw2p != ch) kw2p = kw2;
		if (*kw2p == ch) kw2p++;
		if (*kw2p == '\0') return 2;
		// if (!buffio_ids_has_more()) return -1;
    }
}

// ----------------------------------------------------------------------------
