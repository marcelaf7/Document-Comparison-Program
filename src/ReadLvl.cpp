#include <ReadLvl.h>

void ReadLvl::countWordsnLetters()
{
	numWords = 0;
	numLetters = 0;
	
	for(int i = 0; i < (int)doc.size(); i++)
	{
		for(int n = 0; n < (int)doc[i].size(); n++)
		{
			if((doc[i][n] >= 'a' && doc[i][n] <= 'z') || (doc[i][n] >= 'A' && doc[i][n] <= 'Z'))
			{
				numWords++;
				numLetters += doc[i].size();
				break;
			}
			else if(doc[i][n] == '\'' || (doc[i][n] >= '0' && doc[i][n] <= '9'))
			{
				numWords++;
				numLetters += doc[i].size();
				break;
			}
		}
	}
	//cout << "Words = " << numWords << endl;
	//cout << "Characters = " << numLetters << endl;
}

void ReadLvl::countSentences()
{
	numSentences = 0;
	
	for(int i = 0; i < (int)doc.size(); i++)
	{
		for(int n = 0; n < (int)doc[i].size(); n++)
		{
			if(doc[i][n] == '.' || doc[i][n] == '!' || doc[i][n] == '?')
			{
				//cout << "'" << doc[i][n] << "' is a punctuation" << endl;
				if(doc[i][n] == '.')
				{
					if(doc[i].size() == 1 || n == (int)doc[i].size() -1)
					{
						//cout << "'" << doc[i] << "' is a sentence" << endl;
						numSentences++;
						break;
					}
					else if(n != (int)doc[i].size() -1 && (doc[i][n+1] < '0' || doc[i][n+1] > '9'))
					{
						//cout << "'" << doc[i] << "' is a sentence" << endl;
						numSentences++;
						break;
					}
				}
				else
				{
					numSentences++;
					break;
				}
			}
		}
	}
	
	//cout << "Sentences = " << numSentences << endl;
}

double ReadLvl::s()
{
	if(numWords == -1) countWordsnLetters();
	if(numSentences == -1) countSentences();
	
	if(numWords == 0) return -1;
	
	double s = (double) numSentences / numWords *100;
	
	return s;
}

double ReadLvl::l()
{
	if(numLetters == -1 || numWords == -1) countWordsnLetters();
	
	if(numWords == 0) return -1;
	
	double l = (double) ((double)numLetters / (double)numWords) * 100;
	
	return l;
}

double ReadLvl::getReadLvl()
{
	double ll = l();
	double ss = s();
	
	//cout << "L() = " << ll << endl;
	//cout << "S() = " << ss << endl;
	
	if(ll == -1 || ss == -1) return -1;
	
	double CL = (0.0588 * ll) - (0.296 * ss) - 15.8;
	
	return CL;
}