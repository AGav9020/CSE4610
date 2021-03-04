#include "pch.h"
#include "PasswordFile.h"

#include <string>
#include <vector>
#include <iostream>


int PasswordFile::salt = 1;

// The constructor accepts a filename, and reads the file one-line 
// at a time and adds values to the vectors user and password
// opens the file and reads the names/passwords in the vectors user and password.
PasswordFile::PasswordFile(string filename)
{
	this->filename = filename;
	ifstream infile(this->filename);
	string fuser;
	string fpasswd;
	while (infile >> fuser >> fpasswd)
	{
		user.push_back(fuser);
		password.push_back(decrypt(fpasswd));
		
	
	}
	infile.close();
}


// This adds a new user/password to the vectors and writes the vectors to the file filename
// The function addpw adds a user/password pair to end of each vector
void PasswordFile::addpw(string newuser, string newpassword)
{
	bool isFound = false;
	for (int i = 0; i < user.size(); i++) {

		if (user[i] == newuser) {
			isFound = true;
		}

	}
	if (isFound == false) {
		user.push_back(newuser);
		password.push_back(newpassword);
		synch();
	}


}

// returns true if user exists and password matches
bool PasswordFile::checkpw(string usr, string passwd)
{
	bool isMatched = false;
	for (int i = 0; i < user.size(); i++) {

		if (user[i] == usr) {
			if (password[i] == passwd) {
				isMatched = true;
			}
			break;
		}

	}
	return isMatched;
}

void PasswordFile::newsalt(int ns)
{
	salt = ns;
}


void PasswordFile::synch()
{
	ofstream myfile;
	myfile.open(this->filename);
	for (int i = 0; i < user.size(); i++) {
		myfile << user[i] << " " << encrypt(password[i]) << "\n";
	}
	
	myfile.close();
}

string PasswordFile::encrypt(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		s[i] += salt;
	}
	return s;
}

string PasswordFile::decrypt(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		s[i] -= salt;
	}
	return s;
}
