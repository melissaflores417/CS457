Author = James Schnebly
Date = 3/27/18
Project = PA2
Class = CS457

/////////////////////// RUNNING INSTRUCTIONS ///////////////////////////////

g++ -std=c++11 start.cpp -o run
./run < PA2_test.sql

////////////////////////////////////////////////////////////////////////////



*********************** RESULTS ********************************************

I have provided a screenshot of my program output when run with the supplied 
"PA2_test.sql". I did not change a thing from the supplied test script and my
program ran with the expected output as you can see in my provided screenshot.

****************************************************************************



%%%%%%%%%%%%%%%%%%%%%% DOCUMENTATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

1 - How your program store tuples in the table
2 - At a very high level, how you implement those required functionalities, 
	i.e., tuple insertion, deletion, modification, and query.

My program stores tuples inside of a 2-D vector of strings called 'DataVector'.
Each tuple is its own vector and each tuple vector is pushed onto the datavector
there for datavector[0] is the first row/tuple and datavector[0][0] is the first
element in the first tuple, etc. Each table is an object of the Abstract Data Type
'Table" so each table has its own 'DataVector'.


IMPLEMENTATIONS:
---------------

Database creation = system call to create folder if the folder does not already exist.
Database deletion = system call to delete folder if it does exist.
Table creation = system call to create txt/csv file inside of the database denoted by the "USE" command.
Table deletion = system call to delete txt/csv file inside of the database in use if the file exists.
Table update = Add attributes to the abstract data type Table. The variable updated is the attrs.
Table query = print out the table if and only if the table exists inside the database in use.
Tuple insertion = Create string vector where each slot is a value in the tuple
			and push that vector onto the Table object's datavector.
Tuple deletion = search the table via for loop on the index specified by the where statement
			if the condition is satisfied, use the vector erase method.
Tuple update = search the table via for loop on the index specified by the where statement
			if the condition is satisfied, overwrite the value in the specified index.
Tuple query = search the table via for loop on the indices specified by the where statement
			if the condition is satisfied, display the value(s) in the indicies specified by
			the select statement.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
