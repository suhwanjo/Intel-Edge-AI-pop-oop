//#define _CRT_SECURE_NO_WARNINGS
//#include <stdbool.h>
//#include <stdio.h>
//#include <time.h>
//#include <stdlib.h>  // Include stdlib.h for srand() and rand()
//#define HEIGHT 10
//#define WIDTH 10
//
//void main() {
//	srand((unsigned int)time(0));
//	// 선택한 영상의 크기 만큼의 메모리 확보 (jolly.raw : 10x10 크기 무압축, 미가공 이미지 파일)
//
//	// 메모리 할당
//	unsigned char image[HEIGHT][WIDTH];
//
//	// 이미지 파일 -> 2차월 배열로 로딩(Loading) Disk -> RAM
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			image[i][j] = rand() % 256;
//		}
//	}
//	// 원본 이미지 출력
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			printf("%3d ", image[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//
//	// 영상 처리 (Image Processing)
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (image[i][j]-50 > 0)
//				image[i][j] -= 50;
//			else
//				image[i][j] = 0;
//		}
//	}
//
//	// 결과 이미지 출력
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			printf("%3d ", image[i][j]);
//		}
//		printf("\n");
//	}
//}