#include <iostream>
#include <cstring>
#include <string>

bool average(int a[], int size, double& avg) {  // 원본 변수에 직접 접근하여 값을 읽거나 수정할 수 있음. 참조자를 사용하지 않으면 값을 복사하거나 포인터를 사용
	if (size <= 0)
		return false;
	double sum = 0;
	for (int i = 0; i < size; i++)
		sum += a[i];
	avg = sum / size;
	return true;
}	
using namespace std;

int main() {
	int x[] = { 1,2,3,4 };
	double avg;
	if (average(x, 4, avg))
		cout << avg;
	else
		cout << "1개 이상";
}
