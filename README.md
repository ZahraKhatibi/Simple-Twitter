# Simple Twitter with schema and database in C++

This is a simple SQL-like Database Management System (DBMS) implemented in C++. It provides basic functionalities for managing a database, including INSERT, SELECT, DELETE, and UPDATE operations. The system uses text files to store and manipulate data.

## Table of Contents
1. [Overview](#overview)
2. [Functions](#functions)
3. [Error Handling](#error-handling)
4. [Schema](#schema)
5. [Sample Input](#sample-input)

## Overview<a name="overview"></a>

The DBMS supports the following operations:
- **INSERT:** Insert data into a table.
- **SELECT:** Retrieve data from a table.
- **DELETE:** Remove data from a table.
- **UPDATE:** Modify data in a table.

The system reads and writes data to text files, with each table represented by a separate file. The schema of the database is defined in a file called `schema.txt`, which lists the tables and their columns.

## Functions<a name="functions"></a>
The DBMS provides the following functions:

vector<string> INSERT(string str): Inserts data into a table.
vector<string> SELECT(string str): Retrieves data from a table.
vector<string> DELETE(string str): Deletes data from a table.
vector<string> UPDATE(string str): Updates data in a table.
vector<string> database(string stri): Main function that parses and executes SQL-like commands.

## Error Handling<a name="error-handling"></a>
The DBMS includes error handling for various scenarios, such as invalid input, mismatched data types, and attempts to update non-existing records. Error messages are displayed in the console to assist users in identifying and correcting issues.

## Schema<a name="schema"></a>
The database schema is defined in the schema.txt file, which lists the tables and their columns. Each line represents a table, with columns separated by spaces. The schema file is essential for validating input and ensuring data consistency.

## Sample Input<a name="sample-input"></a>
To interact with the DBMS, you can input SQL-like commands prefixed with ~$. Below is a sample INSERT command:
### input
```
$ INSERT INTO users VALUES (16,zahra,zahrakhtb1,123,Tue/Aug/11/23:45:26/2020,0);
```
