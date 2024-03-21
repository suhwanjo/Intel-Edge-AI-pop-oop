#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <Windows.h> // GUI 지원 기능

void main() {
	//int size = 50;
	//int* p;
	//p = (int *)malloc(sizeof(int)* size); // Heap 영역에 int형 크기로 size 개수만큼 메모리 확보

	//*p = 100; == p[0]
	//*(p + 1) = 101; == p[1]
	//*(p + 2) = 102;* ==  p[2]
	int size = 100;
	int count = 1234;
	int sum = 0;

	// int p[size] 와 같음
	int* p = (int*)malloc(sizeof(int) * size); // Stack에는 포인터 변수(4Byte)만 할당, Heap의 주소를 참조
	free(p);								   // Heap에는 정수형(4Byte) size(100) 만큼의 개수가 할당

	for (int i = 0; i < size; i++) {
		p[i] = count;
		sum += count;
		count++;
		printf("%d ", p[i]);
	}
	printf("\n");
	printf("sum : %d \n", sum);
	int size1 = 5;
	double count1 = 0.1;
	double count2 = 0.5;
	double* p1 = (double*)malloc(sizeof(double) * size1);
	double* p2 = (double*)malloc(sizeof(double) * size1);
	for (int i = 0; i < size1; i++) {
		p1[i] = count1;
		p2[i] = count2;
		count1 += 0.1;
		count2 -= 0.1;

	}
	for (int i = 0; i < size1; i++) {
		printf("%lf ", p1[i]);
	}
	printf("\n");
	for (int i = 0; i < size1; i++) {
		printf("%lf ", p2[i]);
	}
	free(p1);
	free(p2);
}
