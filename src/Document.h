#ifndef Document_H_INCLUDE
#define Document_H_INCLUDE

#include <Exceptions.h>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;

class Document
{
	private:
		vector<string> vec;
		//string *arr;
		//int size;
		double readlvl;
		string name;
		double similarity;
		
	public:
		Document(Exceptions exceps) {e = exceps;}
		
		Exceptions e;
		
		string getName() const {return name;}
		double getSimilarity() const {return similarity;}
		void setSimilarity(double sim) {similarity = sim;}
		double getReadingLevel() const {return readlvl;}
		vector<string> getVec() {return vec;}
		//int getSize() {return size;}
		//string* getArr() {return arr;}
		
		bool readFile(string const &fileName); // reads the file, iterates through every line, and returns true if it's successful
		void parse(string &str, vector<string> &vec); // separates words from punctuation and accounts for caps and pushes them in the vector
		void checkcaps(vector<string> &vec); // checks for words that start with a capital letter and marks them ambiguous if necessary
		
		string checkAmbiguous(string const &str, int index, vector<string> const &vec); // checks ambiguously marked words, marks them unambiguous and stems them
		bool isAlphanumeric(char ch); // returns true if character is ', A-Z, a-z, 0-9
		string split(string &str, int i, vector<string> &vec); // splits the string str at index i and returns the new string
		bool endsent(string const &str); // checks if str contains a punctuation make that makes it an end of a sentence
		void printStrings(vector<string> const &vec); // prints out vector vec and how many times each duplicate appears
		void printStrings();
};

#endif