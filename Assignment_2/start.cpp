// C++ file
// James Schnebly
// 
// CS457 PA2

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "table.cpp"
#include <cstring>
#include <cctype>


using namespace std;

void sanitize(string& input);
void caseChange(string& input);
string toUPPER(string input);

string keywords[] = {"CREATE", "DATABASE", "USE", "TABLE", "INSERT", "INTO", "VALUES", "SELECT",
					"FROM", "UPDATE", "SET", "WHERE", "DELETE", "DROP", "ALTER"};

int main(int argc, char const *argv[])
{
	string line = "";
	size_t found;
	string name = "unnamed";
	int errorNum;
	string db = "";
	string attrs = "";
	vector<Table> tableVect;
	int errorFlag = 0;

	while(line != ".EXIT")
	{
		cout << "> ";
		getline(cin, line);

		// get rid of \r's
		sanitize(line);

		// get rid of case issues
		caseChange(line);
		cout << "Line = " << line << endl;

		if(line.find("--") != -1)
		{
			continue;
		}

		// check if the command was given properly
		if(line.find(';') == -1 && line.find('.') != 0 && line != "")
		{

			cout << "Must end command with ';'." << endl;
		}

		// create database handler that creates a folder with correct name
		else if(line.find("CREATE DATABASE") != -1)
		{	
			name = line.substr(16, line.length() - 17);
			errorNum = system(("mkdir " + name).c_str());
			if(errorNum == 0)
			{
				cout << "-- Database " + name + " created." << endl;
			}
			
		}

		// delete database handler that removes folder
		else if(line.find("DROP DATABASE") != -1)
		{
			name = line.substr(14, line.length() - 15);
			errorNum = system(("rmdir " + name).c_str());
			if(errorNum == 0)
			{
				cout << "-- Database " + name + " deleted." << endl;
			}
		}

		// create table handler
		// this function creates a Table instance and assigns the name
		// parameters (attributes), and database associated with it
		else if(line.find("CREATE TABLE") != -1)
		{
			name = line.substr(13, line.find("(") - 14);

			for(int i = 0; i < tableVect.size(); i++)
			{
				if(name == tableVect[i].getName() && db == tableVect[i].getDBA())
				{
					cout << "-- Failed to create table " + name + " becuase it already exists." << endl;
					errorFlag = 1;
					break;
				}
			}

			if(errorFlag == 0)
			{
				if(db != "")
				{
					errorNum = system(("touch " + db + "/" + name + ".txt").c_str());
					if(errorNum == 0)
					{
						attrs = line.substr(line.find("(") + 1, line.length() - 3 - line.find("("));
						Table* pushT = new Table(name, attrs, db);
						tableVect.push_back(*pushT);
						cout << "-- Table " + name + " created." << endl;

					}
				}
				else
				{
					cout << "-- Failed to create " + name + " becuase you are not using a database." << endl;
				}
			}

		}

		// Drop table handler that deletes table from associated database
		else if(line.find("DROP TABLE") != -1)
		{
			int i;
			name = line.substr(11, line.length() - 12);
			errorNum = system(("rm " + db + "/" + name + ".txt").c_str());
			if (errorNum == 0)
			{
				for (i = 0; i < tableVect.size(); ++i)
				{
					if (name == tableVect[i].getName() && db == tableVect[i].getDBA())
					{
						tableVect.erase(tableVect.begin() + i);
					}

				}
				cout << "-- Table " + name + " deleted." << endl;
			}
		}

		// Use handler that changes functioning database
		else if(line.find("USE") != -1)
		{
			db = line.substr(4, line.length() - 5);
			errorNum = system(("cd " + db).c_str());
			if(errorNum == 0)
			{
				cout << "-- Using Database " + db + "." << endl;
			}

		}

		// Select Query handler that returns the empty table
		else if (line.find("SELECT *") != -1)
		{
			name = line.substr(14, line.length() - 15);
			int i;

			for (i = 0; i < tableVect.size(); i++)
			{
				if(name == tableVect[i].getName() && db == tableVect[i].getDBA())
				{
					tableVect[i].printTable();
					break;
				}
			}
			if(i == tableVect.size())
			{
				cout << "-- Table not located in this database." << endl;
			}
		}

		// Alter Table handler that adds columns to table given
		else if(line.find("ALTER TABLE") != -1)
		{
			int i;
			name = line.substr(12, line.find("ADD") - 13);
			string addedParameters = line.substr(line.find("ADD") + 4, line.length() - (line.find("ADD") + 5));
			
			for (i = 0; i < tableVect.size(); ++i)
			{
				if (name == tableVect[i].getName() && db == tableVect[i].getDBA())
				{
					tableVect[i].setAttrs(tableVect[i].getAttrs() + ", " + addedParameters);
					cout << "-- Table " + name + " modified." << endl;
					break;
				}

			}
			if (i == tableVect.size())
			{
				cout << "-- Table does not exist in this database." << endl;
				
			}
		}
		else if(line.find("INSERT INTO") != -1)
		{
			name = line.substr(12, line.find("values") - 13);
			cout << name << endl;

		}




		errorFlag = 0;
	}

	cout << "-- All done!" << endl;
	return 0;
}

// Function to get rid of those pesky carriage returns
void sanitize(string& input)
{
	string myString;

	if (input.find('\r') == string::npos)
	{
		return;
	}
	else
	{
		for(int i = 0; i < input.size(); i++)
		{
			if (input[i] == '\r')
			{
				continue;
			}
			else
			{
				myString.push_back(input[i]);
			}
		}
		input = myString;
		return;
	}
}

void caseChange(string& input)
{
	char* testSTR = const_cast<char*>(input.c_str());
	vector<string> outputSTRs;
	char* pch;
	string check;
	string output = "";
	int flag = 0;

	cout << "TEST 1" << endl;

	pch = strtok(testSTR," ");
 	while (pch != NULL)
  	{
   		outputSTRs.push_back(string(pch));
    	pch = strtok(NULL, " ");
  	}

  	for(int i = 0; i < outputSTRs.size(); i++)
  	{
  		cout << "TEST 2" << endl;
  		check = toUPPER(outputSTRs[i]);

  		for(int j = 0; j < 15; j++)
  		{	
  			if(check == ".EXIT")
  			{
  				output += check;
  				flag = 1;
  				break;
  			}
	  		else if(check == keywords[j])
	  		{
	  			output += (keywords[j] + " ");
	  			flag = 1;
	  			break;
	  		}

	  	}

	  	if(flag == 0 && outputSTRs[i].find(';') == -1)
	  	{
	  		output += (outputSTRs[i] + " ");
	  	}
	  	else if(flag == 0)
	  	{
	  		output += outputSTRs[i];
	  	}

	  	flag = 0;
  	}	

  input = output;

}

string toUPPER(string input)
{
	string output = "";

	for(int i; i < input.length(); i++)
	{
		output += toupper(input[i]);
	}

	return output;
}
