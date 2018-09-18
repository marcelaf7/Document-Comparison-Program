#include <DocSim.h>

bool DocSim::isWord(string const &word)
{
	for(int i = 0; i < (int)word.size(); i++)
	{
		if((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') || word[i] == '\'' || (word[i] >= '0' && word[i] <= '9'))
		{
			return true;
		} 
	}
	
	return false;
}

bool DocSim::isIn(string const &word, int docIndex)
{
	//cout << "isIn was called with word " << word << " and doc " << docIndex << endl;
	//int docSize = docs[docIndex].getSize();
	//string* doc = docs[docIndex].getArr();
	vector<string> doc = docs[docIndex].getVec();
	
	//cout << "isIn: initializations passed" << endl;

	//cout << "Size of document = " << doc.size() << endl;
	
	if(binarySearch(doc, 0, doc.size() -1, word) != -1) 
	{
		//cout << "isIn: returned true for word " << word << " in doc " << docIndex << endl;
		return true;
	}
	
	//cout << "isIn: returned false for word " << word << " in doc " << docIndex << endl;
	return false;
}

int DocSim::binarySearch(vector<string> &doc, int l, int r, string const x)
{
	//cout << "binarySearch was called with l = " << l << " r = " << r << " word = " << x << endl;
	if (r >= l)
	{
		int mid = l + (r - l)/2;

		//cout << "mid = " << mid << endl;

		// If the element is present at the middle itself
        if (doc[mid].compare(x) == 0)  return mid;
 
        // If element is smaller than mid, then it can only be present
        // in left subarray
        if (doc[mid].compare(x) > 0) return binarySearch(doc, l, mid-1, x);
 
        // Else the element can only be present in right subarray
        return binarySearch(doc, mid+1, r, x);
	}
 
   // We reach here when element is not present in array
   return -1;
}

double DocSim::idf(string const &word)
{
	//cout << "idf was called with word " << word << endl;

	int numDocs = docs.size();
	int contain = 0;
	
	//cout << "idf: initializations passed" << endl;
	//cout << "idf: there are " << numDocs << " docs to check" << endl;

	for(int i = 0; i < numDocs; i++)
	{
		//cout << "idf: checking if word " << word << " is in doc " << i << endl;
		if(isIn(word, i))
		{
			//cout << "idf: word " << word << " is in doc " << i << endl;
			contain++;
		}

		//else cout << "idf: word " << word << " is NOT in doc " << i << endl;
	}

	double frac = (double) numDocs / (double) contain;
	
	//cout << "idf returned log10(" << frac << ") = " << log10(frac) << endl;

	return log10(frac);
}

double DocSim::tf(string const &word, int docIndex)
{
	//cout << "tf was called with word " << word << endl;

	int count = 0;
	//int docSize = docs[docIndex].getSize();
	//string* doc = docs[docIndex].getArr();
	
	vector<string> doc = docs[docIndex].getVec();
	
	int wordIndex = binarySearch(doc, 0, doc.size() -1, word);
	if(wordIndex == -1) return 0;
	
	count++;
	
	//check indexes to the right
	int checkIndex = wordIndex;
	while(checkIndex +1 < (int)doc.size() && doc[checkIndex +1].compare(word) == 0)
	{
		checkIndex++;
		count++;
	}
	
	//check indexes to the left
	checkIndex = wordIndex;
	while(checkIndex -1 >= 0 && doc[checkIndex -1].compare(word) == 0)
	{
		checkIndex--;
		count++;
	}
	
	//cout << "tf returned " << count << endl;

	return (double)count;
}

double DocSim::TFIDF(string &word, int docIndex)
{
	//cout << "TFIDF was called with word " << word << endl;
	//cout << "calling tf and idf with word " << word << endl;
	double tfidf = (double)tf(word, docIndex) * (double)idf(word);
	return tfidf;
}

double DocSim::sim(int doc1index, int doc2index)
{
	//cout << "sim was called with " << doc1index << ", " << doc2index << endl;
	vector<string> doc1 = docs[doc1index].getVec();
	vector<string> doc2 = docs[doc2index].getVec();
	
	string lastWord = "";
	double sum = 0;
	
	//cout << "initializations passed" << endl;
	
	//cout << "Doc1 size is " << doc1.size() << endl;
	//cout << "Doc2 size is " << doc2.size() << endl;
	
	for(int i = 0; i < (int)(doc1.size() + doc2.size()); i++)
	{
		if(i < (int)doc1.size())
		{
			if(isWord(doc1[i]) && doc1[i].compare(lastWord) != 0)
			{
				//cout << "calling TFIDF with word " << doc1[i] << " at index " << i << endl;
				lastWord = doc1[i];
				sum += (TFIDF(doc1[i], doc1index) * TFIDF(doc1[i], doc2index));
				//cout << "TFIFD returned" << endl;
			}
		}
		else if(i - (int)doc1.size() < (int)doc2.size())
		{
			if(isWord(doc2[i - (int)doc1.size()]) && doc2[i - (int)doc1.size()].compare(lastWord) != 0 && !isIn(doc2[i - (int)doc1.size()], doc1index))
			{
				//cout << doc2[i - (int)doc1.size()] << " compared to " << lastWord << " is " << doc2[i - (int)doc1.size()].compare(lastWord) << endl;
				//cout << "calling TFIDF with word " << doc2[i - (int)doc1.size()] << " at index " << i - (int)doc1.size() << " last word is " << lastWord << endl;
				lastWord = doc2[i - (int)doc1.size()];
				sum += (TFIDF(doc2[i - (int)doc1.size()], doc1index) * TFIDF(doc2[i - (int)doc1.size()], doc2index));
				//cout << "TFIDF returned" << endl;
			}
		}
	}
	
	//cout << "sim returned " << sum << endl;
	
	return sum;
}