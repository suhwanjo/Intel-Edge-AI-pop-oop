#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	// 여유롭게 X
	// 정수 : char, short, int, long
	char cNum1 = 200; // 1 Byte, -2^7 ~ 2^7-1
	printf("char : %d \n", cNum1);

	unsigned char cNum2 = 200; // 1 Byte, 0 ~ 2^8-1
	printf("unsigned char : %d \n", cNum2);

	short cShort1 = 40000; // 2 Byte, -2^15 ~ 2^15-1 = 32676
	printf("short : %d \n", cShort1);

	unsigned short cShort2 = 40000; // 2 Byte, 0 ~ 2^16-1 = 65535
	printf("unsigned short : %d \n", cShort2);

	int cInt1 = 2147483648; // 4 Byte : -2147483648 ~ 2147483647
	printf("int : %d \n", cInt1);

	unsigned int cInt2 = 3147483648; // 4 Byte : 0 ~ 42억
	printf("u int : %u \n", cInt2);

	long long lNum1 = 1111111111111111111; // 8 Byte : -900경 ~ 900경
	printf("long long : %lld", lNum1);

	unsigned long long lNum2;
}