#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std에 있는 애들 다 'std::' 안쓰고 사용 가능
#include "Add.h"
Adder::Adder(int a, int b) {
	op1 = a;
	op2 = b;
}

int Adder::process() {
	return op1 + op2;
}

void Calulator::run() {
	cout << "두 개의 수를 입력하세요. : ";
	int a, b;
	cin >> a >> b;
	Adder adder(a, b);
	cout << adder.process();
}