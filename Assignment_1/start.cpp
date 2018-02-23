// C++ file
// James Schnebly

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "table.cpp"


using namespace std;

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


		if(line.find(';') == -1 && line.find('.') != 0)
		{
			cout << "Must end command with ';'." << endl;
		}

		else if(line.find("CREATE DATABASE") != -1)
		{	
			name = line.substr(16, line.length() - 17);
			errorNum = system(("mkdir " + name).c_str());
			if(errorNum == 0)
			{
				cout << "-- Database " + name + " created." << endl;
			}
			
		}

		else if(line.find("DROP DATABASE") != -1)
		{
			name = line.substr(14, line.length() - 15);
			errorNum = system(("rmdir " + name).c_str());
			if(errorNum == 0)
			{
				cout << "-- Database " + name + " deleted." << endl;
			}
		}

		else if(line.find("CREATE TABLE") != -1)
		{
			name = line.substr(13, line.find("(") - 14);

			for(int i = 0; i < tableVect.size(); i++)
			{
				if(name == tableVect[i].getName())
				{
					cout << "-- Failed to create table " + name + " becuase it already exists." << endl;
					errorFlag = 1;
					break;
				}
			}

			if(errorFlag == 0)
			{
				cout << "check 1" << endl;
				if(db != "")
				{
					cout << "check 2" << endl;
					errorNum = system(("touch " + db + "/" + name + ".txt").c_str());
					if(errorNum == 0)
					{
						cout << "check 3" << endl;
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
						cout << tableVect.size() << endl;
						tableVect.erase(tableVect.begin() + i);
						cout << tableVect.size() << endl;
					}

				}
				cout << "-- Table " + name + " deleted." << endl;
			}
		}

		else if(line.find("USE") != -1)
		{
			db = line.substr(4, line.length() - 5);
			errorNum = system(("cd " + db).c_str());
			if(errorNum == 0)
			{
				cout << "-- Using Database " + db + "." << endl;
			}

		}

		else if (line.find("SELECT *") != -1)
		{
			name = line.substr(14, line.length() - 15);
			int i;

			for (i = 0; i < tableVect.size(); i++)
			{
				if(name == tableVect[i].getName())
				{
					if(db == tableVect[i].getDBA())
					{
						tableVect[i].printTable();
						break;
					}
					else
					{
						cout << "-- Table not located in this database." << endl;
					}
				}
			}

			if (i == tableVect.size())
			{
				cout << "-- Table does not exist." << endl;
				
			}
		}

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
					break;
				}

			}
			if (i == tableVect.size())
			{
				cout << "-- Table does not exist in this database." << endl;
				
			}
		}




		errorFlag == 0;
	}
	return 0;
}
