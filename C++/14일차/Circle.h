#pragma once
#ifndef CIRCLE_H  // 헤더파일 한번 더 정의해도 괜찮도록
#define CIRCLE_H
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

#endif // 헤더파일 한번 더 정의해도 괜찮도록