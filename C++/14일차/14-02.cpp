#include <iostream>
#include <cstring>
#include <string>
using namespace std;  // std에 있는 애들 다 'std::' 안쓰고 사용 가능

class Circle {
	/// 클래스의 속성
private:
	int radius;
	// 게터/세터
public:
	void setRadius(int value) { radius = value; };
	int getRadius() { return radius; };
	/// 클래스의 기능
public:
	Circle();  // 함수 오버로딩
	Circle(int);  // 생성자
	double getArea();
};
Circle::Circle() {}
Circle::Circle(int r) {
	cout << "새 인스턴스 생성" << endl;
	r = 1;
}
double Circle::getArea() {
	return radius * radius * 3.14;


}
int main() {
	Circle donut(1);
	Circle donut1;
	donut.setRadius(2);

	cout << "도넛의 면적은" << donut.getArea() << "입니다.";

}
// 예제
class Rectangle {

public:
	int width, height;
public:
	Rectangle();
	Rectangle(int);
	Rectangle(int, int);
	bool isSquare();
};

Rectangle::Rectangle(){}
Rectangle::Rectangle(int wh) {
	width = wh;
	height = wh;
}
Rectangle::Rectangle(int w, int h) {
	width = w;
	height = h;
}

bool Rectangle::isSquare() {
	if (width == height)
		return true;
	return false;
}

int main() {
	Rectangle rect1;
	Rectangle rect2(3,5);
	Rectangle rect3(3);

	if (rect1.isSquare())
		cout << "rect1은 정사각형이다." << endl;
	if (rect2.isSquare())
		cout << "rect2은 정사각형이다." << endl;
	if (rect3.isSquare())
		cout << "rect3은 정사각형이다." << endl;
}