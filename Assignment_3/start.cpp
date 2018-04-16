// C++ file
// James Schnebly
// 4/17/18
// CS457 PA3

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "table.cpp"
#include <cstring>
#include <cctype>
#include <sstream>
#include <algorithm>


using namespace std;

void sanitize(string& input);
void caseChange(string& input);
string toUPPER(string input);
void loadInputVec(string input, vector<string>& loadVec);
void run();

int main(int argc, char const *argv[])
{
	run();
	return 0;
}

// Loads a temporary vector to be put into the table datavector
void loadInputVec(string input, vector<string>& loadVec)
{
	int Oldpos = input.find(',');
	loadVec.push_back(input.substr(0, Oldpos));
	int Newpos = input.find(',', Oldpos + 1);
	while(Newpos > 0)
	{
		//push into loadVec
		loadVec.push_back(input.substr(Oldpos + 1, Newpos - Oldpos - 1));

		// look for next ','
		Oldpos = Newpos;
		Newpos = input.find(',', Oldpos + 1);
	}

	loadVec.push_back(input.substr(Oldpos + 1, input.length() - Oldpos));
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

// case change function to put all keywords and table names into uppercase
void caseChange(string& inputString)
{
	string testString = inputString;
	string dictionary[] = {"FROM","CREATE","UPDATE","ALTER","DROP","INSERT","INTO","SET","WHERE","SELECT","VALUES","USE","DATABASE","TABLE","DELETE",".EXIT", "ON", "LEFT", "OUTER", "JOIN"};
	string wordCheck;
	string sanitizedString = "";

	vector<string> tokens;
	string token;
	istringstream tokenStream(testString);

	while (getline(tokenStream, token, ' '))
	{
		tokens.push_back(token);
		
	}

	size_t dictionaryElements = sizeof( dictionary ) / sizeof( dictionary[0] );
	int dictionarySize = static_cast<int>(dictionaryElements);

	for(int i=0; i<tokens.size();i++)
	{
		wordCheck = tokens[i];
		for(int iterate =0; iterate < wordCheck.size();iterate++)
		{
			wordCheck[iterate]=toupper(wordCheck[iterate]);
		}

		for(int j=0; j< dictionarySize;j++)
		{
			
			if(wordCheck == dictionary[j])
			{
			
				tokens[i]=wordCheck;
				break;
			}
		}
			//Now generate your real string. 
			if(i == (tokens.size()-1))
			{
				sanitizedString = sanitizedString + tokens[i];
			}
			else
			{
				sanitizedString = sanitizedString + tokens[i] + ' ';
			}
	}

	inputString = sanitizedString;
}

// main run function for the program
void run()
{
	string line = "";
	size_t found;
	string name = "unnamed";
	int errorNum;
	string db = "";
	string attrs = "";
	vector<Table> tableVect;
	int errorFlag = 0;
	string appendCommand = "";

	while(line != ".EXIT")
	{
		// manual testing only
		//cout << "> ";
		getline(cin, line);
		sanitize(line);

		while(line.find(';') == -1 && line.find('.') != 0 && line != "" && line.find("--") == -1)
		{
			// manual testing only
			//cout << ".. ";
			getline(cin, appendCommand);
			sanitize(appendCommand);
			if (appendCommand != "")
			{
				// append sapce + appendCommand when manually typing in
				// append only appendCommand when running test script
				line += appendCommand;
			}
			
		}

		// get rid of \r's
		sanitize(line);

		// get rid of case issues
		caseChange(line);

		if(line.find("--") != -1)
		{
			continue;
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
			name = line.substr(13, line.find("(") - 13);

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

		// left outer join handler
		else if(line.find("LEFT OUTER JOIN") != -1)
		{
			cout << "left outer join" << endl;
		}

		// Select (natural inner join) Query handler that returns the empty table
		else if (line.find("SELECT *") != -1 && (line.find("WHERE") != -1 || line.find("ON") != -1))
		{
			if(line.find("WHERE") != -1)
			{
				cout << "natural join" << endl;
				name = line.substr(line.find("FROM") + 5, line.find(',') - line.find("FROM") - 7);
				string name2 = line.substr(line.find(',') + 2, line.find("WHERE") - line.find(',') - 5);

				string attr = line.substr(line.find('.') + 1, line.find('=') - line.find('.') - 2);
				string attr2 = line.substr(line.find_last_of('.') + 1, line.find(';') - line.find('=')- 4);
			
				// indices for the two tables in the tableVect
				int Tindex1, Tindex2;


				for (Tindex1 = 0; Tindex1 < tableVect.size(); Tindex1++)
				{
					if(name == tableVect[Tindex1].getName() && db == tableVect[Tindex1].getDBA())
					{
				 		int attrIndex = tableVect[Tindex1].getIndex(attr);
				 		break;
				 	}
				 }

				for (Tindex2 = 0; Tindex2 < tableVect.size(); Tindex2++)
				{
					if(name2 == tableVect[Tindex2].getName() && db == tableVect[Tindex2].getDBA())
					{
			 			int attr2Index =  tableVect[Tindex2].getIndex(attr2);
			 			break;
				 	}
				}

				// compare values in index's for each table

				// need to create Table::getValue(int row, int col)
				// that returns the value for that row + col
				// call in a nested for loop and compare each iteration of the 
				// outer for loop
//START HERE     /////////////////////////////////////////////////////////////////////////////
				for(int i = 0; ;i++)
				{
					for(int j = 0; ;j++)
					{

					}
				}

			}
			else if(line.find("ON") != -1)
			{
				cout << "inner join" << endl;
			}
			


			// OLD CODE
			// --------
			// caseChange(name);
			// int i;

			// for (i = 0; i < tableVect.size(); i++)
			// {
			// 	if(name == tableVect[i].getName() && db == tableVect[i].getDBA())
			// 	{
			// 		tableVect[i].printTable();
			// 		break;
			// 	}
			// }
			// if(i == tableVect.size())
			// {
			// 	cout << "-- Table not located in this database." << endl;
			// }
		}

		// Select Query handler that returns the empty table
		else if (line.find("SELECT *") != -1)
		{
			name = line.substr(14, line.length() - 15);
			caseChange(name);
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
			
			for (i = 0; i < tableVect.size(); i++)
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
		// insert handler that inserts data into table if table is found
		else if(line.find("INSERT INTO") != -1)
		{
			int i;
			name = line.substr(12, line.find("values") - 13);

			for(i = 0; i < tableVect.size(); i++)
			{
				if(tableVect[i].getName() == name && tableVect[i].getDBA() == db)
				{
					break;
				}
			}

			// if table is found do insert logic
			if(i != tableVect.size())
			{
				vector<string> test;

				int pos = line.find("(");
				attrs = line.substr(pos + 1, line.length() - 3 - pos);

				// strip spaces
				attrs.erase(remove_if(attrs.begin(), attrs.end(), ::isspace), attrs.end());


				loadInputVec(attrs, test);
				tableVect[i].insert2Vector(test);


				cout << "-- 1 new record inserted." << endl;
			}
			else
			{
				cout << "-- Invalid table" << endl;
			}
		}
		// Update handler that updates tuples based on the parameters given
		else if(line.find("UPDATE") != -1)
		{
			int i = 0;
			name = line.substr(7, line.find("SET") - 8);

			for(i = 0; i < tableVect.size(); i++)
			{
				if(tableVect[i].getName() == name && tableVect[i].getDBA() == db)
				{
					break;
				}
			}

			// if table is found do update logic
			if(i != tableVect.size())
			{

				string whereKey = line.substr(line.find("WHERE") + 6, line.find_last_of("=") - 6 - line.find("WHERE"));
				string whereVal = line.substr(line.find_last_of("=") + 2, line.find(";") - 2 - line.find_last_of("="));
				
				string setKey = line.substr(line.find("SET") + 4, line.find("=") - 5 - line.find("SET"));
				string setVal = line.substr(line.find("=") + 2, line.find("WHERE") - 3 - line.find("="));

				int whereIndex = tableVect[i].getIndex(whereKey);
				int setIndex = tableVect[i].getIndex(setKey);

				cout << tableVect[i].update(whereIndex, setIndex, whereVal, setVal) << " record(s) modified." << endl;


			}
			else
			{
				cout << "-- Invalid table" << endl;
			}
		}
		// Delete handler that deletes tuples based on the command that is given with the DELETE keyword
		else if(line.find("DELETE") != -1)
		{
			int i = 0;
			name = line.substr(12, line.find("WHERE") - line.find("FROM") - 6);

			for(i = 0; i < tableVect.size(); i++)
			{
				if(tableVect[i].getName() == name && tableVect[i].getDBA() == db)
				{
					break;
				}
			}

			// if table is found do delete logic
			if(i != tableVect.size())
			{
				string whereKey = "";
				string whereVal = "";

				// equal to handler
				if(line.find("=") != -1)
				{
					whereKey = line.substr(line.find("WHERE") + 6, line.find_last_of("=") - 7 - line.find("WHERE"));
					whereVal = line.substr(line.find_last_of("=") + 2, line.find(";") - 2 - line.find_last_of("="));
					int whereIndex = tableVect[i].getIndex(whereKey);
					char op = 'e';
					cout << tableVect[i].deleteT(whereIndex, whereVal, op) << " record(s) deleted." << endl;
				}
				// less than handler
				else if(line.find("<") != -1)
				{
					whereKey = line.substr(line.find("WHERE") + 6, line.find_last_of("<") - 7 - line.find("WHERE"));
					whereVal = line.substr(line.find_last_of("<") + 2, line.find(";") - 2 - line.find_last_of("<"));	
					int whereIndex = tableVect[i].getIndex(whereKey);
					char op = 'l';
					cout << tableVect[i].deleteT(whereIndex, whereVal, op) << " record(s) deleted." << endl;			
				}
				// greater thn handler
				else if(line.find(">") != -1)
				{
					whereKey = line.substr(line.find("WHERE") + 6, line.find_last_of(">") - 7 - line.find("WHERE"));
					whereVal = line.substr(line.find_last_of(">") + 2, line.find(";") - 2 - line.find_last_of(">"));
					int whereIndex = tableVect[i].getIndex(whereKey);
					char op = 'g';
					cout << tableVect[i].deleteT(whereIndex, whereVal, op) << " record(s) deleted." << endl;
				}
				else
				{
					cout << "-- Invalid Operator." << endl;
				}
			}
			else
			{
				cout << "-- Invalid table." << endl;
			}
		}

		// Query Handler that outputs the necessary tuples depending on command it is given
		else if(line.find("SELECT") != -1)
		{
			int i = 0;
			name = line.substr(line.find("FROM") + 5, line.find("WHERE") - line.find("FROM") - 6);

			for(i = 0; i < tableVect.size(); i++)
			{
				if(tableVect[i].getName() == name && tableVect[i].getDBA() == db)
				{
					break;
				}
			}
			// if table is found do select logic
			if(i != tableVect.size())
			{
				if(line.find("!=") != -1)
				{
					string whereKey = line.substr(line.find("WHERE") + 6, line.find_last_of("!=") - 8 - line.find("WHERE"));
					string whereVal = line.substr(line.find_last_of("!=") + 2, line.find(";") - 2 - line.find_last_of("!="));
					int whereIndex = tableVect[i].getIndex(whereKey);
					char op = 'n'; // not equal to
					//
					string colNames = line.substr(7, line.find("FROM") - 7);
					vector <int> indices;
					indices.push_back(tableVect[i].getIndex(colNames.substr(0, colNames.find(",") - 1)));
					indices.push_back(tableVect[i].getIndex(colNames.substr(colNames.find(",") + 1, colNames.length() - colNames.find(",") - 1)));
					tableVect[i].queryTable(whereIndex,whereVal,indices);
					//

				}
				else
				{
					cout << "-- Invalid operator.";
				}
			}
		}

		errorFlag = 0;
	}

	for(int i = 0; i < tableVect.size(); i++)
	{
		//tableVect[i].fileWrite();
	}
	cout << "-- All done!" << endl;
}
