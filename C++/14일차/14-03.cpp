#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std에 있는 애들 다 'std::' 안쓰고 사용 가능

int main() {
	// 1차원 배열 할당
	cout << "몇 개?";
	int n; // 변수
	cin >> n;

	int* p = new int[n]; // 동적 배열

	delete[] p;

	// 2차원 배열 할당
	int h, w;
	cout << "행?";
	cin >> h;
	cout << "열?";
	cin >> w;

	int** p = new int*[h];
	for (int i = 0; i < h; i++)
		p[i] = new int[w];

	for (int i = 0; i < h; i++)
		delete p[i];
	delete[] p;
}