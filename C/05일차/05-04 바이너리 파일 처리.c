#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#define height 512
#define width 512

void main() {
	FILE* rfp;

	char fileName[200] = "D:/RAW/LENNA512.raw";

	unsigned char image[height][width];

	rfp = fopen(fileName, "rb");

	fread(image, 1, height * width, rfp);

	printf("%d", image[511][511]);

	fclose(rfp);
}