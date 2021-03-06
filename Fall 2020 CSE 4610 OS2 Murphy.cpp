// Fall 2020 CSE 4610 OS2 Murphy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "PasswordFile.h"
#include "Sdisk.h"
#include "Filesys.h"
#include "Shell.h"
#include "Table.h"
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

// Alannah Gavuzzi 
// This is entirely completed.

using namespace std;
/*
int main()
{
	Shell *shell = new Shell("AGtest", 256, 128);

	delete shell;
}
*/

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}


int main()
{
	//
	//This main program inputs commands to the shell.
	//It inputs commands as : command op1 op2
	//You should modify it to work for your implementation.
	//
	//Sdisk sdisk = Sdisk("sdisk.txt", 256, 128);
	//Filesys fsys = Filesys("sdisk.txt", 256, 128);
	//Shell shell = Shell("sdisk.txt", 256, 128);
	Table table = Table("sdisk.txt", 256, 128, "flat", "index");
	table.Build_Table("data.txt");

	string s;
	string command = "go";
	string op1, op2;

	// added
	string op3;

	while (command != "quit")
	{
		command.clear();
		op1.clear();
		op2.clear();

		op3.clear();
		
		cout << "$";
		getline(cin, s);
		int firstblank = s.find(' ');
		if (firstblank < s.length()) s[firstblank] = '#';
		int secondblank = s.find(' ');

		if (secondblank < s.length()) s[secondblank] = '#';
		int thirdblank = s.find(' ');

		command = s.substr(0, firstblank);
		if (firstblank < s.length())
			op1 = s.substr(firstblank + 1, secondblank - firstblank - 1);
		if (secondblank < s.length())
			op2 = s.substr(secondblank + 1, thirdblank - secondblank - 1);

		if (thirdblank < s.length())
			op3 = s.substr(thirdblank + 1);


		if (command == "dir")
		{
			table.dir();
		}
		if (command == "search")
		{
			table.Search(op1);
			// The variable op1 is the data
		}
		if (command == "add")
		{
			// The variable op1 is the new file
			table.add(op1);
		}
		if (command == "del")
		{
			// The variable op1 is the file
			table.del(op1);
		}
		if (command == "type")
		{
			// The variable op1 is the file
			table.type(op1);
		}
		if (command == "copy")
		{
			// The variable op1 is the source file and the variable op2 is the destination file.
			table.copy(op1, op2);
		}
		if (command == "What" 
			|| command == "what")
		{
			
			// "What record has date=50?"
			// record
			// has
			// date=50?
			replace(op3,"?","");
			//date=50
			replace(op3, "=", " ");
			//date 50
			stringstream param(op3);
			string column;
			string value;
			param >> column >> value;
			if (column == "date") {
				table.Search(value);
			}
			else {
				cout << "Only 'date' is indexed. " << endl;
			}
		}

	}
	return 0;
}
/*
vector<string> block(string s, int num) {
	vector<string> returnString;
	for (unsigned i = 0; i < s.length(); i += num) {
		returnString.push_back(s.substr(i, num));
	}

	return returnString;
}

int main()
{
	//Sdisk disk1("disk1", 256, 128);
	Filesys fsys("disk1", 256, 128);
	fsys.newfile("file1");
	fsys.newfile("file2");

	string bfile1;
	string bfile2;
//
	for (int i = 1; i <= 1024; i++)
	{
		bfile1 += "1";
	}

	vector<string> blocks = block(bfile1, 128);

	int blocknumber = 0;

	for (int i = 0; i < blocks.size(); i++)
	{
		blocknumber = fsys.addblock("file1", blocks[i]);
	}
//
	fsys.delblock("file1", fsys.getfirstblock("file1"));

	for (int i = 1; i <= 2048; i++)
	{
		bfile2 += "2";
	}

	blocks = block(bfile2, 128);

	for (int i = 0; i < blocks.size(); i++)
	{
		blocknumber = fsys.addblock("file2", blocks[i]);
	}

	//fsys.delblock("file2", blocknumber);
	for (int i = 0; i < blocks.size(); i++)
	{
		//cout << fsys.checkblock("file2", i) << endl;
		//blocknumber = fsys.addblock("file2", blocks[i]);
	}

return 0;
}
*/
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


