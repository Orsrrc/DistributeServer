//
// implement Elastic Resource Allocation Against Imbalanced Transaction Assignments
//

#ifndef __BLOCK__H_
#define __BLOCK__H_



#include <iostream>
#include <string>
#include <vector>
#include "Common.hpp"

class Block
{
public:
	Block(int index, std::string prevHas, std::string hash, std::string nonce, std::vector<std::string> data);
	std::string getPreviousHash(void);
	std::string getHash(void);
	int getIndex(void);
	std::vector<std::string> getData(void);
	void toString(void);
	// string getMerkleRoot(const vector<string> &merkle);

private:
	int index;
	Block* next;                               // address of next block
	Block* prev;                              // address of previous block
	std::string actual_hash;            // stores actual hash
	std::string local_hash;              // stores local hash
	std::string prev_hash;              // stores hash for previous block
	std::vector<std::string> data; // current block data
	std::string nonce;
};




#endif //__BLOCK__H_H

