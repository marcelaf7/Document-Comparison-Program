# Document-Comparison-Program
Created over the course of Fall Semester 2017 for CS253: Software Development with C++

## What it does
This program compares documents based on their subject and reading level.
It will compare the query document to a library of other documents to determine which is the most similar in subject given the specified reading level.

## How to run it
This program is best run on Linux as it requires command line arguments.

The code can be manually compiled from source using `make`, otherwise a complited executable file is provided in the repository.

The program takes 4 arguments:
1. Path to the query file.
2. Path to the library file (a file containing the path to all files in the library).
3. The minimum reading level
4. The maximum reading level

For example, to compile run from Linux:
```./Document-Comparison.exe Test_Cases/journalshrew Test_Cases/library 10 200```
