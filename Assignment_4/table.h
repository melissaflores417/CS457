// .h file
// James Schnebly
// 5/8/18
// CS457 PA4

#include <iostream>
#include <fstream>

using namespace std;

// class to hold values for tables that are created
class Table
{

public:
	// constructors

	Table(string name, string attrs, string db);
	~Table();

	// get functions

	string getName();
	string getAttrs();
	string getDBA();
	int getIndex(string colName);
	string getValue(int row, int col);

	// set function

	void setAttrs(string a);

	// helper functions

	void printTable();
	void queryTable(int whereIndex, string whereVal, vector<int> indices);
	void insert2Vector(vector<string> input);
	int update(int whereIndex, int setIndex, string whereVal, string setVal);
	int deleteT(int whereIndex, string whereVal, char op);
	void fileWrite();
	



private:
	string Tname;
	string Tparameters;
	string DBA;
	vector <vector<string> > dataVect;
};