#pragma once
#include<string>
using namespace std;
class Word
{
public:
	Word(string s);
	string getWord()const;
	bool operator<(const Word& a) const;
	bool operator==(string s);
private:
	string s;
};

