#include "pch.h"
#include "Table.h"
#include <iostream>
#include <sstream>



// This constructor creates the table object. It creates the new (empty) files 
// flatfile and indexfile in the file system on the Sdisk using diskname.
Table::Table(string diskname, int blocksize, int numberofblocks, string flatfile, string indexfile) : Shell(diskname, blocksize, numberofblocks)
{
	this->flatfile = flatfile;
	this->indexfile = indexfile;
	this->newfile(flatfile);
	this->newfile(indexfile);

}

// This module will read records from the input file (the raw data file described above),
// add the records to the flatfile and create index records consisting of the date and 
// block number, and then add the index records to the index file. 
// (Note that index records will have 10 bytes .. 5 bytes for the date and 5 bytes for the block number.)
int Table::Build_Table(string input_file)
{
	stringstream indexstream;
	// flat stream; // where we write flat file one at a time
	ifstream infile;
	infile.open(input_file);
	// if we can not open
	if (!infile.is_open())
	{
		return 0;
	}

	string s;

	// date index keys are surrounded by a period and a whitespace
	// we start with a dot, and end with whitespace
	indexstream << ".";

	while (getline(infile, s)) {
		// where we process the raw data and get the date key
		string key = s.substr(0, 5);
		//blocksize is 128
		vector<string> blocks = block(s, getblocksize());
		// block 0 is what we want to write in the file
		int b = addblock(flatfile, blocks[0]);
		//read data in, extract key, we blocked the raw data
		// add the block which is block b to the file
		//addblock returns the block number
		// we're writing to index stream
		indexstream << key << " " << b << ".";
		// update the the num rec, so number of records is updated
		// numrec++;
		//int b = addblock(indexfile, indexstream);

		// process line write record to flat file
		// string s has the raw date
		// key is pulling first five bytes, the DATE
		// addd ???? ????
	}

	string buffer = indexstream.str();
	// converting indexstream to string
	vector<string> blocks = block(buffer, getblocksize());
	// outside the scope of while loop, can use it again
	for (int i = 0; i < blocks.size(); i++) {
		addblock(indexfile, blocks[i]);

	}
	// we have to do a new file flatfile, and a new file indexfile.
	// put it in the constructor.

	//process index file
	// write records to ostring stream, add records after blocking

	return 0;
}

// This module accepts a key value, and searches the index file with a call to IndexSearch
// for the record where the date matches the specified value. IndexSearch returns the blocknumber 
// of the block in the flat file where the target record is located. 
// This block should then be read and the record displayed.
int Table::Search(string value)
{
	// cout << "The data is ";
	int idx = IndexSearch(value);
	if (idx == 0) {
		cout << "not existing." << endl << endl;
		return 0;
	}
	string buffer;
	int error = readblock(flatfile, idx, buffer);
	buffer.erase(buffer.find_last_not_of('#') + 1);
	cout << buffer << endl << endl;
	
	return error;
}

// This module accepts a key value, and searches the index file indexfile 
// for the record where the date matches the specified value. IndexSearch then 
// returns the block number key of the index record where the match occurs.
int Table::IndexSearch(string value)
{
	istringstream instream;
	int b = getfirstblock(indexfile);
	string bigbuffer; // i think here
	value = "." + value + " ";
	if (b < 0) {
		return 0;
	}
	while (b != 0) {
		string buffer;
		int error = readblock(indexfile, b, buffer);
		b = nextblock(indexfile, b);
		bigbuffer += buffer;
	}

	int idx = bigbuffer.find(value);
	if (idx < 0)
	{
		return 0;
	}
	stringstream s(bigbuffer.substr(idx + 6, 10));

	int r;
	s >> r;

	return r;
}
