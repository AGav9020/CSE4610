#include "pch.h"
#include "Filesys.h"

#include<iomanip>
#include<sstream>
#include<cmath>

int Filesys::filenameSize = 5;

Filesys::Filesys(string diskname, int numberofblocks, int blocksize) : Sdisk(diskname, numberofblocks, blocksize)
{
	this->addressDigitSize = floor(log10(numberofblocks)) + 1;
	int sizeNeededForFat = numberofblocks * this->addressDigitSize;
	
	this->fatsize = ceil(sizeNeededForFat / blocksize);
	this->rootsize = blocksize / (filenameSize + this->addressDigitSize);

	initializeRoot();
	initializeFat();
	fssynch();

}

int Filesys::fsclose()
{
	return 0;
}


// This module writes FAT and ROOT to the sdisk. 
// It should be used every time FAT and ROOT are modified.
int Filesys::fssynch()
{
	//root
	string rootBlock = "";
	string s_add;
	for (int i = 0; i < this->rootsize; i++)
	{
		// padding address with proper digit length
		
		rootBlock += this->formatfilename(this->filename[i]) + this->padaddressblock(this->firstblock[i]);
	}
	Sdisk::putblock(0, rootBlock);

	//fat
	string fatBlock = "";
	int numOfTimesAddressFits = this->getblocksize() / this->addressDigitSize;
	int i, j = 0;
	int fatBlockIndex = 1;

	for ( i = 0; i < this->fat.size(); i++)
	{
		if (this->fat[i] != -1)
		{
			// example would be going from 0-9, 10-19, ... 
			if (j < numOfTimesAddressFits)
			{
				fatBlock += this->padaddressblock(this->fat[i]);
				j++;
			}
			else
			{
				Sdisk::putblock(fatBlockIndex, fatBlock);
				fatBlockIndex++;
				fatBlock = this->padaddressblock(this->fat[i]);
				j = 1;
			}
		}
		
		

	}
	if (fatBlock != "")
	{
		Sdisk::putblock(fatBlockIndex, fatBlock);
	}
	return 0;
}


//This function adds an entry for the string file in ROOT with an initial first block of 0 (empty).
//It returns error codes of 1 if successful and 0 otherwise (no room or file already exists).
int Filesys::newfile(string file)
{
	int rootIndex = -1;
	int firstBlockIndex = -1;
	file = this->formatfilename(file);
	// checks for file
	if (this->getfirstblock(file) != -1) 
	{
		return 0;
	}
	
	// checks for root
	for (int i = 0; i < this->rootsize; i++)
	{
		if (this->filename[i] == string(filenameSize, '.'))
		{
			rootIndex = i;
			break;
		}
	}
	
	// did not find root index
	if (rootIndex == -1 )
	{
		return 0;
	}

	this->filename[rootIndex] = file;
	this->firstblock[rootIndex] = 0;
	
	fssynch();


	return 1;

}

// This function removes the entry file from ROOT if the file is empty (first block is 0). 
// It returns error codes of 1 if successful and 0 otherwise (not empty or file does not exist).
int Filesys::rmfile(string file)
{
	int firstBlockIndex = -1;
	file = this->formatfilename(file);
	// checks for file found
	firstBlockIndex = this->getfirstblock(file);
	if (firstBlockIndex == -1)
	{
		return 0; // file does not exist
	}

	// not empty
	if(this->firstblock[firstBlockIndex] != 0)
	{
		return 0; // file is not empty
	}

	this->filename[firstBlockIndex] = string(filenameSize, '.');

	return 1;
}

int Filesys::getfirstblock(string file)
{
	file = this->formatfilename(file);

	for (int i = 0; i < this->rootsize; i++)
	{
		if (this->filename[i] == file) // file already exists
		{
			return this->firstblock[i];
		}
	}

	return -1;
}

