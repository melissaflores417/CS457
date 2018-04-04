// C++ file
// James Schnebly
// 3/27/18
// CS457 PA2

#include <iostream>
#include <fstream>
#include "table.h"

using namespace std;	

Table::Table(string name, string attrs, string db)
{
	Tname = name;
	Tparameters = attrs;
	DBA = db;
}

Table::~Table()
{
	Tname = "";
	Tparameters = "";
	DBA = "";
}

string Table::getName()
{
	return Tname;
}

string Table::getAttrs()
{
	return Tparameters;
}

string Table::getDBA()
{
	return DBA;
}

// print table function that outputs attributes in a prettier format (pipe seperated)
void Table::printTable()
{

	string line  = Tparameters;
	int pos = line.find(',');
	while(pos > 0)
	{
		line.replace(pos, 2, " | ");
		pos = line.find(',');
	}
	cout << line << endl;

	for(int i = 0; i < dataVect.size(); i++)
	{
		cout << dataVect[i][0] << '|' << dataVect[i][1] << '|' << dataVect[i][2] << endl;
	}
}

void Table::setAttrs(string a)
{
	Tparameters = a;
}

void Table::insert2Vector(vector<string> input)
{
	dataVect.push_back(input);
}

int Table::getIndex(string colName)
{
	int pos = Tparameters.find(colName);
	int commaPos = Tparameters.find(",");
	int index = 0;
	while(pos > commaPos && commaPos != -1)
	{
		index++;
		commaPos = Tparameters.find(",", commaPos + 1);
	}

	return index;
}

int Table::update(int whereIndex, int setIndex, string whereVal, string setVal)
{
	int counter = 0;

	for (int i = 0; i < dataVect.size(); i++)
	{
		if(dataVect[i][whereIndex] == whereVal)
		{
			dataVect[i][setIndex] = setVal; 
			counter++;
		}
	}

	return counter;
}

int Table::deleteT(int whereIndex, string whereVal, char op)
{
	int counter = 0;

	if(op == 'e')
	{	
		for (int i = 0; i < dataVect.size(); i++)
		{
			if(dataVect[i][whereIndex] == whereVal)
			{
				dataVect.erase(dataVect.begin() + i);
				counter++;
			}
		}
	}
	if(op == 'g')
	{
		for (int i = 0; i < dataVect.size(); i++)
		{
			if(stoi(dataVect[i][whereIndex]) > stoi(whereVal))
			{
				dataVect.erase(dataVect.begin() + i);
				counter++;
			}
		}
	}
	if(op == 'l')
	{
		for (int i = 0; i < dataVect.size(); i++)
		{
			if(stoi(dataVect[i][whereIndex]) < stoi(whereVal))
			{
				dataVect.erase(dataVect.begin() + i);
				counter++;
			}
		}
	}

	return counter;	
}
void Table::queryTable(int whereIndex, string whereVal, vector<int> indices)
{

	string line  = Tparameters;
	int pos = line.find(',');
	while(pos > 0)
	{
		line.replace(pos, 2, " | ");
		pos = line.find(',');
	}

	// 
	line = line.substr(line.find("|") + 2, line.length() - line.find("|") - 1);
	//
	cout << line << endl;


	for (int i = 0; i < dataVect.size(); i++)
	{
		if(dataVect[i][whereIndex] != whereVal)
		{
			cout << dataVect[i][indices[0]] << '|' << dataVect[i][indices[1]] << endl;
		}
	}
}
void Table::fileWrite()
{
	ofstream fout;
	fout.clear();
	fout.open(DBA + '/' + Tname + ".txt");

	string line  = Tparameters;
	int pos = line.find(',');
	while(pos > 0)
	{
		line.replace(pos, 2, " | ");
		pos = line.find(',');
	}
	fout << line << endl;

	for(int i = 0; i < dataVect.size(); i++)
	{
		fout << dataVect[i][0] << '|' << dataVect[i][1] << '|' << dataVect[i][2] << endl;
	}

	fout.close();
}