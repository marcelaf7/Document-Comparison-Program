#include <Exceptions.h>

bool Exceptions::isAlphanumeric(char ch) // returns true if character is ', A-Z, a-z, 0-9
{
	if(ch == '\'' || (ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
	{
		return true;
	}
	return false;
}

bool Exceptions::excepsValid(string const &str)
{
	bool word1 = false;
	bool blank = false;
	bool word2 = false;
	
	if(str.size() < 3) return false;
	
	for(int i = 0; i < (int)str.size(); i++)
	{
		if(i == 0 && str[i] == ' ') return false;
		if(!blank && !word2 && isAlphanumeric(str[i])) word1 = true;
		else if(word1 && !word2 && str[i] == ' ') blank = true;
		else if(word1 && blank && isAlphanumeric(str[i])) word2 = true;
	}
	
	if(word1 && blank && word2) return true;
	return false;
}

string Exceptions::isException(string const &str)
{
	for(int i = 0; i < size; i++)
	{
		if(exceps[i][0].compare(str) == 0)
		{
			return exceps[i][1];
		}
	}
	
	return "";
}

bool Exceptions::readExceps(string const &filename)
{	
	ifstream myfile(filename);
	if(!myfile.is_open())
	{
		cerr << "Exceptions file " << filename << " could not be opened" << endl;
		return false;
	}
	
	string line = "";
	string str0 = "";
	string str1 = "";
	int bufferIndex = 0;
	
	while(!myfile.eof())
	{
		if(bufferIndex >= 500) break;
		stringstream stream;
		
		getline(myfile, line);
		
		if(line == "") continue;
		if(!excepsValid(line)) 
		{
			cerr << "Exceptions file " << filename << " not formatted correctly" << endl;
			return false;
		}
		
		stream << line;
		stream >> str0 >> str1;
		
		exceps[bufferIndex][0] = str0;
		exceps[bufferIndex][1] = str1;
		
		bufferIndex++;
	}
	
	size = bufferIndex;
	
	return true;
}
