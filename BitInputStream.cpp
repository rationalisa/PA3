/*******************************************************************
 *
 * 										Kening Zhang, Gang Yang
 * 										CSE 100, fall 17
 * 										11/9/2017
 * 										cs100fje	  cs100fiy
 *
 * 						Assignment 3
 * Filename: BitInputStream.cpp
 * Description: set the fill method to read the input stream, and 
 * 				the readBit method to read the bit. Last, use the
 * 				isEOF to check the error
 ******************************************************************/

#include <iostream>
#include "BitInputStream.h"

#define b_fill 8
#define move_bit 7

typedef unsigned char byte;

using namespace std;

/** read the input stream and set the counter to 0 
 */
void BitInputStream::fill()
{
		in.read((char*)&buffer,sizeof(char));
		counter=0;
}

/** read the bit of the input stream
 */
int BitInputStream::readBit()
{
		// check the buffer is filled
		if (counter == b_fill)
			fill();

		// set the mask
		byte mask=0x01;
		mask=mask << (move_bit-counter);
		mask = mask & buffer;
		mask= mask>> (move_bit-counter);
		counter++;

		// check if we get 0 or 1
		if (mask == 0x00)
				return 0;
		else if (mask == 0x01)
				return 1;
}

/** return true if the stream's eofbit error state
 * flag is set
 */
bool BitInputStream::isEOF()
{
	return in.eof();
}

