#pragma once
#include "Shell.h"

// LAB 7, 8 || PROJECT 4 - DONE

/* Project 4 - DONE
In this part of the project, you are going to create a database system
with a single table which uses the file system from Project II.
The input file will consist of records associated with Art History.
The data file you will use as input consists of records with the following format:
The data (180 records) is http://cse.csusb.edu/murphy/cse461/data.txt

In the data file, an asterisk is also used to delimit each field and the
last character of each record is an asterisk. The width of any record is
never greater than 120 bytes. Therefore you can block the data accordingly.

The project will also require you to design and implement the machine-user
interface. Your system must be capable of answering queries of the form

	"What record has date=50?"

You can implement this function in any way you choose, but it should NOT be a
member function of the Table class. Instead, it should use the Search function.
*/

/* Lab 7 - DONE
ALL functions return 1 if successful and 0 otherwise.
Work on the constructor.
Work on the Build_table function
*/

/* Lab 8 - DONE
Work on the IndexSearch function.
Work on the Search function.
Use the main program here: http://cse.csusb.edu/murphy/cse461/main2.cpp.txt
*/



class Table :public Shell
{

	// note that all functions return 1 if succesful and 0 otherwise
public:
	// This constructor creates the table object. It creates the new (empty) files 
	// flatfile and indexfile in the file system on the Sdisk using diskname.
	Table(string diskname, int blocksize, int numberofblocks, string flatfile, string indexfile);

	// This module will read records from the input file (the raw data file described above),
	// add the records to the flatfile and create index records consisting of the date and 
	// block number, and then add the index records to the index file. 
	// (Note that index records will have 10 bytes .. 5 bytes for the date and 5 bytes for the block number.)
	int Build_Table(string input_file);

	// This module accepts a key value, and searches the index file with a call to IndexSearch
	// for the record where the date matches the specified value. IndexSearch returns the blocknumber 
	// of the block in the flat file where the target record is located. 
	// This block should then be read and the record displayed.
	int Search(string value);

private:
	string flatfile;
	string indexfile;

	// This module accepts a key value, and searches the index file indexfile 
	// for the record where the data matches the specified value. IndexSearch then 
	// returns the block number key of the index record where the match occurs.
	int IndexSearch(string value);
};

