#include "WordSet.h"
bool WordSet::wordset_add(string s) {
	set_1.insert(Word(s));
	return 1;
}
void WordSet::show() {
	for (set<Word>::iterator it = set_1.begin(); it != set_1.end(); it++) {
		cout << (*it).getWord() << " ";
	}
}