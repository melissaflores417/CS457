// .h file
// James Schnebly
// 
// CS457 PA2

#include <iostream>
#include <fstream>

using namespace std;

// class to hold values for tables that are created
class Table
{

public:
	Table(string name, string attrs, string db);
	~Table();
	string getName();
	string getAttrs();
	string getDBA();
	void setAttrs(string a);
	void printTable();


private:
	string Tname;
	string Tparameters;
	string DBA;
	
};