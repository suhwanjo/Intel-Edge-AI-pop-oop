#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Circle {
public:
	static int numOfCircles; // 클래스의 모든 인스턴스(객체)가 공유하는 변수
	int radius;
public:
	Circle(int radius = 1) {
		this->radius = radius;
		numOfCircles++;
	}	
	~Circle(){
		numOfCircles--;
	}
	static int getNumOfCircle() {  // 클래스의 인스턴스 없이 호출 가능
		return numOfCircles;
	}
};

int Circle::numOfCircles = 0;

int main() {
	
	Circle* p = new Circle[10];
	cout << "현재 원 객체수: " << Circle::getNumOfCircle() << endl;
	delete[] p;
	cout << "현재 원 객체수: " << Circle::getNumOfCircle() << endl;
	if (true) {
		Circle a, b;
		cout << "현재 원 객체수: " << Circle::getNumOfCircle() << endl;
	}
	cout << "현재 원 객체수: " << Circle::getNumOfCircle() << endl;

}
