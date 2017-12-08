/*******************************************************************
 *
 * 										Kening Zhang, Gang Yang
 * 										CSE 100, fall 2017
 * 										11/9/2017
 * 										cs100fje	  cs100fiy
 *
 * 						Assignment 3
 * Filename: BitOutputStream.cpp
 * Description: in this file, we need to flush the buffer, and use
 *				the writeBit to write the bit 
 ******************************************************************/	

#include <iostream>
#include <fstream>
#include "BitOutputStream.h"

#define b_flush 8
#define move_bit 7

typedef unsigned char byte;

using namespace std;

/* this method requests all characters to be written to the 
 * controlled sequence
 */
void BitOutputStream::flush()
{
		// insert char to the stream
		out.put(buffer);
		out.flush();
		buffer = counter=0;
}

/* Write the least significant bit of the argument to
 * the bit buffer, and increment the bit buffer index.
 * But flush the buffer first, if it is full.
 */
void BitOutputStream::writeBit(int i)	{

		// check if the counter is equal to 8
		if (counter == b_flush)
				flush();

		// set the mask and increment counter
		byte mask=0x01;
		mask = mask & i;
		mask =mask << (move_bit-counter);
		buffer = mask | buffer;
		counter++;
}

