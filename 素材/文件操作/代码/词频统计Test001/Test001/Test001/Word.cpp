#include "Word.h"

Word::Word(string s) {
	this->s = s;
}
string Word::getWord() const{
	return s;
}
bool Word::operator<(const Word& a) const{
	return s < a.getWord();
}
bool Word::operator==(string s) {
	return this->s == s;
}
