#pragma once
#include "Filesys.h"

// LAB 6 || PROJECT 3 - DONE

/*
Project 3: done
Shell(string filename, int blocksize, int numberofblocks): This will create a shell object using the Filesys on the file filename.
int dir(): This will list all the files in the root directory.
int add(string file): add a new file using input from the keyboard
int del(string file): deletes the file
int type(string file): lists the contents of file
int copy(string file1, string file2): copies file1 to file2

See the ls function for Filesys
http://cse.csusb.edu/murphy/cse461/ls.cpp.txt
See the dir function for Shell
http://cse.csusb.edu/murphy/cse461/dir.cpp.txt
See the main program for Shell
http://cse.csusb.edu/murphy/cse461/main.cpp.txt

*/

/*
Lab 6: done
All functions return 1 if successful and 0 otherwise.
Work on the constructor.
Work on the add function. Note the add function should have an end of input character.
Work on the delete function.
Work on the type function which displays the content of the file.
Work on the copy function which copies the content of one file to another.

Add the ls function to the Filesys class and add the dir function to the Shell class. 
See the ls function for Filesys
http://cse.csusb.edu/murphy/cse461/ls.cpp.txt
See the dir function for Shell
http://cse.csusb.edu/murphy/cse461/dir.cpp.txt
See the main program for Shell
http://cse.csusb.edu/murphy/cse461/main.cpp.txt

*/
class Shell : public Filesys
{
public:

	// This will create a shell object using the Filesys on the file filename.
	Shell(string filename, int blocksize, int numberofblocks);
	// lists all files
	int dir();

	// add a new file using input from the keyboard
	int add(string file);

	// deletes the file
	int del(string file);

	//lists the contents of file
	int type(string file);

	//copies file1 to file2
	int copy(string file1, string file2);

	//int main();

	int addtofile(string file);



};

