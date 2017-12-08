/**************************************************************************
 *
 *													Kening Zhang, Gang Yang
 *													CSE 100, fall 17
 *													11/9/2017
 *													cs100fje	  cs100fiy
 *
 *								Assignment 3
 * Filename: HCNode.cpp
 * Description: implement the HCNode.h in the file, and use operator < to 
 * 				compare the node
 **************************************************************************/ 

#include <iostream>
#include "HCNode.h"

typedef unsigned char byte;

using namespace std;


    /** Less-than comparison, so HCNodes will work in std::priority_queue
     *  We want small counts to have high priority.
     *  And we want to break ties deterministically.
     */
bool HCNode::operator<(const HCNode& other){
	// if counts are different, just compare counts
	if (count != other.count)
		return count > other.count;
	// counts are equal. use symbol value to break tie.
	return symbol < other.symbol;
}
