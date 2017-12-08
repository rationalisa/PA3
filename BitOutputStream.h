/*************************************************************************
 *
 * 												Kening Zhang, Gang Yang
 * 												CSE 100, fall 17
 * 												11/9/2017
 * 												cs100fje	  cs100fiy
 *
 * 								Assignment 3
 * Filename: BitOutputStream.h`
 * Description: set the private and public field in BitOutputStream
 ************************************************************************/			

#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** a function class for use to set the private and public field 
 *  of the BitOutputStream
 */
class BitOutputStream{
private:
	byte counter; // how many bits have been read to buf
	byte buffer; // one byte buffer of bits
	std::ostream & out; // reference to the output stream to use

public:
	/** initialize a BitOutputStream that will use
     *  the given ostream for output
     */
	BitOutputStream(std::ostream & os): out(os),counter(0), buffer(0){}
	void flush();	// Output current buffer
	void writeBit(int i);	// write the int to the butter
};

#endif //BITOUTPUTSTREAM_H
