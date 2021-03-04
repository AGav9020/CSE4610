#include "pch.h"
#include "Shell.h"


// This will create a shell object using the Filesys on the file filename.
Shell::Shell(string filename, int blocksize, int numberofblocks) : Filesys(filename, blocksize, numberofblocks)
{
	cout << "\tAlannah Gavuzzi's Shell\n\t-------------------\n";
	//this->main();
}

// lists all files
int Shell::dir()
{
	// given 
	// dir lists files in the class Shell
	// Prototype: int Shell::dir() 
	vector<string> flist = ls();
	cout << "Directory of Files:\n";
	for (int i = 0; i < flist.size(); i++)
	{
		cout << flist[i] << endl;
	}
	cout << "\t" << flist.size() << " file(s) found\n\n";
	return 0;
}

// add a new file using input from the keyboard
int Shell::add(string file)
{
	int result = this->newfile(file);
	if (result == 1) {
	this->addtofile(file);
	}

	cout << "\nFile added.\n\n";
	return result;
}

// deletes the file
int Shell::del(string file)
{
	int currentBlock = this->getfirstblock(file);
	if (currentBlock == -1) {
		cout << "No file found to delete.\n";
		return 0;
	}
	while ((currentBlock = this->getfirstblock(file)) > 0) {
		this->delblock(file, currentBlock);
	}
	this->rmfile(file);
	cout << "\nFile deleted.\n\n";

	return 1;
}

//lists the contents of file
int Shell::type(string file)
{

	string fileBuffer = "";
	string blockBuffer = "";
	int currentBlock = this->getfirstblock(file);
	if (currentBlock != 0 && currentBlock !=-1)
	{
		while (currentBlock != 0) 
		{
			this->readblock(file, currentBlock, blockBuffer);
			fileBuffer += blockBuffer;


			// incrementor
			currentBlock = this->nextblock(file, currentBlock);		   
		}

		
	}
	else {
		cout << "Error occurred.\n";
		return 0;
	}

	fileBuffer.erase(fileBuffer.find_last_not_of('#') + 1);


	cout << fileBuffer << endl;

	return 1;

}

// copies file1 to file2
// file1 = source
// file2 = destination
int Shell::copy(string file1, string file2)
{
	string sourceFile = file1;
	string destFile = file2;

	if (this->getfirstblock(sourceFile) == -1) {
		cout << "Can't find source file.\n\n";
		return 0;
	}
	else if (this->getfirstblock(destFile) >= 0) {
		cout << "Destination exists already.\n\n";
		return 0;
	}

	if (this->newfile(destFile) == 0) {
		// one error here could be theres not enough space.
		cout << "File creation failed. Do you have enough space?\n\n";
		return 0;
	}
	int currentBlock = this->getfirstblock(sourceFile);
	string buffer;
	while (currentBlock !=0) {
		readblock(sourceFile, currentBlock, buffer);
		addblock(destFile, buffer);

		currentBlock = this->nextblock(sourceFile, currentBlock);
	}


	return 1;
}
/*
int Shell::main()
{
	//
	//This main program inputs commands to the shell.
	//It inputs commands as : command op1 op2
	//You should modify it to work for your implementation.
	//
	string s;
	string command = "go";
	string op1, op2;

	while (command != "quit")
	{
		command.clear();
		op1.clear();
		op2.clear();
		cout << "$";
		getline(cin, s);
		int firstblank = s.find(' ');
		if (firstblank < s.length()) s[firstblank] = '#';
		int secondblank = s.find(' ');
		command = s.substr(0, firstblank);
		if (firstblank < s.length())
			op1 = s.substr(firstblank + 1, secondblank - firstblank - 1);
		if (secondblank < s.length())
			op2 = s.substr(secondblank + 1);
		if (command == "dir")
		{
			// use the ls function
			this->dir();
		}
		else if (command == "add")
		{
			// The variable op1 is the new file
			this->add(op1);
		}
		else if (command == "del")
		{
			// The variable op1 is the file
			this->del(op1);
		}
		else if (command == "type")
		{
			this->type(op1);
			// The variable op1 is the file
		}
		else if (command == "copy")
		{
			this->copy(op1, op2);
			// The variable op1 is the source file and the variable op2 is the destination file.
		}
		else if (command == "quit")
		{
			break;
		}
		else {
			cout << "'" << command << "' is not recognized as a command. Type \"quit\" to end this session. \n\n";
		}
	}

	return 0;
}
*/
int Shell::addtofile(string file)
{/*
	// DNE
	if (getfirstblock(file) == -1) {
		cout << "File not found." << endl;
		return 0;
	}
//
	int lastBlock;
	for (lastBlock = this->getfirstblock(file); lastBlock != 0 && this->nextblock(file, lastBlock) != 0; lastBlock = nextblock(file, lastBlock));

	string totalBuffer;
	if (lastBlock != 0) {
		this->readblock(file, lastBlock, totalBuffer);
		this->delblock(file, lastBlock);
		totalBuffer = totalBuffer.substr(0, totalBuffer.find_first_of('#'));
	}
	*/
	string buffer;
	string totalBuffer;
	cout << "Enter Data(Press Enter Key to stop input): " << endl;
	getline(cin, buffer);
	totalBuffer += buffer;
	
	vector<string> blocks = block(totalBuffer, this->getblocksize());

	for (int i = 0; i < blocks.size(); i++)
		this->addblock(file, blocks[i]);

	return 1;
}


