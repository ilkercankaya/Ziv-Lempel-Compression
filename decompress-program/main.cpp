#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool doesExist (string SDictionary [], string str, int &size) //if it doesnt exist then put it
{
		for(int i=0 ; i<size; i++)
        {
			if(SDictionary[i] == str)
			{
					return true;
			}
        }
		return false;
}

bool doesExistCode (string SDictionary [], string str, int &size) //if it doesnt exist then put it
{
		int valueIndex = stoi(str);
		if(valueIndex<size)
			return true;
		else
			return false;
}

bool fillDictionaryFull (string SDictionary [], string str, int &size) //if it doesnt exist then put it
{
	
	if(!doesExist(SDictionary,str,size))
	{
	SDictionary[size] = str;
	size++;
	return true;
	}	
	else 
	return false;
}

void initiliazeDictionary (string SDictionary [])
{
	
	for (int i = 0; i<256; i++) //fill dictionary with 256 values
	{
	string value;
	value = i;
	SDictionary [i] =  value;
	}
}

string getKey(string SDictionary [],string Value)
{
		int valueIndex = stoi(Value);
		return SDictionary[valueIndex];
}


void display(string SDictionary [],int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Code: " << i << " Key: " << SDictionary[i] << endl;
	}
}

bool outputFilePrinter (string SDictionary [], ofstream & output, string word,int &size) //output according to compress
{
	if(doesExistCode(SDictionary,word,size))
	{
		output << getKey(SDictionary,word);
		return true;
	}
	else
		return false;
}

void insertNode(string SDictionary [], string value, int&size)
{
		SDictionary[size] = value;
            size++;
        
}

int main()
{
	string SDictionary[4096];
	int size =256;
	char ch='a';
    ifstream deneme ("compout.txt");
	ofstream sonuc("decompout.txt");
	cout << "Program is starting. Reading file from compin.txt!!!" << endl << endl;
	initiliazeDictionary(SDictionary);
	string word; //keep following of words
	string lastWord; //keep following of words
	int MaxSize = 1;
	while(!deneme.eof()) //eof returns true if next character
	 //is eof
	{
		deneme.get(ch);
		if(ch !=' ')
		word += ch;
		while(ch !=' ')
		{
			deneme.get(ch);
			if(ch !=' ')
			word += ch;
		}
		if(MaxSize==1)//for the first code of the input
			lastWord = word;
		if(!deneme.eof()) //eof guard added if last value is taken or not after .get
		{
			if (outputFilePrinter(SDictionary,sonuc, word,size)) //if exists in dictinary to output nad prints already
			{
				string pr;
				string temp = getKey(SDictionary,word);
				char ph_c = temp.at(0);
				pr = ph_c;
				if(!doesExist(SDictionary, getKey(SDictionary, lastWord)+pr , size) &&MaxSize !=1)//if doesnt exist insert
				insertNode(SDictionary, getKey(SDictionary, lastWord)+pr,size);
				MaxSize++;
				lastWord = word;
				word="";
			}
			else
			{
				string pr;
				string temp = getKey(SDictionary,lastWord);
				char ph_c = temp.at(0);
				pr = ph_c;
				insertNode(SDictionary,getKey(SDictionary,lastWord)+pr,size);//have to insert
				sonuc << getKey(SDictionary,word); //print
				MaxSize++;
				lastWord = word;
				word="";
			}
	  }
	}
	cout << "The Dictionary is found as:"<< endl;
	display(SDictionary,size);
	deneme.close();
	sonuc.close();
	cout << endl << "Program exiting!"<< endl << endl;
	return 0;
}