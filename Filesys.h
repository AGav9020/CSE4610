#pragma once
#include "Sdisk.h"

// LAB 3, 4, 5 || PROJECT 2 - DONE

/* Project 2 - done
The second part of this project requires that you implement a 
simple file system. In particular, you are going to write the software 
which which will handle dynamic file management. This part of the project 
will require you to implement the class Filesys along with member functions.
*/

/* Lab 03 - done
This laboratory is designed to get you started with the second part of the project
Create function stubs (functions with no code) for the class functions.
Work first on the Filesys constructor where you have to create the ROOT directory and the FAT.
Work next on the fssynch that writes the Root and FAT to the disk
*/

/* Lab 04 - done
This laboratory is designed to continue the second part of the project.
Make sure you have Filesys and fssynch from Laboratory 3 working.
Work on newfile, rmfile, getfirstblock. Note that these functions should 
have very little code. The first two modify ROOT so you will have to write to the Sdisk using fssynch.
*/

/* Lab 05 - done
Make sure you have everything from Laboratory 3 and Laboratory 4 working.

First work on checkblock which checks if a block belongs to a file. 
Add the function to the private area of the interface.

Work on readblock, writeblock, and nextblock. 
Note that these functions should have very little code if using checkblock

Now work on delblock.
*/

class Filesys : public Sdisk
{
public:
	// This constructor reads from the sdisk and either opens the existing file 
	// system on the disk or creates one for an empty disk. Recall the sdisk is 
	// a file of characters which we will manipulate as a raw hard disk drive. 
	// This file is logically divided up into number_of_blocks many blocks where 
	// each block has block_size many characters. Information is first read from block 1 
	// to determine if an existing file system is on the disk. If a filesystem exists, 
	// it is opened and made available. Otherwise, the file system is created.
	Filesys(string diskname, int numberofblocks, int blocksize);

	// This module writes FAT and ROOT to the sdisk (closing the sdisk).
	int fsclose();

	// This module writes FAT and ROOT to the sdisk. 
	// It should be used every time FAT and ROOT are modified.
	int fssynch();
	
	// This function adds an entry for the string file in ROOT with an initial 
	// first block of 0 (empty). It returns error codes of 1 if successful and
	// 0 otherwise (no room or file already exists).
	int newfile(string file);

	// This function removes the entry file from ROOT if the file is empty 
	// (first block is 0). It returns error codes of 1 if successful and 
	// 0 otherwise (not empty or file does not exist).
	int rmfile(string file);

	// This function returns the block number of the first block in file. 
	// It returns the error code of 0 if the file does not exist.
	int getfirstblock(string file);

	// This function adds a block of data stored in the string buffer to the end
	// of file F and returns the block number. It returns error code 0 if the file 
	// does not exist, and returns -1 if there are no available blocks (file system is full!).
	int addblock(string file, string block);

	// The function removes block numbered blocknumber from file and returns an 
	// error code of 1 if successful and 0 otherwise.
	int delblock(string file, int blocknumber);

	// gets block numbered blocknumber from file and stores the data in the string buffer. 
	// It returns an error code of 1 if successful and 0 otherwise.
	int readblock(string file, int blocknumber, string& buffer);
	
	// writes the buffer to the block numbered blocknumber in file. 
	// It returns an appropriate error code.
	int writeblock(string file, int blocknumber, string buffer);
	
	// returns the number of the block that follows blocknumber in file. 
	// It will return 0 if blocknumber is the last block and -1 if some other error has occurred 
	// (such as file is not in the root directory, or blocknumber is not a block in file.)
	int nextblock(string file, int blocknumber);
	
	// This function is part of the Filesys class
	// given for Lab 6 || Project 3
	vector<string> ls();

	// given
	vector<string> block(string buffer, int b);

private:
	int rootsize;				// maximum number of entries in ROOT
	int fatsize;				// number of blocks occupied by FAT
	vector<string> filename;	// filenames in ROOT
	vector<int> firstblock;		// firstblocks in ROOT
	vector<int> fat;            // FAT

	// For lab 5
	// checks if a block belongs to a file
	bool checkblock(string file, int blocknumber);

	int addressDigitSize;	// ADDED
	static int filenameSize;// ADDED

	// added - initializes fat
	void initializeFat();	

	// added - initializes root
	void initializeRoot();

	// added - padding address block with proper length
	string padaddressblock(int s);

	// added - padding filename with proper length
	string formatfilename(string file);// Added
};

