


#include <iostream>

using namespace std;
//class Person {
//protected:
//	string name;
//	int age;
//public:
//	Person(){}
//	Person(string name, int age) :name(name), age(age) {}
//	virtual ~Person() {
//		cout << "Call ~Person()" << endl;
//	}
//	virtual void info() {
//		cout << "person info:" << this->name << "  " << this->age << endl;
//	}
//};
//class Student :public Person {
//protected:
//	double score;
//public:
//	Student() {
//	}
//	Student(string name,int age,double score):Person(name,age),score(score){}
//	~Student() {
//		cout << "Call ~Student()" << endl;
//	}
//	virtual void info() {
//		cout << "student info:" << this->name << "  " << this->age << "  " << this->score <<  endl;
//	}
//};

//class Animal {
//public:
//	virtual void eat() {
//		cout << "Animal eat" << endl;
//	}
//};
//class Dog :public Animal {
//public:
//	virtual void eat() {
//		cout << "Dog eat" << endl;
//	}
//};
//class Cat :public Animal {
//public:
//	virtual void eat() {
//		cout << "Cat eat" << endl;
//	}
//};


//class Animal {
//public:
//	virtual void func1() {
//		cout << "Animal func1" << endl;
//	}
//	virtual void func2() {
//		cout << "Animal func2" << endl;
//	}
//};
//class Dog : public Animal {
//public:
//	virtual void func3() {
//		cout << "Dog func3" << endl;
//	}
//	virtual void func1() {
//		cout << "Dog func1" << endl;
//	}
//	virtual void func4() {
//		cout << "Dog func4" << endl;
//	}
//};;

class AbstractDrinking {
public:
	//烧水
	virtual void boil() = 0;
	//泡
	virtual void brow() = 0;
	//倒入被子
	virtual void pourInCup() = 0;
	//加辅料
	virtual void putSomething() = 0;

	void makeDrink() {
		boil();
		brow();
		pourInCup();
		putSomething();
	}
};
class Coffee :public AbstractDrinking {
public:
	virtual void boil() {
		cout << "煮山泉水" << endl;
	}
	virtual void brow() {
		cout << "泡咖啡" << endl;
	}
	virtual void pourInCup() {
		cout << "咖啡倒入杯子" << endl;
	}
	virtual void putSomething() {
		cout << "加牛奶" << endl;
	}
};

class Tea :public AbstractDrinking {
public:
	virtual void boil() {
		cout << "煮白开水" << endl;
	}
	virtual void brow() {
		cout << "泡茶" << endl;
	}
	virtual void pourInCup() {
		cout << "茶倒入杯子" << endl;
	}
	virtual void putSomething() {
		cout << "加盐" << endl;
	}
};


void doBussiness(AbstractDrinking* ad) {
	ad->makeDrink();
	delete ad;
}




int main() {

	doBussiness(new Coffee());
	cout << endl;
	doBussiness(new Tea());



	/*Animal* pa = new Dog();
	pa->func1();*/



	/*Person* p1 = new Student("张三", 23, 89);
	p1->info();
	delete p1;*/



	/*Animal* pa = new Animal();
	pa->eat();
	pa = new Dog();
	pa->eat();
	pa = new Cat();
	pa->eat();*/

	/*Animal a1;
	Animal& ya1 = a1;
	ya1.eat();
	Dog d1;
	Animal& ya2 = d1;
	ya2.eat();*/




	//Person* p1 = new Person("zxx", 20);
	//p1->info();
	///*Student* s1 = new Student("xiaoming", 11, 90);
	//s1->info();*/
	//p1 = new Student("xiaoming", 11, 90);
	//p1->info();
	/*Person p1("swk", 500);
	Student s1("bgj", 300, 99);
	Person& pper = p1;
	Person& pstu = s1;
	pper.info();
	pstu.info();*/

	return 0;
}

