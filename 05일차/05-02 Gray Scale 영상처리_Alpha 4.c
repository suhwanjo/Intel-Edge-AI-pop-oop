//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <stdlib.h>
//
//// 선택한 영상의 가로x세로
//#define HEIGHT 5
//#define WIDTH 5
//
//// 메모리 준비
//unsigned char image[HEIGHT][WIDTH];
//
//// 함수의 선언부
//void loadImage() {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			image[i][j] = rand() % 256;
//		}
//	}
//}
//
//void printImage() {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			printf("%3d ", image[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}
//
//void reverseImage() {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			image[i][j] = 255 - image[i][j];
//		}
//	}
//	printImage();
//}
//
//int addImage(int val) {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (image[i][j] + val < 256)
//				image[i][j] += val;
//			else
//				image[i][j] = 255;
//		}
//	}
//	printImage();
//}
//
//
//
//void main() {
//	// 랜덤 초기화
//	srand((unsigned int)time(0));
//
//	// 이미지 파일 -> 2차원 배열로 Loading
//	loadImage();
//
//	//원본 출력
//	printImage();
//
//	// 영상 반전 처리
//	reverseImage();
//
//	// 영상 밝게 처리
//	int value;
//	printf("얼마나 밝게 할까요? : ");
//	scanf("%d", &value);
//	addImage(value);
//}
//
//// 함수의 정의부