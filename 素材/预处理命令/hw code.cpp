#include <iostream>
using namespace std;
#define MAX(x, y)     (((x) > (y)) ? (x) : (y))
#define MIN(x, y)     (((x) < (y)) ? (x) : (y))
int main()
{
	
	int x = 100;
	int y = 300;
	int max = MAX(x, y);
	int min = MIN(x, y);
	cout << "max = " << max << " min = " << min << endl;
	return 0;
}