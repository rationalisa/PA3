/**************************************************************************
 *
 * 												Kening Zhang, Gang Yang
 * 												CSE 100, fall 17
 * 												11/9/2017
 * 												cs100fje	  cs100fiy
 *
 * 							Assignment 3
 * Filename: uncompress.cpp
 * Description: this file will read the contents of the file named by 
 * its first command line argument. Then use the contents of that file to
 * reconstruct the original, uncompressed version
 *************************************************************************/	

#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include "HCNode.h"
#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

#define arg_val 3
#define freq_size 256
#define N_BYTE 3

using namespace std;
typedef unsigned char byte;
/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
int main(int argc, char** argv){

		// check the number of argument
		if (argc != arg_val)
		{
				cout<< "Please enter infile outfile"<< endl;
				return false;
		}

		// open the file
		ifstream in;
		in.open(argv[1]);

		// check whether we can open the file
		if ( in.is_open()== false )
		{
				cout<<"Can Not open input file, please retry."<<endl;
				return false;
		}

		/*
		// Read header from the file for fake header
		std::vector<int> freqs(256,0); 
		for (int i=0; i<256; i++)
		{
		int nextInt;
		in >> nextInt;
		if (in.eof())
		break;
		cout<< nextInt<<endl;
		freqs[i]=nextInt;
		// get the newline character
		in.get();
		}
		*/

		// Read header from the file
		std::vector<int> freqs(freq_size,0);

		// use the for loop to read header
		for (int i=0; i<freq_size; i++)
		{
			int nextInt;
			in.read((char*)& nextInt,N_BYTE*sizeof(char));
			if (in.eof())
				break;
			freqs[i]=nextInt;
		}

		// build the Huffman tree
		HCTree tree;
		tree.build(freqs);



		// open the output file for writing
		ofstream out;
		out.open(argv[2]);
		if ( out.is_open()== false )
		{
			cout<<"Can Not open output file, please retry."<< endl;
			return false;
		}

		// FAKE READ
		/*	while (1)
			{
			int retvalue= tree.decode(in);
			if (retvalue== 256)
			break;
			out.put((byte)retvalue);
			}
		*/

		// decode the codes from the bottom of the input file
		BitInputStream is(in);
		for (int i =0; i< tree.getSum(); i++)
		{
			int retvalue= tree.decode(is);
			// Read bits until reaching the size of bits encoded
			if (retvalue== freq_size)
				break;
			out.put((byte)retvalue);
		}
		in.close();
		out.close();
}
