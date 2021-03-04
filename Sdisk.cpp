#include "pch.h"
#include "Sdisk.h"

// ADDED - checking
char Sdisk::emptyspot = '~';

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{

	this->diskname = diskname;
	this->numberofblocks = numberofblocks;
	this->blocksize = blocksize;

	fstream infile;
	infile.open(this->diskname, ios::in);
	if (infile.fail()) {
		infile.open(this->diskname, ios::out);
		for (int i = 0; i < this->numberofblocks * this->blocksize; i++) {
			infile.put(emptyspot);
		}
	}
	infile.close();

}

	// retrieves block blocknumber from the disk and stores the data in the string buffer. 
	// It returns an error code of 1 if successful and 0 otherwise.
int Sdisk::getblock(int blocknumber, string & buffer) 
{
	fstream infile(this->diskname, ios::in);

	if (infile.fail()) 
	{
		return 0;
	}
	infile.seekg(blocknumber*this->blocksize);
	buffer = "";

	for (int i = 0; i < this->blocksize; i++) 
	{
		buffer += infile.get();
	}

	infile.close();
	return 1;
}

int Sdisk::putblock(int blocknumber, string buffer)
{
	// it needs ios in to ensure it fails if infile is missing
	fstream infile(this->diskname, ios::in | ios::out);

	if (infile.fail())
	{
		return 0;
	}
	
	infile.seekg(blocknumber*this->blocksize);
	
	if (buffer.length() > this->blocksize)
	{
		return 0;
	}
	// if buffer is smaller than block, make sure it's empty
	for (int i = 0; i < this->blocksize; i++)
	{
		if (buffer.length() > i)
		{
			infile.put(buffer[i]);
		}
		else 
		{
			infile.put(emptyspot);
		}
	}

	infile.close();
	return 1;
}

int Sdisk::getnumberofblocks()
{
	return this->numberofblocks;
}

int Sdisk::getblocksize()
{
	return this->blocksize;
}
