#include <Document.h>
#include <ReadLvl.h>
#include <Porter.h>

bool Document::readFile(string const &fileName)
{
	name = fileName;
	ifstream myfile(name);
	string str;
	//vector<string> vec;
	
	if(!myfile.is_open())
	{
		cerr << "Could not open file " << name << endl;
		return false;
	}
	
	while(myfile >> str)
	{
		parse(str, vec);
	}
	
	if(str.empty())
	{
		cerr << "File " << name << " is empty" << endl;
		return false;
	}
	
	myfile.close();
	
	ReadLvl r1(vec);
	readlvl = r1.getReadLvl();
	if(readlvl == -1)
	{
		cerr << "Reading level could not be calculated for " << fileName << endl;
		return false;
	}
	
	Porter p;

	checkcaps(vec);
	
	bool dontStem = false;
	string excep;
	string afterAmbig;
	
	for(int i = 0; i < (int)vec.size(); i++)
	{
		dontStem = false;
		
		if(p.canStem(vec[i]))
		{
			excep = e.isException(vec[i]);
			if(excep != "")
			{
				dontStem = true;
				vec[i] = excep;
			}
		}
		
		afterAmbig = checkAmbiguous(vec[i], i, vec);
		if(!dontStem && afterAmbig.compare(vec[i]) != 0)
		{
			dontStem = true;
			vec[i] = afterAmbig;
		}
		
		if(!dontStem && p.canStem(vec[i]))
		{
			vec[i] = p.step1(vec[i]);
			vec[i] = p.step2(vec[i]);
			vec[i] = p.step3(vec[i]);
			vec[i] = p.step4(vec[i]);
			vec[i] = p.step4(vec[i]);
			vec[i] = p.step5(vec[i]);
			vec[i] = p.step6(vec[i]);
			vec[i] = p.step7(vec[i]);
			vec[i] = p.step8(vec[i]);
		}
	}

	
	
	sort(vec.begin(), vec.end());
	
	
	/* string temparr[vec.size()];
	
	for(int i = 0; i < (int)vec.size(); i++)
	{
		temparr[i] = vec[i];
	}
	
	arr = temparr;
	size = vec.size(); */

	return true;
}

void Document::parse(string &str, vector<string> &vec)
{
	string newstr = str;
	int strsize = newstr.size();
	
	for(int i = 0; i < strsize; i++)
	{
		if(strsize == 1) //always push a string of size 1 
		{
			vec.push_back(newstr);
			break;
		}
		else if(newstr[i] == '.')
		{
			if(i == strsize -1 && isAlphanumeric(newstr[i -1]))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i != strsize -1 && i != 0 && isAlphanumeric(newstr[i +1]) && !(newstr[i +1] >= '0' && newstr[i +1] <= '9') && newstr[i -1] == '.')
			{
				newstr = split(newstr, i +1, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i != strsize -1 && isAlphanumeric(newstr[i +1]) && !(newstr[i +1] >= '0' && newstr[i +1] <= '9'))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i != 0 && isAlphanumeric(newstr[i -1]) && !(newstr[i -1] >= '0' && newstr[i -1] <= '9'))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				
				if(strsize > 1 && isAlphanumeric(newstr[1]))
				{
					newstr = split(newstr, 1, vec);
					strsize = newstr.size();
				}
				
				i = -1;
			}
			else if(i != 0 && i != strsize -1 && (newstr[i -1] >= '0' && newstr[i -1] <= '9') && !(newstr[i +1] >= '0' && newstr[i +1] <= '9'))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i != 0 && i != strsize -1 && (newstr[i +1] >= '0' && newstr[i +1] <= '9') && !(newstr[i -1] >= '0' && newstr[i -1] <= '9'))
			{
				newstr = split(newstr, i +1, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i == strsize -1)
			{
				vec.push_back(newstr);
				break;
			}
		}
		else if(newstr[i] == ',')
		{
			if((i == 0 && isAlphanumeric(newstr[i +1])))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i == strsize -1 && isAlphanumeric(newstr[i -1]))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i != 0 && isAlphanumeric(newstr[i -1]) && !(newstr[i -1] >= '0' && newstr[i -1] <= '9'))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i != strsize -1 && i != 0 && isAlphanumeric(newstr[i +1]) && newstr[i -1] == ',')
			{
				newstr = split(newstr, i +1, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i != strsize -1 && isAlphanumeric(newstr[i +1]) && !(newstr[i +1] >= '0' && newstr[i +1] <= '9'))
			{
				newstr = split(newstr, i, vec); 
				strsize = newstr.size();
				i = -1;
			}
			else if(i != strsize -1 && i != 0 && isAlphanumeric(newstr[i -1]) && (newstr[i +1] < '0' || newstr[i +1] > '9'))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i == strsize -1)
			{
				vec.push_back(newstr);
				break;
			}
		}
		else if(!isAlphanumeric(newstr[i]))
		{
			if((i != 0 && isAlphanumeric(newstr[i -1])))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i != strsize +1 && i != 0 && isAlphanumeric(newstr[i +1]) && !isAlphanumeric(newstr[i -1]))
			{
				newstr = split(newstr, i +1, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i != strsize +1 && isAlphanumeric(newstr[i +1]))
			{
				newstr = split(newstr, i, vec);
				strsize = newstr.size();
				i = -1;
			}
			else if(i == strsize -1)
			{
				vec.push_back(newstr);
				break;
			}
		}
		else if(i == strsize -1) //if end of string, push it
		{
				vec.push_back(newstr);
				break;
		}
	}
}

