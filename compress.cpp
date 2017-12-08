/************************************************************************
 *
 * 												Kening Zhang, Gang Yang
 * 												CSE 100, fall 17
 * 												11/9/2017
 * 												cs100fje	  cs100fiy
 *
 * 								Assignment 3
 * Filename: compress.cpp
 * Description: to compress small files in plain ASCII. First read the
 * content of the file named(infile); then construct a Huffman code for the 
 * contents of that file; last use the code to construct a compressed
 * file named(outfile)
 ************************************************************************/	


#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include "HCNode.h"
#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

#define freq_size 256
#define arg_val 3
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

		// check whether can open the file
		if ( in.is_open()== false )
		{
				cout<<"Can Not open input file, please retry."<<endl;
				return false;
		}

		// Read bytes from the file
		std::vector<int> freqs(freq_size,0); 
		byte nextChar;

		while (1)
		{
				nextChar=in.get();
				if (in.eof())
						break;
				//	cout<< nextChar<<endl;
				freqs[(int)nextChar]++;
		}
		in.close();

		// build the Huffman tree
		HCTree tree;
		tree.build(freqs);

		// open the output file for writing
		ofstream out;
		out.open(argv[2]);
		if ( out.is_open()== false )
		{
				cout<<"Can Not open output file, please retry."<<endl;
				return false;
		}

		/*
		// For Fake compress
		for (int i=0; i<freqs.size(); i++)
		{
		//	cout<<freqs[i]<<endl;
		out<< freqs[i];
		out.put('\n');
		}

		in.open(argv[1]);
		if (!in.eof())
		{
		while (1)
		{
		nextChar=in.get();
		if (in.eof())
		break;
		//	cout<< nextChar<<endl;
		tree.encode(nextChar,out);
		}
		}
		in.close();
		out.close();
		*/

		// create the bitoutput instance object

		// True Compress		
		// use the lop for header
		for (int i=0; i< freqs.size(); i++)
		{
			out.write((char*)&freqs[i], N_BYTE*sizeof(char));
		}
		in.open(argv[1]);


		// Output the code
		if (!in.eof())
		{
			BitOutputStream os(out);
			while (1)
			{
				nextChar= in.get();
				if (in.eof())
				{
					// flush the remaining bits in stream
					os.flush();
					break;
				}
				tree.encode(nextChar,os);
			}
		}
		// close files
		in.close();
		out.close();


}