// This function adds a block of data stored in the string buffer to 
// the end of file F and returns the block number. It returns error 
// code 0 if the file does not exist, and returns -1 if there are no 
// available blocks (file system is full!).
int Filesys::addblock(string file, string block)
{
	// format the file first
	int fileIndex = 0;
	file = this->formatfilename(file);
	if (this->fat[0] == 0)
	{
		return -1; // no available blocks (full)
	}
	int blockAvailable = this->fat[0];
	int blockIndex = this->getfirstblock(file);
	if (blockIndex == -1)
	{
		return 0; // file DNE
	}

	// if it's empty
	if(blockIndex == 0)
	{
		// write in here (this is empty and exists)
		// writing to sdisk
		for (int i = 0; i < filename.size(); i++)
		{
			if(filename[i] == file)
			{
				fileIndex = i;
				break;
			}
		}
		this->firstblock[fileIndex] = blockAvailable;
		this->fat[0] = this->fat[blockAvailable];
		this->fat[blockAvailable] = 0;
		
		this->putblock(blockAvailable, block);
		this->fssynch();
		return blockAvailable;
	}

	// if it has some items in it, but not full
	else
	{
		int currentBlock = this->getfirstblock(file);
		while (this->fat[currentBlock] != 0)
		{
			currentBlock = this->fat[currentBlock];
		}
		this->fat[currentBlock] = blockAvailable;
		this->fat[0] = this->fat[blockAvailable];
		this->fat[blockAvailable] = 0;

		// Write The Buffer To SDisk
		this->putblock(blockAvailable, block);
		return blockAvailable;
	}
}

// The function removes block numbered blocknumber from file and 
// returns an error code of 1 if successful and 0 otherwise.
int Filesys::delblock(string file, int blocknumber)
{
	file = this->formatfilename(file);
	
		/*
	if (!this->checkblock(file, blocknumber)) {
		return 0;
	}
	int b = getfirstblock(file);
	if (blocknumber == b) {
		for (int i = 0; i < filen[i]; i++) {
			if (filen[i] == file) {
				firstblock[i] = fat[blocknumber];
				break;
			}
		}
	}
	else {
		while (fat[b] != blocknumber) {
			b = fat[b];
		}
		fat[b] = fat[blocknumber];
	}

	*/

	int currentBlock = this->getfirstblock(file);

	// checks for existence
	if (currentBlock == -1)
	{
		return 0;
	}

	// block number is first block
	if (currentBlock == blocknumber)
	{
		for (int i = 0; i < this->filename.size(); i++)
		{
			if (this->filename[i] == file)
			{
				this->firstblock[i] = this->fat[blocknumber];
				break;
			}

		}
		this->fat[blocknumber] = this->fat[0];
		this->fat[0] = blocknumber;
	}

	// block number is not first block
	else
	{
		while (currentBlock != 0)
		{
			// found it,
			if (this->fat[currentBlock] == blocknumber)
			{
				this->fat[blocknumber] = this->fat[0];
				this->fat[0] = blocknumber;
				break;
			}

			// iterator
			currentBlock = this->fat[currentBlock];
		}
	}
	this->fssynch();
	return 1;
}

// gets block numbered blocknumber from file and stores the data in the string buffer. 
// It returns an error code of 1 if successful and 0 otherwise.
int Filesys::readblock(string file, int blocknumber, string & buffer)
{
	file = this->formatfilename(file);

	if (this->checkblock(file, blocknumber)) {
		this->getblock(blocknumber, buffer);
		return 1;
	}
	else {
		return 0;
	}



}

// writes the buffer to the block numbered blocknumber in file. 
// It returns an appropriate error code.
int Filesys::writeblock(string file, int blocknumber, string buffer)
{
	file = this->formatfilename(file);
	
	if (this->checkblock(file, blocknumber)) {
		this->putblock(blocknumber, buffer);
		return 1;
	}
	else {
		return 0;
	}

}


