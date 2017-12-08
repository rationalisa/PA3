/****************************************************************************
 *
 * 													Kening Zhang, Gang Yang
 * 													CSE 100, fall 17
 * 													11/8/2017
 * 													cs100fje	  cs100fiy
 *
 * 							Assignment 3
 * Filename: HCTree.cpp
 * Description:
 *
 ****************************************************************************/

#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include "HCNode.h"
#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
using namespace std;
typedef unsigned char byte;
#define END 256

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
void HCTree::build(const vector<int>& freqs)
{
	std::priority_queue <HCNode*,std::vector<HCNode*>, HCNodePtrComp> pq;

	// use the loop to set the node
	for (int i=0; i< freqs.size();i++)
	{

		// check the existence of the int
		if(freqs[i]!=0)
		{

			// set the value of node
			HCNode* p = new HCNode(freqs[i],(char)i,0,0,0);
			this->leaves[i]=p;
			pq.push(p);
		}

		freqSum=freqSum+freqs[i];
	}

	// check the size of the queue
	if (pq.size() ==0)
		return;

	// check the element is all pop
	while (pq.size()>1)
	{
		
		// pop the child node and set their parent node
		HCNode* p0 =pq.top();
		pq.pop();
		HCNode* p1= pq.top();
		pq.pop();
		HCNode* parent= new HCNode(p0->count+p1->count,(char)0,p0,p1,0);
		p0->p = parent;
		p1->p = parent;
		pq.push(parent);
	}

	HCNode* root = pq.top();
	pq.pop();
	this-> root=root;
}

/** the destructor of thr HCTree
 */
HCTree::~HCTree()
{
	// check if the root is null
	if (root != nullptr)
		deleteNode(root);

}

/** delete the node in tree
 */
void HCTree::deleteNode( HCNode* node)
{
	// use the recursion to delete the node
	if (node->c0)
		deleteNode(node->c0);
	if (node->c1)
		deleteNode(node->c1);
	delete node;
}



    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
void HCTree::encode(byte symbol, BitOutputStream& out) const{
	HCNode* node;
	std::vector<HCNode*> trial; 
	for (int i =0; i< leaves.size();i++)
	{
			// find the correpsonding symbol
			if (leaves[i] && (symbol== leaves[i]->symbol))
			{
				if(leaves[i]->count !=0)
				{
					// continue push node into the vector
					node = leaves[i];
					while (true)
					{
						trial.push_back(node);	
						if (node == root)
							break;
						node = node->p;
					}
				}
				else
				{
					return;
				}
				break;		
			}
	}
	// only one node in the tree
	if (trial.size()==1)
	{
		out.writeBit(0x01);
		return;
	}	
	// check if edge is 0 or 1
	for (int i=trial.size()-1; i>0; i--)
	{
		if (trial[i]->c0 == trial[i-1])
		{
				out.writeBit(0x00);	

		}
		else if (trial[i]->c1 == trial[i-1])
		{
				out.writeBit(0x01);
		}
	}

}

    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
void HCTree::encode(byte symbol, ofstream& out) const{
	HCNode* node;
	std::vector<HCNode*> trial; 
	// loop through the leaves vector
	for (int i =0; i< leaves.size();i++)
	{
		if (leaves[i])
		{
			if (symbol== leaves[i]->symbol)
			{	
				if(leaves[i]->count !=0)
				{
					// put non-zero nodes into the vector
					node = leaves[i];
					while (true)
					{
						trial.push_back(node);	
						if (node == root)
							break;
						node = node->p;
					}
				}
				else
				{
					return;
				}
				break;
			}
		}
	}
	// only one node in the tree
	if (trial.size()==1)
	{
		out<< '1';
		return;
	}	
	// check the edge is 0 or 1
	for (int i=trial.size()-1; i>0; i--)
	{
		if (trial[i]->c0 == trial[i-1])
		{
				out << '0';	
		}
		else if (trial[i]->c1 == trial[i-1])
				out << '1';
	}


}


    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
int HCTree::decode(BitInputStream& in) const{
	HCNode* node=root;
	while (1)
	{
		byte nextChar;
		nextChar=in.readBit();
		if (in.isEOF())
		{
			return END;
		}
		// edge case when root is the only symbol
		if (node->c0 ==0 && node->c1 ==0)
			return (int)node->symbol;
		else
		{
			// check the character and read until the symbol
			if (nextChar == 0x00)
			{
				node = node-> c0;
			}
			else if (nextChar == 0x01)
			{
				node = node-> c1;
			}
			if (node->c0 ==0 && node->c1 ==0 )
			{
				return (int)node->symbol;
			}
		}
	}
	

}

    /** Return the symbol coded in the next sequence of bits (represented a 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
int HCTree::decode(ifstream& in) const
{
	HCNode* node=root;
	while (1)
	{
		byte nextChar;
		nextChar=in.get();
		if (in.eof())
		{
			return 256;
		}
		// edge case when root is the only symbol
		if (node->c0 ==0 && node->c1 ==0)
			return (int)node->symbol;
		// check the character and print out 
		else
		{
			if (nextChar == '0')
			{
				node = node-> c0;
			}
			else if (nextChar == '1')
			{
				node = node-> c1;
			}
			if (node->c0 ==0 && node->c1 ==0 )
			{
				return (int)node->symbol;
			}
		}
	}
	
}

// get function to get the sum of frequency
int HCTree::getSum()const
{
	return freqSum;
}


