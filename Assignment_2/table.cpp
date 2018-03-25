// C++ file
// James Schnebly
// 
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
	for (int i = 0; i < dataVect.size(); i++)
	{
		cout << dataVect[i][0] << "   " << dataVect[i][1] << "   " << dataVect[i][2] << endl;
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