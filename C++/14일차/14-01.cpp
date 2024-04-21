#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std에 있는 애들 다 std 안쓰고 사용 가능
int main() {
   // "Hello \n" 문자열과 "HI" 문자열을 출력한 후 
   // 줄바꿈(std::endl)하고 3.14를 출력합니다.
   // << 연산자는 오버로딩되어 있어서 출력 스트림에 값을 보내는 역할을 합니다.
   std::cout << "Hello \\n" << "HI" << std::endl << 3.14; 

   cout << "너비 : "; // "너비 : " 문자열 출력

   int width; // width 변수 선언

   cin >> width; // 사용자로부터 width 값을 입력받습니다.

   cout << "입력한 너비는" << width << "입니다."; // 입력받은 width 값을 출력합니다.

   char passwd[11]; // 길이가 11인 char 배열 passwd 선언

   cout << "암호 : "; // "암호 : " 문자열 출력

   // cin >> passwd; // 이 방식으로는 공백까지만 입력받을 수 있습니다.
   cin.getline(passwd, 11, '\n'); // cin.getline을 이용해 공백까지 포함된 문자열을 입력받습니다.

   cout << "입력한 암호" << passwd << "입니다."; // 입력받은 passwd 출력

   string song("fedsdfsf"); // string 객체 song 생성 및 초기화
   string elvis("엘비스 프레슬리"); // string 객체 elvis 생성 및 초기화

   cout << "노래 불러!" << song << endl << "누가 부름??" << elvis; // song와 elvis 출력

   return 0; // 프로그램 종료
}
