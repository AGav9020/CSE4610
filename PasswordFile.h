#include "pch.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

// LAB 1 - DONE
/*
In this laboratory, we are going to maintain a username - password system 
by storing the usernames and passwords in a file.The file will consist of 
a single username and password per line with a space in between.
1.
Begin by creating a class PasswordFile which has the following interface
2.
Now create a password.txt file with some entries*/
class PasswordFile
{
public:
	// The constructor accepts a filename, and reads the file one-line 
	// at a time and adds values to the vectors user and password
	// opens the file and reads the names/passwords in the vectors user and password.
	PasswordFile(string filename);	

	// This adds a new user/password to the vectors and writes the vectors to the file filename
	// The function addpw adds a user/password pair to end of each vector
	void addpw(string newuser, string newpassword);	

	// returns true if user exists and password matches
	bool checkpw(string usr, string passwd);		
	static void newsalt(int ns);					// encryption
private:
	static int salt;			// encryption
	string filename;			// the file that contains password information
	vector<string> user;		// the list of usernames
	vector<string> password;	// the list of passwords
	void synch();				// writes the user / password vectors to the password file
	
	string encrypt(string s);	// encryption
	string decrypt(string s);	// encryption
};