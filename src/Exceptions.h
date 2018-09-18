#ifndef Exceptions_H_INCLUDE
#define Exceptions_H_INCLUDE

#include <iostream>
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

class Exceptions
{
	private:
		bool isAlphanumeric(char ch);
		bool excepsValid(string const &str);
	
	public:
		int size;
		string exceps[500][2];
		
		string isException(string const &str);
		bool readExceps(string const &filename);
		
};

#endif