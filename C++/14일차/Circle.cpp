#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std에 있는 애들 다 'std::' 안쓰고 사용 가능
#include "Circle.h"
Circle::Circle() {}
Circle::Circle(int r) {
	cout << "새 인스턴스 생성" << endl;
	r = 1;
}
double Circle::getArea() {
	return radius * radius * 3.14;
}