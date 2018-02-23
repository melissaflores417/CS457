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