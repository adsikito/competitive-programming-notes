#include "myCal.h"
int main()
{
	char select;
	double a = 0, b = 0;
	while (1)
	{
		menu();
		cout << "请选择序号进行计算：";
		cin >> select;
		switch (select)
		{
		case '1':
			Add(a, b);
			break;
		case '2':
			Sub(a, b);
			break;
		case '3':
			Mul(a, b);
			break;
		case '4':
			Div(a, b);
			break;
		case '5':
			Sur(a, b);
			break;
		case '6':
			Pow(a);
			break;
		case '7':
			Sqrt(a);
			break;
		case '8':
			Powp(a, b);
			break;
		default:
			quit();
			break;
		}
	}
	system("pause");
	return 0;
}
