#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std에 있는 애들 다 'std::' 안쓰고 사용 가능

// Circle 클래스
class Circle {
   /// 클래스의 속성
private:
   int radius; // 반지름 속성(private)

   // 게터/세터
public:
   void setRadius(int value) { radius = value; }; // 반지름 설정 메서드
   int getRadius() { return radius; }; // 반지름 반환 메서드

   /// 클래스의 기능
public:
   Circle(); // 기본 생성자(인자 없음), 함수 오버로딩
   Circle(int); // 매개변수를 가진 생성자 

   double getArea(); // 원의 면적을 계산하는 메서드
};

Circle::Circle() {} // 기본 생성자 구현

Circle::Circle(int r) { // 매개변수를 가진 생성자 구현
   cout << "새 인스턴스 생성" << endl; 
   r = 1; // 반지름을 1로 초기화
}

double Circle::getArea() { // 원의 면적 계산 메서드 구현
   return radius * radius * 3.14; // 반지름의 제곱 * 파이
}

int main() {
   Circle donut(1); // 반지름 1인 Circle 객체 생성
   Circle donut1; // 기본 생성자로 Circle 객체 생성
   
   donut.setRadius(2); // donut 객체의 반지름을 2로 설정
   
   cout << "도넛의 면적은" << donut.getArea() << "입니다."; // donut의 면적 출력
}

// Rectangle 클래스 예제
class Rectangle {
public:
   int width, height; // 너비, 높이 속성(public)

public:
   Rectangle(); // 기본 생성자
   Rectangle(int); // 정사각형 생성자
   Rectangle(int, int); // 직사각형 생성자
   
   bool isSquare(); // 정사각형인지 확인하는 메서드
};

Rectangle::Rectangle(){} // 기본 생성자 구현

Rectangle::Rectangle(int wh) { // 정사각형 생성자 구현
   width = wh;
   height = wh;
}

Rectangle::Rectangle(int w, int h) { // 직사각형 생성자 구현
   width = w;
   height = h;
}

bool Rectangle::isSquare() { // 정사각형 확인 메서드 구현
   if (width == height) 
       return true; // 너비와 높이가 같으면 정사각형
   return false;
}

int main() {
   Rectangle rect1; // 기본 생성자로 객체 생성
   Rectangle rect2(3,5); // 너비 3, 높이 5인 직사각형 객체 생성
   Rectangle rect3(3); // 너비와 높이가 3인 정사각형 객체 생성
   
   if (rect1.isSquare())
       cout << "rect1은 정사각형이다." << endl;
   if (rect2.isSquare())
       cout << "rect2은 정사각형이다." << endl;
   if (rect3.isSquare())
       cout << "rect3은 정사각형이다." << endl;
}
