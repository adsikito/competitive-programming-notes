#pragma once
#include <iostream>
#include "Word.h"
#include <set>
using namespace std;
class WordSet
{
private:
	set<Word> set_1;
public:
	bool wordset_add(string s);
	void show();
};

