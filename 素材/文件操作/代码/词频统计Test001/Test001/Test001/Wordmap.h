#pragma once
#include <iostream>
#include <map>
#include "Word.h"
class Wordmap
{
private:
	map<Word, int> map_1;
public:
	bool wordmap_add(string s);
	void show();
};

