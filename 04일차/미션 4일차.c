#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>  // Include stdlib.h for srand() and rand()
#define HEIGHT 7
#define WIDTH 7

// 메모리 준비
unsigned char image[HEIGHT][WIDTH];

// 함수의 선언부
void loadImage() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			image[i][j] = rand() % 256;
		}
	}
}

void printImage() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			printf("%3d ", image[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void reverseImage() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			image[i][j] = 255 - image[i][j];
		}
	}
	printImage();
}

int addImage(int val) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] + val < 256)
				image[i][j] += val;
			else
				image[i][j] = 255;
		}
	}
	printImage();
}

int binaryImage(int th) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] > th) // 임계값 128로 설정
				image[i][j] = 255;
			else
				image[i][j] = 0;
		}
	}
	printImage();
}

void main() {
	srand((unsigned int)time(0));
	// 선택한 영상의 크기 만큼의 메모리 확보 (jolly.raw : 10x10 크기 무압축, 미가공 이미지 파일)
	// 이미지 로드
	loadImage();

	// 원본 출력
	printImage();

	// 반전
	reverseImage();

	// 밝게, 어둡게
	int value;
	printf("밝기 조절 정도 : ");
	scanf("%d", &value);
	addImage(value);

	// 흑백
	int threshold;
	printf("흑백 임계값: ");
	scanf("%d", &threshold);
	binaryImage(threshold);

	// 심화
	// 영상의 평균 값을 출력
	int hap = 0;
	int result;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			hap += image[i][j];
		}
	}
	result = hap / (HEIGHT * WIDTH);
	printf("%d\n", result);

	// 영상의 최대값, 최소값 및  그 위치를 출력
	int max = 0;
	int min = 9999;
	int maxIndexH;
	int maxIndexW;
	int minIndexH;
	int minIndexW;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] >= max) {
				max = image[i][j];
				maxIndexH = i;
				maxIndexW = j;
			}
			if (image[i][j] <= min) {
				min = image[i][j];
				minIndexH = i;
				minIndexW = j;
			}
		}
	}
	printf("max = %d, index=(%d,%d), min = %d, index=(%d,%d) \n", max, maxIndexH, maxIndexW, min, minIndexH, minIndexW);

	// 영상의 중앙값(=중위수=Median)과 위치를 출력
	// 1차원으로 펴기 -> 정렬하기 -> 중간 값 위치 출력

	// 1차원으로 펴기
	unsigned char arr[HEIGHT * WIDTH];
	int index = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			arr[index] = image[i][j];
			// printf("%d ", arr[index]);
			index++;
		}
	}

	// 정렬하기
	for (int i = 0; i < HEIGHT * WIDTH-1; i++) {
		for (int j = 0; j < HEIGHT * WIDTH - i-1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	// 정렬 결과 출력
	for (int i = 0; i < HEIGHT * WIDTH; i++)
		printf("%d ", arr[i]);
	printf("\n");

	// 중간 값과 위치 출력
	int median = arr[(HEIGHT * WIDTH) / 2];
	int medianIndexH;
	int medianIndexW;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] == median) {
				medianIndexH = i;
				medianIndexW = j;
			}
		}
	}
	printf("median = %d, index=(%d,%d)", median, medianIndexH, medianIndexW);
	// 영상에서 최빈값(가장 많이 출현한 값)을 출력
	// 1차원으로 펴기 -> 영상 크기와 동일한 배열 생성(빈도 수 저장) -> 빈도 세기 -> 최대 픽셀 값과 위치 출력
	unsigned char arr2[HEIGHT * WIDTH];
	int index2 = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			arr2[index2] = image[i][j];
			// printf("%d ", arr2[index]);
			index2++;
		}
	}
	// 영상 크기와 동일한 배열 생성
	unsigned char freq[HEIGHT * WIDTH] = { 1 };
	// 빈도 세기
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		for (int j = i + 1; j < HEIGHT * WIDTH; j++) {
			if (arr2[i] == arr2[j])
				freq[i] += 1;
		}
	}
	// 최대 픽셀 값 구하기
	int max2 = 0;
	int maxFreq;
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		if (freq[i] >= max2) {
			max2 = freq[i];
			maxFreq = arr2[i];
		}
	}
	// 위치 찾기
	int maxFreqIndexH = -1;
	int maxFreqIndexW = -1;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (image[i][j] == maxFreq) {
				maxFreqIndexH = i;
				maxFreqIndexW = j;
				break;
			}
		}
		if (maxFreqIndexH != -1) // 처음 발견한 최대 빈도만 사용
			break;
	}
	printf("\nmax freq= %d, index=(%d,%d)", maxFreq, maxFreqIndexH, maxFreqIndexW);

}