#include "Wordmap.h"

bool Wordmap::wordmap_add(string s) {
	map<Word, int>::iterator it = map_1.find(s);
	if (it == map_1.end()) {
		pair<Word, int> p(Word(s), 1);
		map_1.insert(p);
	}
	else {
		it->second++;
	}
	return 1;
}

void Wordmap::show() {
	for (map<Word, int>::iterator it = map_1.begin(); it != map_1.end(); it++) {
		cout << it->first.getWord() << ":³öÏÖ" << it->second << "´Î" << endl;
	}
}
