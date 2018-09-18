#include <Exceptions.h>
#include <Document.h>
#include <DocSim.h>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ifstream;

int main(int argc, char* argv[])
{	
	//check arguments
	 if(argc < 5) //checks for the right amount of input arguments
	{
		cerr << "Input should be 4 arguments. (query filename, library filename, minimum reading level, maximum reading level" << endl;
		return -1;
	}
	
	//read exceptions file
	ifstream myfile(argv[2]); //opens library file
	string excepsFileName;
	Exceptions excep;
	
	if(!myfile.is_open()) //checks that the library file can be opened
	{
		cerr << "library file " << argv[2] << " could not be opened" << endl;
		return -1;
	}
	
	if(myfile >> excepsFileName) //reads first line of library file
	{
		if(excepsFileName.empty())//checks if library file is empty
		{
			cerr << "library file " << argv[2] << " is empty" << endl;
			return -1;
		}
		
		if(!excep.readExceps(excepsFileName)) return -1; //reads exceptions file and returns -1 if there was an error
			
	}
	else //error if first line of library file could not be read
	{
		cerr << "library file " << argv[2] << " could not be read" << endl;
		return -1;
	}
	
	//read query document
	Document doc(excep); //holds query document
	string queryName = argv[1];
	if(!doc.readFile(queryName)) return -1; //reads query document and returns -1 if there is an error
	
	//read library documents
	vector<Document> docVec; //holds library of documents
	string docName;
	
	docVec.push_back(doc);
	
	while(myfile >> docName) //read from library file line by line
	{	
		Document d(excep);
		if(!d.readFile(docName)) return -1;
		docVec.push_back(d);
	}
	
	//parse reading level bounds
	double readMin = 0; //holds reading level bounds
	double readMax = 0;
	
	string minString = argv[3]; //holds reading level bounds as strings from arguments
	string maxString = argv[4];
	
	for(int i = 0; i < (int)minString.size(); i++) //checks that min reading level is valid input
	{
		if(argv[3][i] != '.' && (argv[3][i] < '0' || argv[3][i] > '9'))
		{
			cerr << "Minimum reading level should be a decimal number" << endl;
			return -1;
		}
	}
	
	for(int i = 0; i < (int)maxString.size(); i++) //checks that max reading level is valid input
	{
		if(argv[4][i] != '.' && (argv[4][i] < '0' || argv[4][i] > '9'))
		{
			cerr << "Maximum reading level should be a decimal number" << endl;
			return -1;
		}
	}
	
	readMin = atof(argv[3]); //parses reading level bounds from string to double
	readMax = atof(argv[4]);
	
	if(readMin >= readMax) //checks that reading level bounds are valid
	{
		cerr << "Reading level bounds are invalid" << endl;
		return -1;
	}
	
	//Document similarity things go here
	
	DocSim ds(docVec);
	double sim;
	
	for(int i = 1; i < (int)docVec.size(); i++)
	{
		if(docVec[i].getReadingLevel() >= readMin && docVec[i].getReadingLevel() <= readMax)
		{
			//cout << "Document " << docVec[i].getName() << " is in the reading level bounds" << endl;
			sim = ds.sim(0, i);
			docVec[i].setSimilarity(sim);
			//cout << "Document " << docVec[i].getName() << " sim is " << sim << endl;
		}
	}
	
	sim = 0;
	string mostSimilar;
	
	for(int i = 1; i < (int)docVec.size(); i++)
	{
		if(docVec[i].getSimilarity() > sim)
		{
			sim = docVec[i].getSimilarity();
			mostSimilar = docVec[i].getName();
		}
	}
	
	if(mostSimilar.empty())
	{
		cerr << "There are no documents within the specified reading level" << endl;
		return -1;
	}

	cout << mostSimilar << endl;
	
	return 0;
}
