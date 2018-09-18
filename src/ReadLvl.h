#ifndef ReadLvl_H_INCLUDE
#define ReadLvl_H_INCLUDE

#include <vector>
using std::vector;
#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

class ReadLvl
{
	private:
		int numWords = -1;
		int numSentences = -1;
		int numLetters = -1;
		
		void countWordsnLetters();
		void countSentences();
		
		double s();
		double l();
		
		vector<string> doc;
		
	public:
		ReadLvl(vector<string> const &strings) {doc = strings;}
		
		double getReadLvl();
	
};

#endif