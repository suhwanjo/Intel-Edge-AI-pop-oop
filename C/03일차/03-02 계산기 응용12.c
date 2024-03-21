#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	int iNum1, iNum2;
	float fResult, fResult2, fResult3, fResult4;

	printf("첫 번째 숫자를 입력하세요: ");
	scanf("%d", &iNum1);
	printf("두 번째 숫자를 입력하세요: ");
	scanf("%d", &iNum2);


	fResult = iNum1 + iNum2;
	fResult2 = iNum1 - iNum2;
	fResult3 = iNum1 * iNum2;
	fResult4 = ((float)iNum1 / (float)iNum2);

	printf("%d + %d = %f \n", iNum1, iNum2, fResult);
	printf("%d - %d = %f \n", iNum1, iNum2, fResult2);
	printf("%d * %d = %f \n", iNum1, iNum2, fResult3);
	if (iNum2 == 0)
		printf("0으로 나눌 수 없습니다");
	else
		printf("%d / %d = %f \n", iNum1, iNum2, fResult4);


}