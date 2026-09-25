
#include <iostream>

using namespace std;

class Student {
public:
	string name;
	int age;
	Student(string name, int age) {
		this->name = name;
		this->age = age;
	}
	void operator=(const Student& t) {
		this->name = t.name;
		this->age = t.age;
	}
	
	bool operator>(Student& t) {
		if (this->age > t.age) {
			return 1;
		}
		else {
			return 0;
		}
	}

	bool operator<(Student& t) {
		if (this->age < t.age) {
			return 1;
		}
		else {
			return 0;
		}
	}

	bool operator<=(Student& t) {
		if (this->name < t.name) {
			return 1;
		}
		else {
			return 0;
		}
	}

	void printInfo() {
		cout << this->name << "  " << this->age << endl;
	}
};

class Complex {
public:
	double r, i;
	Complex(){}
	Complex(double r, double i) {
		this->r = r;
		this->i = i;
	}
	Complex operator+(Complex& c) {
		Complex c2;
		c2.r = this->r + c.r;
		c2.i = this->i + c.i;
		return c2;
	}

	Complex operator-(Complex& c) {
		Complex c2;
		c2.r = this->r - c.r;
		c2.i = this->i - c.i;
		return c2;
	}
	void print() {
		cout << this->r << "  " << this->i << endl;
	}
};

const int SIZE = 5;
class SafeArr {
public:
	int arr[SIZE];
	SafeArr() {
		register int i = 0;
		for (; i < SIZE; i++) {
			arr[i] = i;
		}

	}
	int operator[](int i) {
		if (i >= SIZE) {
			cout << "下标越界" << endl;
			return -1;
		}
		return arr[i];
	}
};

class Animal {
private:
	int age;
public:
	Animal(int age) {
		this->age = age;
	}
	Animal() {}

	bool operator>(Animal& a) {
		if (this->age > a.age) {
			return 1;
		}
		else {
			return 0;
		}
	}
	bool operator==(Animal& a) {
		if (this->age == a.age) {
			return 1;
		}
		else {
			return 0;
		}
	}
	bool operator<(Animal& a) {
		if (this->age < a.age) {
			return 1;
		}
		else {
			return 0;
		}
	}
};


int main() {


	Animal a1(10), a2(20), a3(30);
	if (a1 < a2) {
		cout << "a1 < a2" << endl;
	}

	if (a1 == a3) {
		cout << "a1 == a3" << endl;
	}
	else {
		cout << "a1 != a3" << endl;
	}
	if (a3 > a2) {
		cout << "a3 > a2" << endl;
	}



	/*SafeArr arr;
	cout << arr[1] << endl;
	cout << arr[10] << endl;*/


	/*Complex c1(11, 12), c2(10, 11), c3, c4;
	c3 = c1 + c2;
	c3.print();
	c4 = c1 - c2;
	c4.print();*/

	//Student s1("as", 20), s2("zw", 30);

	//if (s1 <= s2) {
	//	cout << "s1 <= s2" << endl;
	//}













	return 0;
}

