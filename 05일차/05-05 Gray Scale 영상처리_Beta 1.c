//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <stdlib.h>
//
///////////////
//// 전역 변수부
///////////////
//FILE* rfp;
//char fileName[200] = "D:/RAW/LENNA512.raw";
//#define height 512
//#define width 512
//// 메모리 확보
//unsigned char inImage[height][width];
//unsigned char outImage[height][width];
//
///////////////
//// 함수 선언부
///////////////
//void loadImage(); int getInValue(); void printImage();
//
//void equalImage(); void addImage(int);
//
//
//void main() {
//	loadImage();
//	// 영상처리 알고리즘 구현
//	// 밝기 조절
//	int value = getInValue();
//	addImage(value);
//
//}
//
////////////////
//// 함수 정의부
////////////////
//
//// 공통 함수
//void printImage() {
//	for (int i = height/2-5; i < height /2+5; i++) {
//		for (int j = width / 2 - 5; j < width / 2 + 5; j++) {
//			printf("%3d ", outImage[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}
//void loadImage() {
//	rfp = fopen(fileName, "rb");
//	fread(inImage, sizeof(unsigned char), height * width, rfp);
//
//	fclose(rfp);
//	equalImage();
//}
//int getInValue() {
//	int retValue;
//
//	printf("정수값 : ");
//	scanf("%d", &retValue);
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
//
//void addImage(int val) {
//	// 다하기, 빼기 알고리즘
//	for (int i = 0; i < height; i++) {
//		for (int j = 0; j < width; j++) {
//			if (inImage[i][j]+ val < 255)
//				outImage[i][j] = inImage[i][j] + val;
//			else
//				outImage[i][j] = 255;
//		}
//	}
//	printImage();
//}