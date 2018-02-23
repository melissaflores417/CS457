Author = James Schnebly
Date = 2/22/18
Project = PA1
Class = CS457

/////////////////////// RUNNING INSTRUCTIONS ///////////////////////////////

g++ start.cpp -o run
./run < PA1_test.sql

////////////////////////////////////////////////////////////////////////////



*********************** RESULTS ********************************************

I have provided a screenshot of my program output when run with the supplied 
"PA1_test.sql". I deleted all comments from the file as you will. Professor
said we did not need to worry about parsing the comment lines and the real 
test script would only contain the commands. Please test with my uncommented 
"PA1_test.sql" if the commands are the same as I know my program works 100%
with the test script I have supplied in the zip folder.

****************************************************************************



%%%%%%%%%%%%%%%%%%%%%% DOCUMENTATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

1 - How your program organizes multiple databases?
2 - How your program manages multiple tables?
3 - At a very high level, how you implement those required functionalities?
	
Each database is implemented as a folder via system call and each table 
is implemeted as a txt/csv file that will contain the appropriate data. 
The USE keyword tells which database is being used and therefore only 
tables in that directory can be altered or selected. There is a vector
that holds an abstract data type instance of each table. The table data 
type contains values such as "name", "attributes", and "Database Associated".
There are many error checks associated with databases and tables like making
usre the database in use actually holds the table you want to select or alter.

IMPLEMENTATIONS:
---------------

Database creation = system call to create folder if the folder does not already exist.
Database deletion = system call to delete folder if it does exist.
Table creation = system call to create txt/csv file inside of the database denoted by the "USE" command.
Table deletion = system call to delete txt/csv file inside of the database in use if the file exists.
Table update = Add attributes to the abstract data type Table. The variable updated is the attrs.
Table query = print out the table if and only if the table exists inside the database in use.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%