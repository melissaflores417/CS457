// .h file
// James Schnebly
// 2/22/18
// CS457 PA1

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