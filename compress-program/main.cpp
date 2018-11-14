#include <string>
#include <iostream>
#include "HashTable.cpp"
#include <fstream>
#include <algorithm> 
using namespace std;

template<typename K, typename V>
bool fillDictionaryFull (HashMap<K, V> *dictionary, K ch , int& code) //if it doesnt exist then put it
{
	
	if(!dictionary->doesExist(ch))
	{
   	K ch_str = to_string(code);
	dictionary->insertNode(ch,ch_str);
	code++;
	return true;
	}	
	else 
	return false;
}

template<typename K, typename V>
void initiliazeDictionary (HashMap<K, V> *dictionary)
{
	
	for (int i = 0; i<256; i++) //fill dictionary with 256 values
	{
   	string ch_str = to_string(i);
	string value;
	value = i;
	dictionary->insertNode(value,ch_str);
	}
}

template<typename K, typename V>
bool outputFileFiller (HashMap<K, V> *dictionary, ofstream & output, V word) //output according to compress
{
	if(dictionary->doesExist(word))
	{
		output << dictionary->get(word) << " ";
		return true;
	}
	else
		return false;
}


int main()
{
	char ch;
	HashMap<string, string> *dictionary = new HashMap<string, string>;
    ifstream deneme ("compin.txt");
	ofstream sonuc("compout.txt");
	int code = 256;
	cout << "Program is starting. Reading file from compin.txt!!!" << endl << endl;
	initiliazeDictionary(dictionary);
	string word; //keep following of words
	//look for the highest size first 
	//then size -1... till found.
	//when outputted something get the next charecter and put that to dictionary
	int MaxSize = 1;
	while(!deneme.eof() || word!="" ) //eof returns true if next character
	 //is eof
	{
		while (word.length()!=MaxSize && !deneme.eof()) //get as according to maxSize of prefix
		{
			
			deneme.get(ch);
			if(!deneme.eof())
			word += ch;
		}
		if (outputFileFiller(dictionary,sonuc, word)) //if exists in dictinary to output
		{
		
			string WordTemp = word;
			word = "";
			deneme.get(ch);
			if(!deneme.eof()) //eof guard added if last value is taken or not after .get
			{			
			WordTemp += ch;
			word+= ch;
			if(fillDictionaryFull(dictionary,WordTemp,code)) //if it is able to add increase maxWord size
				MaxSize++;
			}
		}
		else
		{
				for (int z = MaxSize-1; z>0; z-- )
				{
					string wordTemp = word.substr(0,z);
					if (outputFileFiller(dictionary,sonuc, wordTemp)) //if exists in dictinary to output
					{
						string WordTempTwo = word.substr(0,wordTemp.length()+1);
						word = word.substr(wordTemp.length(),word.length()-wordTemp.length());
						fillDictionaryFull(dictionary,WordTempTwo,code); //if it is able to add increase maxWord size
						break;
					}
				}
		}
	}
	cout << "The Dictionary is found as:"<< endl;
	dictionary->display();
	deneme.close();
	sonuc.close();
	cout << endl << "Program exiting!"<< endl << endl;
	return 0;
}