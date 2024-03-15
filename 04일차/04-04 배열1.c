//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#define SIZE 20
//#include <stdbool.h>
//
//void main() {
//	// const int SIZE = 5;
//
//	//int ary[SIZE];
//	//int num = 100;
//
//	//for (int i = 0; i < 5; i++) {
//	//	ary[i] = num;
//	//	printf("%d ", ary[i]);
//	//	num++;
//	//}
//
//	//int ary2[SIZE * 2];
//	//int num2 = 5;
//	//int hap = 0;
//	//for (int i = 0; i < 10; i++) {
//	//	ary2[i] = num2;
//	//	num2 += 5;
//	//	hap += ary2[i];
//	//}
//	//printf("\n%d\n", hap);
//
//	// 퀴즈 : 배열 20개 준비, 2부터 소수 20개 저장, 배열 내용 출력
//	int arr[20];
//	int ctr = 0;
//	for (int i = 2; i < 100; i++) {
//		for (int j = 2; j <= i; j++) {
//			if (i % j == 0) {
//				if (i == j) {
//					arr[ctr] = i;
//					printf("%d\n", arr[ctr]);
//					ctr++;
//				}
//				else
//					break;
//			}
//		}
//		if (ctr >= 20)
//			break;
//	}
//	// while문
//	//(0) 배열 준비하기
//	int ary[SIZE];
//	//(1) 배열에 값 대입하기
//	// 소수 20개 찾아서 배열에 넣기
//	int count = 0;
//	int num = 2;
//	while (1) { // 일단 20개 찾을때까지 무한루프.
//		// num이 소수?
//		bool sosuYN = true;
//		for (int div = 2; div < num; div++) {
//			if (num % div == 0) {
//				sosuYN = false;
//				break;
//			}
//		}
//		if (sosuYN) {
//			ary[count] = num;
//			count++;
//		}
//		// 20개 다 찾았으면,  break;
//		if (count >= SIZE)
//			break;
//		num++;
//	}
//	// (3) 활용하기
//	for (int i = 0; i < SIZE; i++)
//		printf("%d ", ary[i]);
//}