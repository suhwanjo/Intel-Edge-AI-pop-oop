//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <stdlib.h>
//#include <math.h>
//#include <conio.h>
//#include <Windows.h> // GUI 지원 기능
//
////////////////////////
//// 전역 변수부
////////////////////////
//
//// 윈도우 API 프로그래밍
//HWND hwnd; // 왼도우 화면(외부, 물리적)
//HDC hdc; // 윈도우 화면(내부, 논리적)
//
//FILE *rfp, *wfp;
//char fileName[200];
//#define height 512
//#define width 512
//// 메모리 확보
//unsigned char inImage[height][width];
//unsigned char outImage[height][width];
//
///////////////////////
//// 함수 선언부
///////////////////////
//void loadImage(); void saveImage();
//int getInValue(); double getFlValue();
//void printImage(); void printMenu();
//
//void equalImage();
//void addImage();
//void reverseImage();
//void binaryImage(); int medCalc(); int avgCalc();
//void gammaImage();
//void paraImage();
//void postImage();
//void emphImage();
//
//void main() {
//	hwnd = GetForegroundWindow();
//	hdc = GetWindowDC(NULL); // windows 10 : hwnd
//
//	char inKey = 0;
//	while (inKey != '9') {
//		printMenu(); // 메뉴 출력
//		inKey = _getch(); // 한 글자 입력 받기
//		system("cls"); // 화면 정리
//
//		switch (inKey) {
//		case '0': loadImage(); break;
//		case '1': saveImage(); break;
//		case '9': break;
//		case 'a':
//		case 'A': equalImage(); break;
//		case 'b':
//		case 'B': addImage(); break;
//		case 'c':
//		case 'C': reverseImage(); break;
//		case 'd':
//		case 'D': binaryImage(); break;
//		case 'e':
//		case 'E': gammaImage(); break;
//		case 'f':
//		case 'F': paraImage(); break;
//		case 'g':
//		case 'G': postImage(); break;
//		case 'h':
//		case 'H': emphImage(); break;
//		}
//	}
//}
//
/////////////////////
//// 함수 정의부
/////////////////////
//
//// 공통 함수
//void printMenu() {
//	puts("\b ## Gray Scale Image Processing (Beta 4) ##");
//	puts("\b--------------------------------------------");
//	puts("\b 0.열기 1.저장 9.종료");
//	puts("\b--------------------------------------------");
//	puts("\b A.원본         B.밝기조절   C.반전 ");
//	puts("\b D.이진화       E.감마보정   F.파라볼라변환");
//	puts("\b G.포스터라이징 H.범위강조");
//	puts("\b--------------------------------------------");
//
//}
//void printImage() {
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			int px = outImage[i][j];
//			SetPixel(hdc, j + 50, i + 250, RGB(px, px, px)); // 뿌릴 좌표, RGB 채널 값이 같으면 Gray Scale
//		}
//		printf("\n");
//	}
//	printf("\n");
//}
//void loadImage() {
//	char fullName[200] = "D:/RAW/Pet_RAW(512x512)/";
//	char tmpName[50];
//	printf("파일명 : "); // cat01, dog05
//	scanf("%s", &tmpName);
//	strcat(fullName, tmpName); // D:/RAW/Pet_RAW(512x512)/cat01
//	strcat(fullName, "_512.raw"); // D:/RAW/Pet_RAW(512x512)/cat01_512.raw
//	strcat(fileName, fullName);
//
//	rfp = fopen(fileName, "rb");
//	fread(inImage, sizeof(unsigned char), height * width, rfp);
//	fclose(rfp);
//	equalImage();
//}
//void saveImage() {
//	char fullName[200] = "D:/RAW/Pet_RAW(512x512)/";
//	char tmpName[50];
//	printf("파일명 : "); // cat01, dog05
//	scanf("%s", &tmpName);
//	strcat(fullName, tmpName); // D:/RAW/Pet_RAW(512x512)/cat01
//	strcat(fullName, "_512.raw"); // D:/RAW/Pet_RAW(512x512)/cat01_512.raw
//	strcat(fileName, fullName);
//
//	wfp = fopen(fileName, "wb");
//	for (int i = 0; i < height; i++)
//		fwrite(outImage[i], sizeof(unsigned char), width, wfp);
//	fclose(wfp);
//	printf("저장 완료");
//	//MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
//}
//int getInValue() {
//	int retValue;
//
//	printf("정수값 : ");
//	scanf("%d", &retValue);
//
//	return retValue;
//}
//double getFlValue() {
//	double retValue;
//
//	printf("실수 또는 정수값 : ");
//	scanf("%lf", &retValue);
//
//	return retValue;
//}
//
//// 영상처리 함수
//void equalImage() {
//	// 동일 영상 알고리즘
//	// 입력 배열 -> 출력 배열
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			outImage[i][j] = inImage[i][j];
//		}
//	}
//	printImage();
//}
//void addImage() {
//	int val = getInValue();
//	// 더하기, 빼기 알고리즘
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (val < 0) {
//				if (inImage[i][j] + val >= 0) // val이 음수면
//					outImage[i][j] = inImage[i][j] + val;
//				else
//					outImage[i][j] = 0;
//			}
//			else {
//				if (inImage[i][j] + val <= 255)
//					outImage[i][j] = inImage[i][j] + val;
//				else
//					outImage[i][j] = 255;
//			}
//		}
//	}
//	printImage();
//}
//void reverseImage() {
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			outImage[i][j] = 255 - inImage[i][j];
//		}
//	}
//	printImage();
//}
//void binaryImage() {
//	int val = 0;
//	printf("0.직접입력 1.평균값 2.중앙값 \n");
//	int option = getInValue();
//	if (option == 0)
//		val = getInValue();
//	else if (option == 1)
//		val = avgCalc();
//	else if (option == 2)
//		val = medCalc();
//
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (inImage[i][j] > val)
//				outImage[i][j] = 255;
//			else
//				outImage[i][j] = 0;
//		}
//	}
//	printImage();
//}
//int avgCalc() {
//	int hap = 0;
//	int result;
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			hap += inImage[i][j];
//		}
//	}
//	result = hap / (height * width);
//	printf("영상의 평균 값: %d\n", result);
//	return result;
//}
//int medCalc() { // 정렬에서 개선
//	int median;
//	int max = 0;
//	unsigned char arr[256] = { 0 };
//
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			arr[inImage[i][j]] += 1;
//		}
//	}
//	for (int i = 0; i < 256; i++) {
//		if (arr[i] > max) {
//			max = arr[i];
//			median = i;
//		}
//	}
//	printf("영상의 중앙 값: %d\n", median);
//	return median;
//}
//void gammaImage() {
//	printf("감마 값을 입력하세요 \n");
//	double gam = getFlValue();
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			outImage[i][j] = pow(((double)inImage[i][j] / 255.0), gam) * 255.0; // pow의 반환 타입은 double
//		}
//	}
//	printImage();
//}
//void paraImage() { // 출력 값 범위 제한 추가 필요?
//	printf("0.CAP(밝은 곳이 입체적으로) 1.CUP(어두운 곳이 입체적으로) \n");
//	int option = getInValue();
//	if (option == 0) {
//		for (int i = 0; i < height; i++) {
//			for (int j = 0; j < width; j++) {
//				outImage[i][j] = 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CAP 파라볼라 : 밝은 곳이 입체적으로 보임
//			}
//		}
//		printImage();
//	}
//	else if (option == 1) {
//		for (int i = 0; i < height; i++) {
//			for (int j = 0; j < width; j++) {
//				outImage[i][j] = 255.0 - 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CUP 파라볼라 : 어두운 곳이 입체적으로 보임
//			}
//		}
//		printImage();
//	}
//}
//void postImage() {
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (inImage[i][j] >= 0 && inImage[i][j] <= 31)
//				outImage[i][j] = 31;
//			else if(inImage[i][j] > 31 && inImage[i][j] <= 63)
//				outImage[i][j] = 63;
//			else if (inImage[i][j] > 63 && inImage[i][j] <= 95)
//				outImage[i][j] = 95;
//			else if (inImage[i][j] > 95 && inImage[i][j] <= 127)
//				outImage[i][j] = 127;
//			else if (inImage[i][j] > 127 && inImage[i][j] <= 159)
//				outImage[i][j] = 159;
//			else if (inImage[i][j] > 159 && inImage[i][j] <= 191)
//				outImage[i][j] = 191;
//			else if (inImage[i][j] > 191 && inImage[i][j] <= 223)
//				outImage[i][j] = 223;
//			else if (inImage[i][j] > 223 && inImage[i][j] <= 255)
//				outImage[i][j] = 255;
//		}
//	}
//	printImage();
//}
//void emphImage() {
//	printf("강조할 픽셀 값의 범위를 입력하세요 \n");
//	printf("시작 픽셀 ");
//	int startVal = getInValue();
//	printf("끝 픽셀 ");
//	int endVal = getInValue();
//
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (inImage[i][j] > startVal && inImage[i][j] < endVal)
//				outImage[i][j] = 255;
//			else
//				outImage[i][j] = inImage[i][j];
//		}
//	}
//	printImage();
//}
//
