#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std에 있는 애들 다 std 안쓰고 사용 가능
int main() {
	std::cout << "Hello \n" << "HI" << std::endl << 3.14;  // << : 연산자 오버로딩, 호출 X -> 빠름

	cout << "너비 : ";
	int width;
	cin >> width;
	cout << "입력한 너비는" << width << "입니다.";

	char passwd[11];
	cout << "암호 : ";

	// cin >> passwd;
	cin.getline(passwd, 11, '\n');

	cout << "입력한 암호" << passwd << "입니다.";

	string song("fedsdfsf");
	string elvis("엘비스 프레슬리");
	cout << "노래 불러!" << song << endl << "누가 부름??" << elvis;
	return 0;
}