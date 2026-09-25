
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

	cout << "欢迎光临本店" << endl;
	cout << "请收好您的优惠券,面值20元" << endl;
	int yhq = 20;

	cout << "-------------------自助点餐系统-------------------" << endl;
	cout << "菜单：" << endl;
	cout << "1火锅 2回锅肉 3宫保鸡丁 4夫妻肺片 5毛血旺 6麻婆豆腐 7东坡肘子 8水煮牛肉" << endl;
	cout << "9龙抄手 10钟水饺 11串串香 12肥肠粉 13担担面" << endl;
	cout << "14可乐 15雪碧 16脉动 17果缤纷 18果粒橙 19营养快线" << endl;
	cout << "套餐A(优惠10)：火锅 回锅肉 东坡肘子，任选其一" << endl;
	cout << "龙抄手 钟水饺 串串香，任选其一" << endl;
	cout << "可乐 雪碧，任选其一" << endl;
	cout << "套餐B（优惠12）：火锅 回锅肉 东坡肘子 水煮牛肉，任选其一" << endl;
	cout << "肥肠粉 担担面，任选其一" << endl;
	cout << "脉动 果缤纷 果粒橙，任选其一" << endl;
	cout << "本店消费满100元，可加1元，换购一种饮料" << endl;

	//选择单点 套餐 结账菜单变量
	char c;
	//接收菜的编号
	int input;

	//菜名数组
	string name[19] = {"火锅","回锅肉","宫保鸡丁","夫妻肺片","毛血旺","麻婆豆腐","东坡肘子","水煮牛肉","龙抄手","钟水饺",
						"串串香","肥肠粉","担担面","可乐","雪碧","脉动","果缤纷","果粒橙","营养快线"};
	//价格数组
	int price[19] = { 30,20,15,45,21,34,22,23,31,16,18,19,11,9,13,10,9,8,6 };
	//数量数组
	int cnt[19] = { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0 };
	int cnt2[19] = { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0 };
	//总价格  总优惠
	int total = 0, fp = 0;

	while (true)
	{
		cout << "A单点  B套餐  C结账" << endl;
		cin >> c;
		if (c == 'A')
		{
			//单点
			cout << "输入编号点餐,输入0结束点餐" << endl;
			while (true)
			{
				cin >> input;
				if (input == 0) {
					break;
				}
				switch (input) {
				case 1:
					cnt[0]++;
					break;
				case 2:
					cnt[1]++;
					break;
				case 3:
					cnt[2]++;
					break;
				case 4:
					cnt[3]++;
					break;
				case 5:
					cnt[4]++;
					break;
				case 6:
					cnt[5]++;
					break;
				case 7:
					cnt[6]++;
					break;
				case 8:
					cnt[7]++;
					break;
				case 9:
					cnt[8]++;
					break;
				case 10:
					cnt[9]++;
					break;
				case 11:
					cnt[10]++;
					break;
				case 12:
					cnt[11]++;
					break;
				case 13:
					cnt[12]++;
					break;
				case 14:
					cnt[13]++;
					break;
				case 15:
					cnt[14]++;
					break;
				case 16:
					cnt[15]++;
					break;
				case 17:
					cnt[16]++;
					break;
				case 18:
					cnt[17]++;
					break;
				case 19:
					cnt[18]++;
					break;
				}
			}

			//每种菜名字，数量和小计
			total = 0;
			for (int i = 0; i < 19; i++)
			{
				if (cnt[i] != 0) {
					cout << name[i] << price[i] << "元，数量:" << cnt[i] << " 小计:" << price[i] * cnt[i] << "元" << endl;
					total += price[i] * cnt[i];
				}
			}
			cout << "单点总计:" << total << "元,优惠:" << fp << "元" << endl;
		}
		else if (c == 'B') {
			//套餐
			while(1){
				cout << "套餐A    套餐B  （输入字母确定)" << endl;
				cin >> c;
				if (c == 'A') {
					//套餐A
					fp += 10;
					cout << "1火锅 2回锅肉 7东坡肘子" << endl;
					cin >> input;
					switch (input) {
					case 1:
						cnt2[0] ++;
						break;
					case 2:
						cnt2[1] ++;
						break;
					case 7:
						cnt2[6] ++;
						break;
					}

					cout << "9龙抄手 10钟水饺 11串串香" << endl;
					cin >> input;
					switch (input) {
					case 9:
						cnt2[8] ++;
						break;
					case 10:
						cnt2[9] ++;
						break;
					case 11:
						cnt2[10] ++;
						break;
					}
					cout << "14可乐 15雪碧" << endl;
					cin >> input;
					switch (input) {
					case 14:
						cnt2[13] ++;
						break;
					case 15:
						cnt2[14] ++;
						break;
					}

					break;
				}
				else if (c == 'B') {
					//套餐B
					fp += 12;
					cout << "1火锅 2回锅肉 7东坡肘子 8水煮牛肉" << endl;
					cin >> input;
					switch (input) {
					case 1:
						cnt2[0] ++;
						break;
					case 2:
						cnt2[1] ++;
						break;
					case 7:
						cnt2[6] ++;
						break;
					case 8:
						cnt2[7]++;
					}

					cout << "12肥肠粉 13担担面" << endl;
					cin >> input;
					switch (input) {
					case 12:
						cnt2[11] ++;
						break;
					case 13:
						cnt2[12] ++;
						break;
					
					}
					cout << "16脉动 17果缤纷 18果粒橙" << endl;
					cin >> input;
					switch (input) {
					case 16:
						cnt2[15] ++;
						break;
					case 17:
						cnt2[16] ++;
						break;
					case 18:
						cnt2[17]++;
						break;
					}

					break;
				}
				else {
					cout << "请输入正确的大写字母进行套餐选择!!" << endl;
				}
			}
			total = 0;  //数量累加的，所以total需要清零
			for (int i = 0; i < 19; i++) {
				if (cnt2[i] != 0) {
					total += price[i] * cnt2[i];
					cout << name[i] << price[i] << "元，数量:" << cnt2[i] << " 小计:" << price[i] * cnt2[i] << "元" << endl;
				}
			}
			total -= fp;
			cout << "套餐总计:" << total << "元，优惠:" << fp << "元" << endl;
		}
		else if (c == 'C') {
			//结账

			total = 0;
			cout  << "单点消费:" << endl;
			for (int i = 0; i < 19; i++) {
				if (cnt[i] != 0) {
					cout << name[i] << price[i] << "元，数量:" << cnt[i] << " 小计：" << price[i] * cnt[i] << "元" << endl;
					total += price[i] * cnt[i];
				}
			}

			cout << "套餐消费:" << endl;
			for (int i = 0; i < 19; i++) {
				if (cnt2[i] != 0) {
					cout << name[i] << price[i] << "元，数量:" << cnt2[i] << " 小计：" << price[i] * cnt2[i] << "元" << endl;
					total += price[i] * cnt2[i];
				}
			}
			total -= fp;
			cout << "总费用:" << total << "元,优惠" << fp << "元" << endl;

			if (total >= 100)
			{
				cout << "总消费超过了100元，请问是否加1元换购饮料(Y/N)" << endl;
				cin >> c;
				if (c == 'Y') {
					total += 1;
					cout << "14可乐 15雪碧 16脉动 17果缤纷 18果粒橙" << endl;
					cin >> input;
					switch (input)
					{
					case 14:
						fp += price[13] - 1;
						break;
					case 15:
						fp += price[14] - 1;
						break;
					case 16:
						fp += price[15] - 1;
						break;
					case 17:
						fp += price[16] - 1;
						break;
					case 18:
						fp += price[17] - 1;
						break;
					
					}
				}
			}

			cout << "您总共消费：" << total << "元，优惠了" << fp << "元" << endl;
			cout << "是否使用优惠券(Y/N)" << endl;
			cin >> c;
			if (c == 'Y') {
				total -= yhq;
				fp += yhq;
			}


			cout << "您支付了：" << total << "元，优惠了" << fp << "元" << endl;
			break;

		}
		else {
			cout << "请输入正确的大写字母!!" << endl;
		}

	}
	cout << "-----------------------欢迎下次光临!-------------------------" << endl;

	return 0;
}

