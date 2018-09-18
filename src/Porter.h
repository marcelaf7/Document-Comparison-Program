#ifndef Porter_H_INCLUDE
#define Porter_H_INCLUDE

#include <string>
using std::string;

class Porter
{
	private:
		bool endsent(string const &str); // returns true if string contains punctuation marking the end of a sentence
		bool endsWith(string const &orig, string const &ending); // returns true if string orig ends with str ending
		bool containsVow(string const &str); // returns true if str contains a vowel at any index
		bool isVow(string const &str, int index); //checks character at index and returns true if it is a vowel
		int region1index(string const &str); // returns index where region 1 starts
		bool endsShort(string const &str); // returns true if str is "short"
		bool liChar(char const cha); // returns true if cha is {'c', 'd', 'e', 'g', 'h', 'k', 'm', 'n', 'r', 't'}
		bool containsRegion2(string const &str); // returns true if str contains a region 2

	public:
		bool canStem(string const &str); // returns true if str is a word longer than 2 letters and contains no punctuation or numbers
		string step1(string str); // does Porter step 1 on str and returns the result
		string step2(string str); // does Porter step 2 on str and returns the result
		string step3(string str); // does Porter step 3 on str and returns the result
		string step4(string str); // does Porter step 4 on str and returns the result
		string step5(string str); // does Porter step 5 on str and returns the result
		string step6(string str); // does Porter step 6 on str and returns the result
		string step7(string str); // does Porter step 7 on str and returns the result
		string step8(string str); // does Porter step 8 on str and returns the result
	
};

#endif