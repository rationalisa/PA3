/*********************************************************************
 *
 * 											Kening Zhang, Gang Yang
 * 											CSE 100, fall 17
 * 											11/9/2017
 * 											cs100fje	  cs100fiy
 *
 * 								Assignment 3
 * Filename: BitInputStream.h
 * Description: set the private and public field in BitInputStream
 ********************************************************************/

#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <iostream>

#define buf_count 8

typedef unsigned char byte;

using namespace std;

/** A function class for use as setting the private and public 
 *  field of BitInputStream
 */
class BitInputStream{
private:
	int counter; // how many bits have been read to buf
	byte buffer; // one byte buffer of bits
	std::istream & in; // reference to the input stream to use

public:
    /* Initialize a BitInputStream that will use
     * the given istream for input */
	BitInputStream(std::istream & is): in(is){ buffer =0; counter = buf_count;}
	void fill(); // call to fill the buffer
	int readBit();	// call to read ifstream and return bit value
	bool isEOF();	// check if ifstream is EOF
};

#endif //BITINPUTSTREAM_H
