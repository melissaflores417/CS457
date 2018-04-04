// .h file
// James Schnebly
// 3/27/18
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
	void queryTable(int whereIndex, string whereVal, vector<int> indices);
	void insert2Vector(vector<string> input);
	int getIndex(string colName);
	int update(int whereIndex, int setIndex, string whereVal, string setVal);
	int deleteT(int whereIndex, string whereVal, char op);
	void fileWrite();


private:
	string Tname;
	string Tparameters;
	string DBA;
	vector <vector<string> > dataVect;
};