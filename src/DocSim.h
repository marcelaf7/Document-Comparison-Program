#ifndef DocSim_H_INCLUDE
#define DocSim_H_INCLUDE

#include <Document.h>

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <math.h>

class DocSim
{
	private:
		vector<Document> docs;
		
		bool isWord(string const &word);
		bool isIn(string const &word, int docIndex);
		int binarySearch(vector<string> &doc, int l, int r, string const x);
		double idf(string const &word);
		double tf(string const &word, int docIndex);
		double TFIDF(string &word, int docIndex);
		
	public:
		DocSim(vector<Document> &d) {docs = d;}
		
		double sim(int doc1index, int doc2index);
};

#endif