//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <stdlib.h>
//
//void main() {
//	char str[100]; // 읽어올 한줄
//	FILE* rfp;
//
//	// 파일 처리 3단계
//	// (1) 파일 열기
//	rfp = fopen("c:/windows/win.ini", "rt");
//
//	// (2) 파일 읽거나 쓰기
//	int count = 1;
//	while (1) {
//		fgets(str, 100, rfp);
//
//		if (feof(rfp))
//			break;
//
//		printf("%2d행 : %s", count, str);
//		count++;
//
//	}
//
//
//	// (3) 파일 닫기
//	fclose(rfp);
//
//	
//
//}