// returns the number of the block that follows blocknumber in file. 
// It will return 0 if blocknumber is the last block and -1 if some other error has occurred 
// (such as file is not in the root directory, or blocknumber is not a block in file.)
int Filesys::nextblock(string file, int blocknumber)
{
	file = this->formatfilename(file);
	// int thisBlock = this->checkblock(file, blocknumber);

	if (this->checkblock(file, blocknumber)) {
			
		return this->fat[blocknumber];
	}
	else {
		return 0;
	}

	file = this->formatfilename(file);
	int thisBlock = this->checkblock(file, blocknumber);
	if (thisBlock == -1)
	{
		return -1;
	}
	
	return thisBlock;
	//return this->fat[thisBlock];
}

// given
vector<string> Filesys::ls()
{
	vector<string> flist;
	for (int i = 0; i < filename.size(); i++)
	{
		// my delete uses .
		if (filename[i] != string(filenameSize, '.'))
		{
			flist.push_back(filename[i]);
		}
	}
	return flist;
}

// For lab 5
// checks if a block belongs to a file
bool Filesys::checkblock(string file, int blocknumber)
{
	file = this->formatfilename(file);
	int blockIndex = this->getfirstblock(file);

	if (blockIndex == -1)
	{
		return false; // file DNE
	}

	// if its first block
	if (blockIndex==blocknumber) {
		return true;
	}

	while (fat[blockIndex]!=0)
	{
		if (fat[blockIndex] == blocknumber) {
			return true;
		}

		//increments
		blockIndex = fat[blockIndex];
	}


	return false;
	/*
	All of this was my old code, before the professor had lecture 11. 
	
	if (this->fat[blockIndex] == 0) {
		if (blocknumber == 0) {
			return blockIndex;
		}
		else {
			return -1;
		}
	}
	// more than one block
	for(int index= 0; index < blocknumber; index++)
	//while (index <= blocknumber && blockIndex != 0)
	{
		if (this->fat[blockIndex] == 0)
		{
			return -1;
		}
		else
		{
			blockIndex = this->fat[blockIndex];
			break;
		}
	}
	return blockIndex;
	*/
}

void Filesys::initializeFat()
{
	string fatBlock= "";
	int firstDataBlock = 1 + this->fatsize;
	int numOfTimesAddressFits = this->getblocksize() / this->addressDigitSize;
	fatBlock = string(numOfTimesAddressFits*this->addressDigitSize, '0');
	
	// this initiallizes third array
	this->fat.push_back(firstDataBlock); // initializes first available block
	// reserves fat blocks
	for (int j = 0; j < (this->fatsize); j++)
	{
		this->fat.push_back(-1);
	}
	// initializes FAT 
	for (int j = 1+this->fatsize; j < this->getnumberofblocks(); j++)
	{
		this->fat.push_back(j+1);
	}


}

void Filesys::initializeRoot()
{
	//string rootBlock = "";
	for (int i = 0; i < rootsize; i++)
	{
		this->filename.push_back(string(filenameSize, '.'));
		this->firstblock.push_back(0);
	}
}

string Filesys::padaddressblock(int s)
{
	string s_add;
	s_add = to_string(s);
	s_add.insert(s_add.begin(), this->addressDigitSize - s_add.length(), '0');// padding address with proper digit length

	return s_add;
}


string Filesys::formatfilename(string file)
{
	if (file.length() > this->filenameSize)
	{
		file = file.substr(0, this->filenameSize);
	}
	else if (file.length() < this->filenameSize)
	{
		file.append(this->filenameSize - file.length(), ' '); // padding filename with proper digit length
	}

	return file;
}

// blocks the buffer into a list of blocks of size b
vector<string> Filesys::block(string buffer, int b)
{
	// given
	// blocks the buffer into a list of blocks of size b

	vector<string> blocks;
	int numberofblocks = 0;

	if (buffer.length() % b == 0)
	{
		numberofblocks = buffer.length() / b;
	}
	else
	{
		numberofblocks = buffer.length() / b + 1;
	}

	string tempblock;
	for (int i = 0; i < numberofblocks; i++)
	{
		tempblock = buffer.substr(b*i, b);
		blocks.push_back(tempblock);
	}

	int lastblock = blocks.size() - 1;

	for (int i = blocks[lastblock].length(); i < b; i++)
	{
		blocks[lastblock] += "#";
	}

	return blocks;


}