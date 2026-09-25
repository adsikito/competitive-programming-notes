#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;

stack<char> stk;
char str[256];
int main() {
	
	cin >> str;
	int slen = strlen(str);
	for (int i = 0; i < slen; i++) {
		if (str[i] == '@')
			break;
		else if (str[i] == '(') 
			stk.push(str[i]);
		
		else if(str[i] == ')'){
			if(stk.top() == '(')
				stk.pop();
			else if(stk.empty()){
				cout << "NO" << endl;
				return 0;
			}
		}
	}

	if (!stk.empty())
		cout << "NO" << endl;
	else
		cout << "YES";

	return 0;
}

/*
(()))@
*/
