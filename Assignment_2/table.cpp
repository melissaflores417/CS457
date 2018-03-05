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
	string line  = Tparameters;
	int pos = line.find(',');
	while(pos > 0)
	{
		line.replace(pos, 2, " | ");
		pos = line.find(',');
	}
	cout << line << endl;

}

void Table::setAttrs(string a)
{
	Tparameters = a;
}