void Document::checkcaps(vector<string> &vec)
{
	
	if(vec[0][0] >= 65 && vec[0][0] <= 90)
	{
		bool acr = false;
		for(int i = 1; i < (int)vec[0].size(); i++)
		{
			if((vec[0][i] >= 48 && vec[0][i] <= 57) || (vec[0][i] >= 65 && vec[0][i] <= 90))
			{
				acr = true;
				break;
			}
		}
		if(!acr)
		{
			vec[0] = "+" + vec[0];
		}
	}
	for(int i = 1; i < (int)vec.size(); i++)
	{
		string currstr = vec[i];
		
	 	if(currstr[0] >= 65 && currstr[0] <= 90 && endsent(vec[i -1]))
	 	{
	 		bool acr = false;
	 		for(int n = 1; n < (int)currstr.size(); n++)
	 		{
	 			if((currstr[n] >= 48 && currstr[n] <= 57) || (currstr[n] >= 65 && currstr[n] <= 90))
	 			{
					acr = true; 
	 				break;
	 			}
	 		}
	 		if(!acr)
	 		{
	 			vec[i] = "+" + vec[i];
	 		}
	 	}
	}
}

string Document::checkAmbiguous(string const &str, int index, vector<string> const &vec)
{
	string unambig = str;
		
	if(str[0] == '+')
	{
		bool cap = false;
		unambig = str.substr(1, str.size() -1);
		for(int i = 0; i < (int)vec.size(); i++)
		{
			if(i != index && unambig.compare(vec[i]) == 0)
			{
				cap = true;
				break;
			}
		}
		if(!cap)
		{	
			unambig[0] += 32;
			Porter p;
				
			if(p.canStem(unambig))
			{
				string excep = e.isException(unambig);
				if(excep != "") return excep;
				
				unambig = p.step1(unambig);
				unambig = p.step2(unambig);
				unambig = p.step3(unambig);
				unambig = p.step4(unambig);
				unambig = p.step4(unambig);
				unambig = p.step5(unambig);
				unambig = p.step6(unambig);
				unambig = p.step7(unambig);
				unambig = p.step8(unambig);
				
			}	
		}
	}
	
	return unambig;
}

bool Document::isAlphanumeric(char ch)
{
	if(ch == '\'' || (ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
	{
		return true;
	}
	return false;
}

string Document::split(string &str, int i, vector<string> &vec)
{
	if(i == 0)
	{
		vec.push_back(str.substr(0, 1));
		str = str.substr(1, str.size() -1);
		return str;
	}
	else
	{
		vec.push_back(str.substr(0, i));
		str = str.substr(i, str.size() -i);
		return str;
	}
}

bool Document::endsent(string const &str)
{
	bool foundPunc = false;
	
	for(int i = 0; i < (int)str.size(); i++)
	{
		if(str[i] >= '0' && str[i] <= '9')
		{
			return false;
		}
		if(!foundPunc && (str[i] == '.' || str[i] == '?' || str[i] == '!'))
		{
			foundPunc = true;
		}
	}
	
	if(foundPunc) 
	{
		return true;
	}
	
	return false;
}

void Document::printStrings(vector<string> const &vec)
{
	int num = 1;
	int vecSize = vec.size();

    for(int i = 0; i < vecSize; i++) //prints output
    {
    	if(i +1 < vecSize && vec[i].compare(vec[i +1]) == 0)
    	{
    		num++;
    	}
    	else
    	{
    		cout << vec[i] << " " << num << endl;
    		num = 1;
    	}
	}
}

void Document::printStrings()
{
	
	int num = 1;
	
	for(int i = 0; i < (int)vec.size(); i++)
	{
		if(i +1 < (int)vec.size() && vec[i].compare(vec[i + 1]) == 0)
		{
			num++;
		}
		else
		{
			cout << vec[i] << " " << num << endl;
			num = 1;
		}
	}
}