#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

void main() {
	// 심화 퀴즈 : 2부터 1000까지의 소수를 출력하고 합계
	int result = 0;
	for (int i = 2; i <= 1000; i++) {
		for (int j = 2; j <= i; j++) {
			if (i % j == 0) {
				if (i == j) {
					result += i;
					printf("%d\n", i);
				}
				else
					break;
			}
		}
	}
	printf("%d", result);

	//int hap = 0;
	//printf("%d\n", 2);
	//hap += 2;
	//
	//for (int num = 3; num <= 1000; num += 2) {
	//	// 일단 num을 소수로 가정
	//	bool isPrime = true;
	//	for (int div = 2; div < num; div++) {
	//		if (num % div == 0) {
	//			isPrime = false;
	//		}
	//	}
	//	if (isPrime == true) {
	//		printf("%d\n", num);
	//		hap += num;
	//	}
	//}
	//printf("%d", hap);
}


