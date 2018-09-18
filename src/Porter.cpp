#include <Porter.h>

bool Porter::endsent(string const &str) //checks if str contains a punctuation make that makes it an end of a sentence
{
	bool foundPunc = false;
	
	for(int i = 0; i < (int)str.size(); i++)
	{
		if(str[i] >= '0' || str[i] <= '9')
		{
			return false;
		}
		if(!foundPunc && (str[i] == '.' || str[i] == '?' || str[i] == '!'))
		{
			foundPunc = true;
		}
	}
	
	if(foundPunc) return true;
	
	return false;
}

bool Porter::endsWith(string const &orig, string const &ending) // returns true if string orig ends with str ending
{
	if (orig.length() >= ending.length()) 
	{
        return (0 == orig.compare (orig.length() - ending.length(), ending.length(), ending));
    } 
    else 
    {
        return false;
    }
}

bool Porter::containsVow(string const &str) // returns true if str contains a vowel at any index
{
	char vowels[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

	for(int i = 0; i < (int)str.size(); i++)
	{
		if((str[i] == 'y' || str[i] == 'Y') && i != 0)
		{
			bool followsVow = false;

			for(int n = 0; n < 11; n++)
			{
				if(str[i -1] == vowels[n])
				{
					followsVow = true;
					break;
				}
			}

			if(!followsVow)
			{
				return true;
			}
		}
		for(int n = 0; n < 11; n++)
		{
			if(str[i] == vowels[n]) 
			{
				return true;
			}
		}
	}
	
	return false;
}

bool Porter::isVow(string const &str, int index) //checks character at index and returns true if it is a vowel
{
	char vows[] = {'a', 'e', 'i', 'o', 'u'};
	char cons[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 
	'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'};
	
	int vowsSize = 5;
	int consSize = 20;
	
	for(int i = 0; i < vowsSize; i++)
	{
		if(str[index] == vows[i])
		{
			return true;
		}
	}
	if(str[index] == 'y' && index != 0)
	{
		for(int i = 0; i < consSize; i++)
		{
			if(str[index -1] == cons[i])
			{
				return true;
			}
		}
	}
	
	return false;
}

int Porter::region1index(string const &str) // returns index where region 1 starts
{
	bool foundVowel = false;

	for(int i = 0; i < (int)str.size(); i++)
	{
		if(foundVowel && !isVow(str, i))
		{
			return i;
		}
		else if(isVow(str, i))
		{
			foundVowel = true;
		}

	}
	
	return -1;
}

bool Porter::canStem(string const &str) // returns true if str is a word longer than 2 letters and contains no punctuation or numbers
{
	if(str.size() <= 2)
	{
		return false;
	}
	for(int i = 0; i < (int)str.size(); i++)
	{
		if(!(str[i] == '\'' || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
		{
			return false;
		}
		else if(str[i] >= 'A' && str[i] <= 'Z')
		{
			return false;
		}
	}
	
	return true;
}

bool Porter::endsShort(string const &str) // returns true if str is "short"
{
	bool shortsyll = false;
	
	if(str.size() == 2 && isVow(str, 0) && !isVow(str, 1)) // ends with a short syllable
	{
		shortsyll = true;
	}
	if(str.size() >= 3 && !isVow(str, str.size() -3) && isVow(str, str.size() -2) && !isVow(str, str.size() -1)) // ends with a short syllable
	{
		if(str[str.size() -1] != 'w' && str[str.size() -1] != 'x' && str[str.size() -1] != 'y')
		{
			shortsyll = true;
		}
	}
	if((region1index(str) == -1 || region1index(str) == (int)str.size() -1) && shortsyll) //region1 is empty
	{
		return true;
	}
	
	return false;
}

bool Porter::liChar(char const cha) // returns true if cha is {'c', 'd', 'e', 'g', 'h', 'k', 'm', 'n', 'r', 't'}
{
	char liEndings[] = {'c', 'd', 'e', 'g', 'h', 'k', 'm', 'n', 'r', 't'};
	for(int i = 0; i < 11; i++)
	{
		if(liEndings[i] == cha)
		{
			return true;
		}
	}
	
	return false;
}

bool Porter::containsRegion2(string const &str) // returns true if str contains a region 2
{
	if(region1index(str) != -1)
	{
		if(region1index(str.substr(region1index(str), str.length() - region1index(str))) != -1)
		{
			return true;
		}
	}
	return false;
}

string Porter::step1(string str) // does Porter step 1 on str and returns the result
{
		
	if(str[0] == '\'')
	{
		str = str.substr(1, str.size() -1);
	}
		
	if(endsWith(str, "'s"))
	{
		str = str.substr(0, str.size() -2);
	}
	else if(endsWith(str, "'s'"))
	{
		str = str.substr(0, str.size() -3);
	}
	else if(str[str.size() -1] == '\'')
	{
		str = str.substr(0, str.size() -1);
	}
		
	return str;
}

string Porter::step2(string str) // does Porter step 2 on str and returns the result
{
			
	if(endsWith(str, "sses"))
	{
		str = str.substr(0, str.size() -2);
	}
	else if(endsWith(str, "ied") || endsWith(str, "ies"))
	{
		str = str.substr(0, str.size() -2);

		if(str.size() <= 2)
		{
			str = str + "e";
		}

	}	
	else if(!endsWith(str, "ss") && !endsWith(str, "us") && str[str.size() -1] == 's') // ends with s and there is a vowel
	{
		if(containsVow(str.substr(0, str.size() -2)))
		{
			str = str.substr(0, str.size() -1);
		}
	}

	return str;
}

string Porter::step3(string str) // does Porter step 3 on str and returns the result
{
			
	int region1 = region1index(str);

	if(region1 != -1 && (endsWith(str, "eedly") || endsWith(str, "eed")))
	{
		
		if(endsWith(str.substr(region1, str.size() - region1), "eedly"))
		{
			str = str.substr(0, str.size() -3);
		}
		else if(endsWith(str.substr(region1, str.size() - region1), "eed"))
		{
			str = str.substr(0, str.size() -1);
			
		}
	}
	else if(endsWith(str, "ed") && containsVow(str.substr(0, str.size() -2)))
	{
		string preceder = str.substr(0, str.size() -2);
		
		if(endsWith(preceder, "at") || endsWith(preceder, "bl") || endsWith(preceder, "iz"))
		{
				str = preceder + "e";
		}
		else if(endsWith(preceder, "bb") || endsWith(preceder, "dd") || endsWith(preceder, "ff") || endsWith(preceder, "gg")
			|| endsWith(preceder, "mm") || endsWith(preceder, "nn") || endsWith(preceder, "pp") || endsWith(preceder, "rr")
			|| endsWith(preceder, "tt")) //bb, dd, ff, gg, mm, nn, pp, rr, tt
		{
			str = preceder.substr(0, preceder.size() -1);
		}
		else if(endsShort(preceder)) //is short
		{
			str = preceder + "e";
		}
		else
		{
			str = preceder;
		}
	}
	else if(endsWith(str, "edly") && containsVow(str.substr(0, str.size() -4)))
	{
		string preceder = str.substr(0, str.size() -4);

		if(endsWith(preceder, "at") || endsWith(preceder, "bl") || endsWith(preceder, "iz"))
		{
			str = preceder + "e";
		}
		else if(endsWith(preceder, "bb") || endsWith(preceder, "dd") || endsWith(preceder, "ff") || endsWith(preceder, "gg")
			|| endsWith(preceder, "mm") || endsWith(preceder, "nn") || endsWith(preceder, "pp") || endsWith(preceder, "rr")
			|| endsWith(preceder, "tt")) //bb, dd, ff, gg, mm, nn, pp, rr, tt
		{
			str = preceder.substr(0, preceder.size() -1);
		}
		else if(endsShort(preceder)) //is short
		{
			str = preceder + "e";
		}
		else
		{
			str = preceder;
		}
	}
	else if(endsWith(str, "ing") && containsVow(str.substr(0, str.size() -3)))
	{
		string preceder = str.substr(0, str.size() -3);

		if(endsWith(preceder, "at") || endsWith(preceder, "bl") || endsWith(preceder, "iz"))
		{
			str = preceder + "e";
		}
		else if(endsWith(preceder, "bb") || endsWith(preceder, "dd") || endsWith(preceder, "ff") || endsWith(preceder, "gg")
			|| endsWith(preceder, "mm") || endsWith(preceder, "nn") || endsWith(preceder, "pp") || endsWith(preceder, "rr")
			|| endsWith(preceder, "tt")) //bb, dd, ff, gg, mm, nn, pp, rr, tt
		{
			str = preceder.substr(0, preceder.size() -1);
		}
		else if(endsShort(preceder)) //is short
		{
			str = preceder + "e";
		}
		else
		{
			str = preceder;
		}
	}
	else if(endsWith(str, "ingly") && containsVow(str.substr(0, str.size() -5)))
	{
		string preceder = str.substr(0, str.size() -5);

		if(endsWith(preceder, "at") || endsWith(preceder, "bl") || endsWith(preceder, "iz"))
		{
			str = preceder + "e";
		}
		else if(endsWith(preceder, "bb") || endsWith(preceder, "dd") || endsWith(preceder, "ff") || endsWith(preceder, "gg")
			|| endsWith(preceder, "mm") || endsWith(preceder, "nn") || endsWith(preceder, "pp") || endsWith(preceder, "rr")
			|| endsWith(preceder, "tt")) //bb, dd, ff, gg, mm, nn, pp, rr, tt
		{
			str = preceder.substr(0, preceder.size() -1);
		}
		else if(endsShort(preceder)) //is short
		{
			str = preceder + "e";
		}
		else
		{
			str = preceder;
		}
	}
	
	return str;
}

string Porter::step4(string str) // does Porter step 4 on str and returns the result
{
			
	if(str[str.size() -1] == 'y' && str.size() > 2 && !isVow(str, str.size() -2)) // Suffix follows a non-vowel that is not the first letter of the preceder.
	{
		str = str.substr(0, str.size() -1) + "i";
	}
			
	
	return str;
}

string Porter::step5(string str) // does Porter step 5 on str and returns the result
{
			
	if(endsWith(str, "ization") || endsWith(str, "ational")) // length 7
	{
		str = str.substr(0, str.size() -5) + "e"; // replacement: ize || ate
	}
	else if(endsWith(str, "fulness") || endsWith(str, "ousness") || endsWith(str, "iveness"))
	{
		str = str.substr(0, str.size() -4); // replacement: ful || ous || ive
	}
	else if(endsWith(str, "tional")) // length 6
	{
		str = str.substr(0, str.size() -2); // replacement: tion
	}
	else if(endsWith(str, "biliti"))
	{
		str = str.substr(0, str.size() -5) + "le"; // replacement: ble
	}
	else if(endsWith(str, "lessli"))
	{
		str = str.substr(0, str.size() -2); // replacement: less
	}
	else if(endsWith(str, "entli")) // length 5
	{
		str = str.substr(0, str.size() -2); // replacement: ent
	}
	else if(endsWith(str, "ation"))
	{
		str = str.substr(0, str.size() -3) + "e"; // replacement: ate
	}
	else if(endsWith(str, "alism") || endsWith(str, "aliti"))
	{
		str = str.substr(0, str.size() -3); // replacement: al
	}
	else if(endsWith(str, "ousli"))
	{
		str = str.substr(0, str.size() -2); // replacement: ous
	}
	else if(endsWith(str, "iviti"))
	{
		str = str.substr(0, str.size() -3) + "e"; // replacement: ive
	}
	else if(endsWith(str, "fulli"))
	{
		str = str.substr(0, str.size() -2); // replacement: ful
	}
	else if(endsWith(str, "enci") || endsWith(str, "anci") || endsWith(str, "abli")) // length 4
	{
		str = str.substr(0, str.size() -1) + "e"; // replacement: ence || ance || able
	}
	else if(endsWith(str, "izer"))
	{
		str = str.substr(0, str.size() -1); // replacement: ize
	}
	else if(endsWith(str, "ator"))
	{
		str = str.substr(0, str.size() -2) + "e"; // replacement: ate
	}
	else if(endsWith(str, "alli"))
	{
		str = str.substr(0, str.size() -2); // replacement: al
	}
	else if(endsWith(str, "bli")) // length 3
	{
		str = str.substr(0, str.size() -1) + "e"; // replacement: ble
	}
	else if(endsWith(str, "logi"))
	{ // originally "ogi" length 3
		str = str.substr(0, str.size() -1); // replacement: log
	}
	else if(endsWith(str, "li") && liChar(str[str.size() -3])) // length 2
	{
		str = str.substr(0, str.size() -2); // replacement: none
	}
	
	return str;
}

string Porter::step6(string str) // does Porter step 6 on str and returns the result
{
			
	if(endsWith(str, "ational") && region1index(str.substr(0, str.size() -7)) != -1)
	{
		str = str.substr(0, str.size() -5) + "e"; // replacement: ate
	}
	else if(endsWith(str, "tional") && region1index(str.substr(0, str.size() -6)) != -1)
	{
		str = str.substr(0, str.size() -2); // replacement: tion
	}
	else if(endsWith(str, "alize") && region1index(str.substr(0, str.size() -5)) != -1)
	{
		str = str.substr(0, str.size() -3); // replacement: al
	}
	else if(endsWith(str, "icate") && region1index(str.substr(0, str.size() -5)) != -1)
	{
		str = str.substr(0, str.size() -3); // replacement: ic
	}
	else if(endsWith(str, "iciti") && region1index(str.substr(0, str.size() -5)) != -1)
	{
		str = str.substr(0, str.size() -3); // replacement: ic
	}
	else if(endsWith(str, "ative") && containsRegion2(str.substr(0, str.size() -5))) // region 2
	{
		str = str.substr(0, str.size() -5); // replacement: (none)
	}
	else if(endsWith(str, "ical") && region1index(str.substr(0, str.size() -4)) != -1)
	{
		str = str.substr(0, str.size() -2); // replacement: ic
	}
	else if(endsWith(str, "ness") && region1index(str.substr(0, str.size() -4)) != -1)
	{
		str = str.substr(0, str.size() -4); // replacement: (none)
	}
	else if(endsWith(str, "ful") && region1index(str.substr(0, str.size() -3)) != -1)
	{
		str = str.substr(0, str.size() -3); // replacement: (none)
	}			
	
	
	return str;
}

string Porter::step7(string str) // does Porter step 7 on str and returns the result
{
			
	if(endsWith(str, "al"))
	{
		if(containsRegion2(str.substr(0, str.size() -2)))
		{
			str = str.substr(0, str.size() -2);
		}
	}
	else if(endsWith(str, "ance"))
	{
		if(containsRegion2(str.substr(0, str.size() -4)))
		{	
			str = str.substr(0, str.size() -4);
		}
	}
	else if(endsWith(str, "ence"))
	{
		if(containsRegion2(str.substr(0, str.size() -4)))
		{
			str = str.substr(0, str.size() -4);
		}
	}
	else if(endsWith(str, "er"))
	{
		if(containsRegion2(str.substr(0, str.size() -2)))
		{
			str = str.substr(0, str.size() -2);
		}
	}
	else if(endsWith(str, "ic"))
	{
		if(containsRegion2(str.substr(0, str.size() -2)))
		{
			str = str.substr(0, str.size() -2);
		}
	}
	else if(endsWith(str, "able"))
	{
		if(containsRegion2(str.substr(0, str.size() -4)))
		{
			str = str.substr(0, str.size() -4);
		}
	}
	else if(endsWith(str, "ible"))
	{
		if(containsRegion2(str.substr(0, str.size() -4)))
		{
			str = str.substr(0, str.size() -4);
		}
	}
	else if(endsWith(str, "ant"))
	{
		if(containsRegion2(str.substr(0, str.size() -3)))
		{
			str = str.substr(0, str.size() -3);
		}
	}
	else if(endsWith(str, "ement"))
	{
		if(containsRegion2(str.substr(0, str.size() -5)))
		{
			str = str.substr(0, str.size() -5);
		}
	}
	else if(endsWith(str, "ment"))
	{	
		if(containsRegion2(str.substr(0, str.size() -4)))
		{
			str = str.substr(0, str.size() -4);
		}
	}
	else if(endsWith(str, "ent"))
	{
		if(containsRegion2(str.substr(0, str.size() -3)))
		{
			str = str.substr(0, str.size() -3);
		}
	}
	else if(endsWith(str, "ism"))
	{
		if(containsRegion2(str.substr(0, str.size() -3)))
		{
			str = str.substr(0, str.size() -3);
		}
	}
	else if(endsWith(str, "ate"))
	{
		if(containsRegion2(str.substr(0, str.size() -3)))
		{
			str = str.substr(0, str.size() -3);
		}
	}
	else if(endsWith(str, "iti"))
	{
		if(containsRegion2(str.substr(0, str.size() -3)))
		{
			str = str.substr(0, str.size() -3);
		}
	}
	else if(endsWith(str, "ous"))
	{
		if(containsRegion2(str.substr(0, str.size() -3)))
		{
			str = str.substr(0, str.size() -3);
		}
	}
	else if(endsWith(str, "ive"))
	{
		if(containsRegion2(str.substr(0, str.size() -3)))
		{
			str = str.substr(0, str.size() -3);
		}
	}
	else if(endsWith(str, "ize"))
	{
		if(containsRegion2(str.substr(0, str.size() -3)))
		{
			str = str.substr(0, str.size() -3);
		}
	}
	else if(endsWith(str, "ion") && containsRegion2(str.substr(0, str.size() -3)) 
		&& (str[str.size() -4] == 's' || str[str.size() -4] == 't'))
	{
		str = str.substr(0, str.size() -3);
	}
	
	
	return str;
}

string Porter::step8(string str) // does Porter step 8 on str and returns the result
{
	
	if(str[str.size() -1] == 'e' && (containsRegion2(str.substr(0, str.size() -1)) 
		|| (region1index(str.substr(0, str.size() -1)) != -1 && !endsShort(str.substr(0, str.size() -1)))))
	{
		str = str.substr(0, str.size() -1);
	}
	else if(endsWith(str, "ll") && containsRegion2(str.substr(0, str.size() -1)))
	{
		str = str.substr(0, str.size() -1);
	}
	
	return str;
}
