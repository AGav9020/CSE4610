#pragma once
#include <iostream>
#include <string>
#include "pch.h"
#include <vector>
#include <fstream>

using namespace std;

// LAB 2 || Project 1 - DONE

// Project 1 - done
// The first part of this project requires that you implement a class 
// that will be used to simulate a disk drive. The disk drive will have 
// numberofblocks many blocks where each block has blocksize many bytes. 

// Lab 2 - done
// This laboratory is designed to get you started with the project and random access file I/O
// Open your source file and write or copy the code for the class interface for the Sdisk.
// You can copy a sample main program from here: http://cse.csusb.edu/murphy/cse461/prog1main.txt
// Create function stubs(functions with no code) for the class functions.
// Work first on the constructor that creates the Sdisk.
// Now work on putblock to open the file and write a block.
// Finally work on getblock to open the file and get a block.
// Now test with the example main program.
class Sdisk
{
public:
	// This constructor incorporates the creation of the disk with the "formatting" 
	// of the device. It accepts the integer values numberofblocks, blocksize, a 
	// string diskname and creates a Sdisk (software-disk). The Sdisk is a file of 
	// characters which we will manipulate as a raw hard disk drive. The function will 
	// check if the file diskname exists. If the file exists, it is opened and treated 
	// as a Sdisk with numberofblocks many blocks of size blocksize. If the file does 
	// not exist, the function will create a file called diskname which contains 
	// numberofblocks*blocksize many characters. This file is logically divided up into 
	// numberofblocks many blocks where each block has blocksize many characters. 
	Sdisk(string diskname, int numberofblocks, int blocksize);
	
	// retrieves block blocknumber from the disk and stores the data in the string buffer. 
	// It returns an error code of 1 if successful and 0 otherwise.
	int getblock(int blocknumber, string& buffer);

	// writes the string buffer to block blocknumber. It returns an error code of 1 if successful and 0 otherwise.
	int putblock(int blocknumber, string buffer);

	// IMPLEMENTATION GUIDELINES : It is essential that your software satisfies the specifications (the above three)
	// These will be the only functions (in your system) which physically access the Sdisk. 
	// NOTE that you must also write drivers to test and demonstrate your program.

	int getnumberofblocks(); // accessor function
	int getblocksize(); // accessor function
private:
	string diskname;		// file name of software-disk
	int numberofblocks;		// number of blocks on disk
	int blocksize;		    // block size in bytes
	static char emptyspot;	// ADDED: empty value for disk
};

