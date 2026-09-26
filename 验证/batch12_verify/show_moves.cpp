#include <iostream>
#include <string>
using namespace std;
string moves;
void moveShow(int x, char s, char e, char h) {
    if (x == 1) { moves += string(1, '0' + x); moves += " "; moves += s; moves += "--->"; moves += e; moves += "\n"; return; }
    moveShow(x - 1, s, h, e);
    moves += string(1, '0' + x); moves += " "; moves += s; moves += "--->"; moves += e; moves += "\n";
    moveShow(x - 1, h, e, s);
}
int main() { moveShow(3, 'a', 'c', 'b'); cout << moves; return 0; }
