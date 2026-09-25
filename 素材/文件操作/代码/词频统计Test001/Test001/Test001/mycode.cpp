#include "mycode.h"

//建立集合和映射的实例对象
WordSet set_111;
Wordmap map_111;

void showData() {
	cout << endl;
	cout << "单词集合为：" << endl;
	set_111.show();
	cout << endl;
	cout << "单词集合及出现次数：" << endl;
	map_111.show();
	cout << endl;
}

//打开文件读入数据，装入集合
void dataProcessing() {
	

	//打开文件，读取文本
	int pos = 0;
	string s = " ";
	string delimet = ",.?";
	ifstream in1;
	in1.open("data.txt");
	char c;
	while (in1.peek() != EOF)
	{
		in1.read(&c, 1);
		cout << c;
	}
	in1.close();
	ifstream in("data.txt");
	while (!in.eof())
	{
		getline(in, s);
		if (s == " ") {
			continue;
		}
		pos = 0;
		while ((pos = s.find_first_of(delimet, pos)) != string::npos) {
			s.replace(pos, 1, " ");
		}
		istringstream stringeam(s);
		while (!stringeam.eof()) {
			stringeam >> s;
			if (s == " ") {
				continue;
			}
			set_111.wordset_add(s);
			map_111.wordmap_add(s);
		}
	}
	in.close();
}

