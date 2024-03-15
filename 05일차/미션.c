#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/////////////
// 전역 변수부
/////////////
FILE* rfp;
char fileName[200] = "D:/RAW/LENNA512.raw";
#define height 512
#define width 512
// 메모리 확보
unsigned char inImage[height][width];
unsigned char outImage[height][width];

/////////////
// 함수 선언부
/////////////
void loadImage(); 
int getInValue(); double getFlValue(); 
void printImage();

void equalImage(); 
void addImage(int);
void reverseImage();
void binaryImage(int); int medCalc(); int avgCalc();
void gammaImage();
void paraCAPImage(); void paraCUPImage();

void main() {
	// 영상 로딩
	loadImage();
	// 영상처리 알고리즘 구현 
	// 밝기 조절
	int value = getInValue();
	addImage(value);

	// 반전
	reverseImage();

	// 흑백(128)
	binaryImage(128);

	// 흑백(평균)
	int average = avgCalc();
	binaryImage(average);

	// 흑백(중앙)
	int median = medCalc();
	binaryImage(median);

	// 감마 보정 : 빛의 변화를 비선형적으로 변화시킨 것
	double gamValue = getFlValue();
	gammaImage(gamValue);
	
	// 파라볼라 : 2차원 곡선그래프를 통한 변환 처리법
	paraCAPImage();
	paraCUPImage();
}

//////////////
// 함수 정의부
//////////////

// 공통 함수
void printImage() {
	for (int i = height / 2 - 5; i < height / 2 + 5; i++) {
		for (int j = width / 2 - 5; j < width / 2 + 5; j++) {
			printf("%3d ", outImage[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void loadImage() {
	rfp = fopen(fileName, "rb");
	fread(inImage, sizeof(unsigned char), height * width, rfp);

	fclose(rfp);
	equalImage();
}
int getInValue() {
	int retValue;

	printf("정수값 : ");
	scanf("%d", &retValue);

	return retValue;
}
double getFlValue() {
	double retValue;

	printf("실수 또는 정수값 : ");
	scanf("%lf", &retValue);

	return retValue;
}

// 영상처리 함수
void equalImage() {
	// 동일 영상 알고리즘
	// 입력 배열 -> 출력 배열
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = inImage[i][j];
		}
	}
	printImage();
}
void addImage(int val) {
	// 다하기, 빼기 알고리즘
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (val < 0) {
				if (inImage[i][j] + val >= 0) // val이 음수면
					outImage[i][j] = inImage[i][j] + val;
				else
					outImage[i][j] = 0;
			}
			else {
				if (inImage[i][j] + val <= 255)
					outImage[i][j] = inImage[i][j] + val;
				else
					outImage[i][j] = 255;
			}
		}
	}
	printImage();
}
void reverseImage() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = 255 - inImage[i][j];
		}
	}
	printImage();
}
void binaryImage(int val) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (inImage[i][j] > val) 
				outImage[i][j] = 255;
			else
				outImage[i][j] = 0;
		}
	}
	printImage();
}
int avgCalc() {
	int hap = 0;
	int result;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			hap += inImage[i][j];
		}
	}
	result = hap / (height * width);
	printf("영상의 평균 값: %d\n", result);
	return result;
}
int medCalc() { // 정렬에서 개선
	int median;
	int max = 0;
	unsigned char arr[256] = { 0 };

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			arr[inImage[i][j]] += 1;
		}
	}
	for (int i = 0; i < 256; i++) {
		if (arr[i] > max) {
			max = arr[i];
			median = i;
		}
	}
	printf("영상의 중앙 값: %d\n", median);
	return median;
}
void gammaImage(double gam) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = pow(((double)inImage[i][j] / 255.0), gam) * 255.0; // pow의 반환 타입은 double
		}
	}
	printImage();
}
void paraCAPImage() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CAP 파라볼라 : 밝은 곳이 입체적으로 보임
		}
	}
	printImage();
}
void paraCUPImage() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImage[i][j] = 255.0-255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CUP 파라볼라 : 어두운 곳이 입체적으로 보임
		}
	}
	printImage();
}