#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <Windows.h> // GUI 지원 기능
#define PI 3.141592

//////////////////////
// 전역 변수부
//////////////////////

// 윈도우 API 프로그래밍
HWND hwnd; // 왼도우 화면(외부, 물리적)
HDC hdc; // 윈도우 화면(내부, 논리적)

FILE* rfp, * wfp;
char fileName[200];
int inH, inW, outH, outW;
int width;
// 메모리 확보
//unsigned char inImage[height][width];
//unsigned char outImage[height][width];
unsigned char** inImage, ** outImage = NULL;

/////////////////////
// 함수 선언부
/////////////////////
void loadImage(); void saveImage();
void freeInputMemory(); void freeOutputMemory(); void mallocInputMemory(); void mallocOutputMemory(); double** mallocDoubleMemory(); void freeDoubleMemory(double**, int);
int getInValue(); double getFlValue();
void printImage(); void printMenu();

void equalImage();
void addImage(); void reverseImage(); void binaryImage(); int medCalc(); int avgCalc();
void gammaImage(); void paraImage(); void postImage(); void emphImage();
void scaleImage(); void rotatImage(); void moveImage(); void mirrorImage();
void histoStretch(); void histoEqual();
void emboss();
void edgeLOG(); void edgeBetterLOG(); void edgeDOG();

void main() {
    hwnd = GetForegroundWindow();
    hdc = GetWindowDC(NULL); // windows 10 : hwnd

    char inKey = 0;
    while (inKey != '9') {
        printMenu(); // 메뉴 출력
        inKey = _getch(); // 한 글자 입력 받기
        system("cls"); // 화면 정리

        switch (inKey) {
        case '0': loadImage(); break;
        case '1': saveImage(); break;
        case '9': break;
        case 'a':
        case 'A': equalImage(); break;
        case 'b':
        case 'B': addImage(); break; // 밝기 조절
        case 'c':
        case 'C': reverseImage(); break; // 반전
        case 'd':
        case 'D': binaryImage(); break; // 이진화
        case 'e':
        case 'E': gammaImage(); break; // 감마 보정
        case 'f':
        case 'F': paraImage(); break; // 파라볼릭 변환
        case 'g':
        case 'G': postImage(); break; // 포스터라이징
        case 'h':
        case 'H': emphImage(); break; // 범위 강조
        case 'i':
        case 'I': scaleImage(); break; // 크기 조절
        case 'j':
        case 'J': rotatImage(); break; // 회전
        case 'k':
        case 'K': moveImage(); break; // 이동
        case 'l':
        case 'L': mirrorImage(); break; // 미러링(대칭)
        case 'm':
        case 'M': histoStretch(); break; // 히스토그램 스트레칭
        case 'n':
        case 'N': histoEqual(); break; // 히스토그램 평활화
        case 'o':
        case 'O': emboss(); break; // 엠보싱/스무딩/샤프닝
        case 'p':
        case 'P': edgeLOG(); break; // 에지 검출(LOG)
        case 'q': 
        case 'Q': edgeBetterLOG(); break; // 에지 검출(LOG계산량개선)
        case 'r':
        case 'R': edgeDOG(); break;
        }
    }
    freeInputMemory();
    freeOutputMemory();
}

///////////////////
// 함수 정의부
///////////////////

// 공통 함수
void printMenu() {
    puts(" ----------------------------------------------------------------------");
    puts("|  ## Gray Scale Image Processing (GA 1) ##                            |");
    puts("|----------------------------------------------------------------------|");
    puts("|  0. 열기     1. 저장      9. 종료                                    |");
    puts("|----------------------------------------------------------------------|");
    puts("|  A. 원본             B. 밝기조절      C. 반전                        |");
    puts("|  D. 이진화           E. 감마보정      F. 파라볼릭변환                |");
    puts("|  G. 포스터라이징     H. 범위강조      I. 확대/축소                   |");
    puts("|  J. 회전             K. 이동          L. 미러링(대칭)                |");
    puts("|  M. 명암대비스트레칭 N. 평활화        O. 엠보싱/블러링/스무딩/샤프닝 |");
    puts("|  P. 에지검출(LOG)    Q. LOG계산량개선 R. 에지검출(DOG)               |");
    puts(" ----------------------------------------------------------------------");
}
void printImage() {
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            int px = outImage[i][j];
            SetPixel(hdc, j + 500, i + 500, RGB(px, px, px)); // 뿌릴 좌표, RGB 채널 값이 같으면 Gray Scale
        }
    }
    //system("cls");
}
void loadImage() { // 하나 열고 또 열면 오류 남
    fileName[0] = '\0'; // 여러번의 파일 열기를 위한 전역 변수 초기화

    //char fullName[200] = "C:/Users/IOT/Desktop/Project1/Intel-Edge-AI-SW-Academy/RAW/";
    char fullName[200] = "C:/Users/shjo/Desktop/Intel-Edge-AI-SW-Academy/RAW/";
    char tmpName[50];
    printf("파일명 : "); // flower512, LENA256
    scanf("%s", &tmpName);
    strcat(fullName, tmpName); // D:/RAW/Pet_RAW(512x512)/cat01
    strcat(fullName, ".raw"); // D:/RAW/Pet_RAW(512x512)/cat01.raw
    strcat(fileName, fullName);

    // (중요!) 이미지의 폭과 높이를 결정
    rfp = fopen(fileName, "rb");
    if (rfp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    fseek(rfp, 0L, SEEK_END); // 파일의 끝으로 이동
    long long fsize = ftell(rfp); // 나 어디쯤이지? 512?
    fclose(rfp);
    // 메모리 해제
    freeInputMemory();
    // 폭=높이 크기 구하기
    inH = inW = (int)sqrt(fsize);
    // 메모리 할당
    mallocInputMemory();

    // 파일에서 메모리로 읽기
    rfp = fopen(fileName, "rb");
    if (rfp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    for (int i = 0; i < inH; i++) {
        fread(inImage[i], sizeof(unsigned char), inH, rfp);
    }
    fclose(rfp);

    equalImage();
}
void saveImage() {
    if (inImage == NULL)
        return;
    fileName[0] = '\0';
    char fullName[200] = "C:/Users/IOT/Desktop/Project1/Intel-Edge-AI-SW-Academy/RAW/";
    char tmpName[50];
    printf("파일명 : ");
    scanf("%s", &tmpName);
    strcat(fullName, tmpName);
    strcat(fullName, ".raw");
    strcat(fileName, fullName);

    wfp = fopen(fileName, "wb");
    //printf("%s", fileName);
    if (wfp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }
    for (int i = 0; i < outH; i++)
        fwrite(outImage[i], sizeof(unsigned char), outW, wfp);
    fclose(wfp);
    printf("저장 완료\n");
    //MessageBox(hwnd, L"저장 완료", L"저장 창", NULL);
}
int getInValue() {
    if (inImage == NULL)
        return 0;
    int retValue = 0;

    while (1) {
        printf("정수값 : ");
        if (scanf("%d", &retValue) != 1) {
            // 입력 오류 처리
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            // 입력 버퍼를 비워 오류 발생 후의 입력을 올바르게 처리
            while (getchar() != '\n');
        }
        else
            break;

    }
    return retValue;

}
double getFlValue() {
    if (inImage == NULL)
        return 0.0;
    double retValue = 0.0;

    while (1) {
        printf("실수 또는 정수값 : ");
        if (scanf("%lf", &retValue) != 1) {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            while (getchar() != '\n');
        }
        else
            break;
    }
    return retValue;
}
void freeInputMemory() {
    if (inImage == NULL)
        return;
    for (int i = 0; i < inH; i++) {
        free(inImage[i]);
    }
    free(inImage);
    inImage = NULL;
}
void freeOutputMemory() {
    if (inImage == NULL)
        return;
    for (int i = 0; i < outH; i++) {
        free(outImage[i]);
    }
    free(outImage);
    outImage = NULL;
}
void mallocInputMemory() {
    inImage = (unsigned char**)malloc(sizeof(unsigned char*) * inH);
    for (int i = 0; i < inH; i++) {
        inImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * inW);
    }
}
void mallocOutputMemory() {
    outImage = (unsigned char**)malloc(sizeof(unsigned char*) * outH);
    for (int i = 0; i < outH; i++) {
        outImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);
    }
}
double** mallocDoubleMemory(int h, int w) {
    double** retMemory = (double**)malloc(sizeof(double*) * h);
    for (int i = 0; i < h; i++) {
        retMemory[i] = (double*)malloc(sizeof(double) * w);
    }

    return retMemory;
}
void freeDoubleMemory(double** memory, int h) {
    if (memory == NULL)
        return;
    for (int i = 0; i < h; i++) {
        free(memory[i]);
    }
    free(memory);
    memory = NULL;
}
// 영상처리 함수
// 점 변환
void equalImage() { // 동일 영상 알고리즘
    // 입력 배열 -> 출력 배열

    // 메모리 해제
    freeOutputMemory();
    // (중요!) 출력 이미지의 크기 결정 -> 알고리즘에 의존
    outH = inH;
    outW = inW;
    //  메모리 할당
    mallocOutputMemory();

    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            outImage[i][j] = inImage[i][j];
        }
    }
    printImage();
}
void addImage() { // 밝기조절
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    printf("밝기 조절 정도를 입력하세요.(-:어둡게, +:밝게)\n");
    int val = getInValue();
    // 더하기, 빼기 알고리즘
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
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
void reverseImage() { // 반전
    if (inImage == NULL)
        return;
    freeOutputMemory();
    // (중요!) 출력 이미지의 크기 결정 -> 알고리즘에 의존
    outH = inH;
    outW = inW;
    //  메모리 할당
    mallocOutputMemory();

    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            outImage[i][j] = 255 - inImage[i][j];
        }
    }
    printImage();
}
void binaryImage() { // 이진화
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    int val = 0;
    int option;
    while (1) {
        printf("임계값 설정 방법을 선택하세요. \n");
        printf("0.직접입력 1.평균값 2.중앙값 \n");
        option = getInValue();
        if (option == 0) {
            val = getInValue();
            break;
        }
        else if (option == 1) {
            val = avgCalc();
            break;
        }
        else if (option == 2) {
            val = medCalc();
            break;
        }
        else
            printf("잘못된 입력입니다. 다시 시도하세요.(0,1,2)\n");
    }

    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            if (inImage[i][j] > val)
                outImage[i][j] = 255;
            else
                outImage[i][j] = 0;
        }
    }
    printImage();
}
int avgCalc() {
    if (inImage == NULL)
        return 0;
    int hap = 0;
    int result;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            hap += inImage[i][j];
        }
    }
    result = hap / (inH * inW);
    printf("영상의 평균 값: %d\n", result);
    return result;
}
int medCalc() { // 정렬에서 개선
    if (inImage == NULL)
        return 0;
    int count = 0;
    int median = 0;
    int arr[256] = { 0 };

    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            arr[inImage[i][j]] += 1;
        }
    }
    for (int i = 0; i < 256; i++) {
        count += arr[i];
        if (count >= (inH * inW / 2)) {
            median = i;
            break;
        }
    }
    printf("영상의 중앙 값: %d\n", median);
    return median;
}
void gammaImage() { // 감마보정
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();
    double gam = 0;
    while (1) {
        printf("감마(Gamma) 값을 소수 형태로 입력하세요.(0.5~2.5) \n");
        gam = getFlValue();
        if (gam >= 0.5 && gam < 2.5) {
            for (int i = 0; i < inH; i++) {
                for (int j = 0; j < inW; j++) {
                    outImage[i][j] = pow(((double)inImage[i][j] / 255.0), gam) * 255.0; // pow의 반환 타입은 double
                }
            }
            break;
        }
        else
            printf("잘못된 입력입니다. 다시 시도하세요.(0.5~2.5)\n");
    }
    printImage();
}
void paraImage() { // 파라볼릭변환
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();
    int option = 0;
    while (1) {
        printf("변환 방법을 선택하세요. \n");
        printf("0.CAP(밝은 곳이 입체적으로) 1.CUP(어두운 곳이 입체적으로) \n");
        option = getInValue();
        if (option == 0) {
            for (int i = 0; i < inH; i++) {
                for (int j = 0; j < inW; j++) {
                    outImage[i][j] = 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CAP 파라볼라 : 밝은 곳이 입체적으로 보임
                }
            }
            break;
        }
        else if (option == 1) {
            for (int i = 0; i < inH; i++) {
                for (int j = 0; j < inW; j++) {
                    outImage[i][j] = 255.0 - 255.0 * pow(((double)inImage[i][j] / 127.0 - 1.0), 2.0); // CUP 파라볼라 : 어두운 곳이 입체적으로 보임
                }
            }
            break;
        }
        else
            printf("잘못된 입력입니다. 다시 시도하세요.(0,1)\n");
    }
    printImage();
}
void postImage() { // 포스터라이징
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            if (inImage[i][j] >= 0 && inImage[i][j] <= 31)
                outImage[i][j] = 31;
            else if (inImage[i][j] > 31 && inImage[i][j] <= 63)
                outImage[i][j] = 63;
            else if (inImage[i][j] > 63 && inImage[i][j] <= 95)
                outImage[i][j] = 95;
            else if (inImage[i][j] > 95 && inImage[i][j] <= 127)
                outImage[i][j] = 127;
            else if (inImage[i][j] > 127 && inImage[i][j] <= 159)
                outImage[i][j] = 159;
            else if (inImage[i][j] > 159 && inImage[i][j] <= 191)
                outImage[i][j] = 191;
            else if (inImage[i][j] > 191 && inImage[i][j] <= 223)
                outImage[i][j] = 223;
            else if (inImage[i][j] > 223 && inImage[i][j] <= 255)
                outImage[i][j] = 255;
        }
    }
    printImage();
}
void emphImage() { // 범위강조
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();
    int startVal, endVal = 0;
    while (1) {
        printf("강조할 픽셀 값의 범위를 입력하세요.(0~255) \n");
        printf("시작 픽셀 ");
        startVal = getInValue();
        printf("끝 픽셀 ");
        endVal = getInValue();
        if ((startVal >= 0 && startVal <= 255) && (endVal >= 0 && endVal <= 255))
            break;
        else
            printf("잘못된 입력입니다. 다시 시도하세요.(0~255)\n");
    }

    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            if ((inImage[i][j] > startVal && inImage[i][j] < endVal) || (inImage[i][j] < startVal && inImage[i][j] > endVal))
                outImage[i][j] = 255;
            else
                outImage[i][j] = inImage[i][j];
        }
    }
    printImage();
}
void histoStretch() { // 히스토그램(대비) 스트레칭
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    // new = (old - low) / (high - low) * 255
    int high = inImage[0][0]; // 최대, 최소 구할 때 처음 값으로 설정
    int low = inImage[0][0];

    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            if (inImage[i][j] < low)
                low = inImage[i][j];
            if (inImage[i][j] > high)
                high = inImage[i][j];
        }
    }
    // high -= 50;
    // low += 50;  
    //
    int old, new;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            // End-In 탐색 : 최대 최소값 사이를 좁혀 스트레칭 효과를 극대화
            // new = (old - low) / (high - low) * 255
            old = inImage[i][j];
            new = (int)((old - low) / (double)(high - low) * 255.0);
            if (new > 255)
                new = 255;
            if (new < 0)
                new = 0;
            outImage[i][j] = new;
        }
    }
    printImage();
}
void histoEqual() { // 히스토그램 평활화
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    
    int histo[256] = { 0, };
    for (int i = 0; i < inH; i++)
        for (int j = 0; j < inW; j++)
            // 1단계 : 빈도수 세기(=히스토그램) histo[256]
            histo[inImage[i][j]]++;
    // 2단계 : 누적히스토그램 생성
    int sumHisto[256] = { 0, };
    sumHisto[0] = histo[0];
    for (int i = 1; i < 256; i++)
        // 2단계 : 누적히스토그램 생성
        sumHisto[i] = sumHisto[i - 1] + histo[i];
    // 3단계 : 정규화된 히스토그램 생성  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
    double normalHisto[256] = { 1.0, };
    for (int i = 0; i < 256; i++) {
        // 3단계 : 정규화된 히스토그램 생성
        normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;
    }
    // 4단계 : inImage를 정규화된 값으로 치환
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            // 4단계 : inImage를 정규화된 값으로 치환
            outImage[i][j] = (unsigned char)normalHisto[inImage[i][j]];
        }
    }
    printImage();
}
// 기하 변환
void scaleImage() { // 확대/축소
    if (inImage == NULL)
        return;
    int scale = 1;
    printf("크기 조절 정도를 입력하세요.(-:축소, +:확대)\n");

    scale = getInValue();

    if (scale < 0) {
        scale = -scale;
        freeOutputMemory();
        outH = (int)(inH / scale);
        outW = (int)(inW / scale);
        mallocOutputMemory();

        //for (int i = 0; i < inH; i++) { // 하나의 값으로 축소
        //    for (int j = 0; j < inW; j++) {
        //        outImage[i / scale][j / scale] = inImage[i][j];
        //    }
        //}

        // 영역 처리 구현을 너무 복잡하게 함 -> 계산량 증가, 가독성 감소
        //int sum = 0;
        //int avg;
        //for (int i = 0; i < outH; i++) { // 평균값으로 축소
        //    for (int j = 0; j < outW; j++) {
        //        sum = 0;
        //        for (int k = i * scale; k < ((i + 1) * scale); k++) {     // for(int k = 0; k < scale; k++)
        //            for (int q = j * scale; q < ((j + 1) * scale); q++) {      // for(int q = 0; q < scale; q++)
        //                sum += inImage[k][q];                                       // sum += inImage[i+k][j+q]; 로 대체 가능
        //            }
        //        }
        //        avg = (double)sum / (scale * scale);
        //        outImage[i][j] = avg;
        //    }
        //}

        int count, median;
        for (int i = 0; i < outH; i++) { // 중간값으로 축소
            for (int j = 0; j < outW; j++) {
                int histo[256] = { 0, };
                for (int k = i * scale; k < ((i + 1) * scale); k++) {
                    for (int q = j * scale; q < ((j + 1) * scale); q++) {
                        // 히스토그램 계산
                        histo[inImage[k][q]] += 1;
                    }
                }
                count = 0;
                for (int a = 0; a < 256; a++) {
                    count += histo[a];
                    // 중간 값 계산
                    if (count >= (scale * scale) / 2) {
                        median = a;
                        break;
                    }
                }
                outImage[i][j] = median;
            }
        }

        //int max;
        //for (int i = 0; i < outH; i++) { // 최대값으로 축소
        //    for (int j = 0; j < outW; j++) {
        //        int histo[256] = { 0, };
        //        for (int k = i * scale; k < ((i + 1) * scale); k++) {
        //            for (int q = j * scale; q < ((j + 1) * scale); q++) {
        //                histo[inImage[k][q]] += 1;
        //            }
        //        }
        //        max = 0;
        //        for (int a = 0; a < 256; a++) {
        //            if (histo[a] > max)
        //                max = a;
        //        }  
        //        outImage[i][j] = max;
        //    }
        //}
        printImage();
    }
    else if (scale > 0) {
        freeOutputMemory();
        outH = (int)inH * scale;
        outW = (int)inW * scale;
        mallocOutputMemory();

        //for (int i = 0; i < inH; i++) { // 보간법 적용 가능 == 포워딩
        //   for (int j = 0; j < inW; j++) {
        //      outImage[i*2][j*2] = inImage[i][j];
        //   }
        //}

        for (int i = 0; i < outH; i++) { // 인접 픽셀 보간법 == 백워딩
            for (int k = 0; k < outW; k++) {
                outImage[i][k] = inImage[(int)(i / scale)][(int)(k / scale)];
            }
        }
    else {
        outH = inH;
        outW = inW;
        for (int i = 0; i < outH; i++) {
            for (int k = 0; k < outW; k++) {
                outImage[i][k] = inImage[i][k];
            }
        }
    }
        // 양선형 보간 -> 실패
        // 주변 4점 찾기
        // 보간

        printImage();
    }
}
void rotatImage() { // 회전
    if (inImage == NULL)
        return;

    int degree = getInValue();
    double tmp_radian = degree % 90 * PI / 180.0;
    double tmp_radian90 = (90 - degree % 90) * PI / 180.0;
    freeOutputMemory();
    // 회전 각도에 따라 출력 영상을 확대
    outH = (int)(inH * cos(tmp_radian90) + inW * cos(tmp_radian));
    outW = (int)(inW * cos(tmp_radian) + inH * cos(tmp_radian90));
    double angle = degree * PI / 180.0;
    mallocOutputMemory();
    //xd = cos(xs) - sin(ys)
    //yd = sin(xs) + cos(ys)
    //for (int i = 0; i < inH; i++) { // 기준, 업스케일링에 의한 빈 값 문제
    //   for (int j = 0; j < inW; j++) {
    //      int xd = (int)(cos(radian) * i - sin(radian) * j);
    //      int yd = (int)(sin(radian) * i + cos(radian) * j);
    //      if((0<=xd && xd<outH) && (0<=yd && yd<outW))
    //         outImage[xd][yd] = inImage[i][j];
    //   }
    //}
    // 여전히 잘리는 문제
    int dx = (outW - inW) / 2;
    int dy = (outH - inH) / 2;
    unsigned char** tmpImage = (unsigned char**)malloc(sizeof(unsigned char*)*outH);
    for (int i = 0; i < outH; i++) {
        tmpImage[i] = (unsigned char*)malloc(sizeof(unsigned char) * outW);
    }
    for (int i = 0; i < inH; i++)
        for (int j = 0; j < inW; j++)
            // 출력 크기의 임시 영상, 중앙에 (0,0) 오도록 이동
            tmpImage[i + dx][j + dy] = inImage[i][j];

    int cx = outH / 2;
    int cy = outW / 2;
    int xs, ys;
    for (int i = 0; i < outH; i++) { 
        for (int j = 0; j < outW; j++) {
            int xd = i;
            int yd = j;
            // 백워딩 + 중앙으로 이동
            xs = (int)(cos(angle) * (xd - cx) + sin(angle) * (yd - cy)) + cx;
            ys = (int)(-sin(angle) * (xd - cx) + cos(angle) * (yd - cy)) + cy;
            if ((0 <= xs && xs < outH) && (0 <= ys && ys < outW))
                outImage[xd][yd] = tmpImage[xs][ys];
        }
    }

    // 임시 영상 메모리 해제
    //for (int i = 0; i < outH; i++) {
    //    free(tmpImage[i]);
    //}
    //free(tmpImage);

    printImage();
}
void moveImage() { // 이동
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    int move = getInValue();
    if (move >= 0) { // 우측 하단으로 이동
        for (int i = 0; i < outH - move; i++) {
            for (int j = 0; j < outW - move; j++) {
                // 우측 하단
                if ((0 <= i && i < outH) && (0 <= j && j < outW))
                    outImage[i + move][j + move] = inImage[i][j];
            }
        }
    }
    else // 좌측 상단으로 이동
        for (int i = 0; i < outH; i++) {
            for (int j = 0; j < outW; j++) {
                // 좌측 상단
                if ((0 - move <= i && i < outH) && (0 - move <= j && j < outW))
                    outImage[i + move][j + move] = inImage[i][j];
            }
        }
    printImage();
}
void mirrorImage() { // 미러링(대칭)
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();
    int mirror;
    while (1) {
        printf("대칭 방식을 선택하세요.\n");
        printf("0.상하, 1.좌우\n");
        mirror = getInValue();
        if (mirror == 1) {
            for (int i = 0; i < outH; i++) {
                for (int j = 0; j < outW; j++) {
                    // 좌-우
                    outImage[i][-(j - outW + 1)] = inImage[i][j];
                }
            }
            break;
        }
        else if (mirror == 0) {
            for (int i = 0; i < outH; i++) {
                for (int j = 0; j < outW; j++) {
                    // 상-하
                    outImage[-(i - outH + 1)][j] = inImage[i][j];
                }
            }
            break;
        }
        else
            printf("잘못된 입력입니다. 다시 시도하세요.(0~1)\n");
    }
    printImage();
}
// 영역 변환
void emboss() { // 엠보싱/블러링/샤프닝
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    int type, size;
    while (1) {
        printf("효과를 적용할 정도(마스크 크기)를 입력하세요.(홀수만 가능)\n");
        size = getInValue();
        if (size % 2 == 0)
            printf("잘못된 입력입니다. 다시 시도하세요.(홀수)\n");
        else
            break;
    }

    int center = size / 2;
    double** mask = mallocDoubleMemory(size, size);
    while (1) {
        printf("영역 처리 타입을 선택하세요.(0.엠보싱 1.블러링 2.스무딩 3.샤프닝)\n");
        type = getInValue();
        if (type == 0) { // 엠보싱 : 처음에 -1,  끝에 1
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    // 엠보싱 마스크 생성
                    if (i == 0 && j == 0)
                        mask[i][j] = -1.0;
                    else if (i == size - 1 && j == size - 1)
                        mask[i][j] = 1.0;
                    else
                        mask[i][j] = 0.0;
                }
            }
            break;
        }
        else if (type == 1) { // 블러링 : size * size 로 나눔
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    // 블러링 마스크 생성
                    mask[i][j] = 1 / (double)(size * size);
                }
            }
            break;
        }
        else if (type == 2) { // 스무딩 : exp(-(x * x) / (2 * sigma * sigma)) / (sigma * sqrt(2 * PI)) -> 시그마 입력 받고 x(중심으로부터의 거리) 구하기 
            double sigma;
            while (1) {
                printf("적용할 스무딩 정도(Sigma)를 입력하세요.(0.5~5.0)\n");
                sigma = getFlValue();
                if ((sigma < 0.5) || (sigma > 5.0))
                    printf("잘못된 입력입니다. 다시 시도하세요.(0.5~5.0)\n");
                else
                    break;
            }
            double gaussian;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    // 가우시안 마스크 생성
                    double x = sqrt((pow((i - center), 2)+ pow((j - center), 2)));
                    gaussian = exp(-(x * x) / (2.0 * sigma * sigma)) / (sigma * sqrt(2.0 * PI));
                    mask[i][j] = gaussian;
                }
            }
            break;
        }
        else if (type == 3) { // 샤프닝 : 주변은 -1, 중앙은 배열 크기
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    // 샤프닝 마스크 생성
                    if (i == center && j == center)
                        mask[i][j] = (double)size * size;
                    else
                        mask[i][j] = -1.0;
                }
            }
            break;
        }
        else
            printf("잘못된 입력입니다. 다시 시도하세요.(0~3)\n");
    }
    // 임시 이미지 할당(실수) : 패딩을 위한
    double** tmpInImage = mallocDoubleMemory(inH + (size - 1), inW + (size - 1)); // 필터 크기에 따라 패딩 변화
    double** tmpOutImage = mallocDoubleMemory(outH, outW);
    // 임시 이미지 초기화(127)
    for (int i = 0; i < inH + (size - 1); i++) {
        for (int j = 0; j < inW + (size - 1); j++) {
            tmpInImage[i][j] = 127;
        }
    }
    // 입력 이미지 -> 임시 이미지에 넣기(패딩 완료)
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImage[i + 1][j + 1] = inImage[i][j];
        }
    }
    // 컨볼루션 연산
    double sum;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            sum = 0;
            for (int k = 0; k < size; k++) {
                for (int q = 0; q < size; q++) {
                    sum += tmpInImage[i + k][j + q] * mask[k][q];
                }
            }
            tmpOutImage[i][j] = sum;
        }
    }
    // 마스크 값의 합에 따라 후처리 (엠보싱만)
    if (type == 0) {
        for (int i = 0; i < outH; i++) {
            for (int j = 0; j < outW; j++) {
                tmpOutImage[i][j] += 127.0;
            }
        }
    }
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            //임시 출력 영상 -> 출력 영상
            if (tmpOutImage[i][j] < 0.0)
                outImage[i][j] = 0;
            else if (tmpOutImage[i][j] > 255.0)
                outImage[i][j] = 255;
            else
                outImage[i][j] = (unsigned char)tmpOutImage[i][j];
        }
    }

    freeDoubleMemory(tmpInImage, inH + (size - 1));
    freeDoubleMemory(tmpOutImage, outH);
    freeDoubleMemory(mask, size);
    printImage();
}
void edgeLOG() { // 가우시안 블러링 -> 라플라시안 적용 -> zero-crossing
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    //double mask[5][5] // LOG 필터
    //    = { {0.0, 0.0, -1.0, 0,0, 0.0} ,
    //        {0.0, -1.0, -2.0, -1,0, 0.0} ,
    //        {-1.0, -2.0, 16.0, -2.0, -1.0},
    //        {0.0,-1.0, -2.0, -1,0, 0.0} ,
    //        {0.0, 0.0, -1.0, 0.0, 0.0} };

    int t;
    while (1) {
        printf("에지를 얼마나 찾을까요?(0~255)\n");
        t = getInValue();
        if ((t < 0) || (t > 255))
            printf("잘못된 입력입니다. 다시 시도하세요.(0~255)\n");
        else
            break;
    }
    double gaussMask[3][3];
    double gaussian;
    // 3x3 크기의 시그마 0.5인 가우시안 마스크 생성
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // 3x3 가우시안 마스크
            double x = sqrt((pow((i - 1), 2) + pow((j - 1), 2)));
            gaussian = exp(-(x * x) / (2.0 * 0.5 * 0.5)) / (0.5 * sqrt(2.0 * PI));
            gaussMask[i][j] = gaussian;
        }
    }
    // 라플라시안 마스크 생성
    double laplaceMask[3][3] = {
        {0.0, 1.0, 0.0},
        {1.0, -4.0, 1.0},
        {0.0, 1.0, 0.0}
    };
    double** tmpInImage = mallocDoubleMemory(inH + 2,inW + 2);
    double** tmpOutImage = mallocDoubleMemory(outH,outW);

    // 패딩1
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImage[i + 1][j + 1] = inImage[i][j];
        }
    }
    // log는 잡음에 민감하기 때문에 가우시안 마스크를 통한 블러 처리
    double sum;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            sum = 0;
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    // 가우시안 마스크를 통한 블러 처리
                    sum += tmpInImage[i + k][j + q] * gaussMask[k][q];
                }
            }
            tmpOutImage[i][j] = sum;
        }
    }
    // 패딩2
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImage[i + 1][j + 1] = tmpOutImage[i][j];
        }
    }
    // 라플라시안 마스크를 블러된 영상에 적용
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            sum = 0;
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    sum += tmpInImage[i + k][j + q] * laplaceMask[k][q];
                }
            }
            tmpOutImage[i][j] = sum;
        }
    }
    // 패딩3
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImage[i + 1][j + 1] = tmpOutImage[i][j];
        }
    }
    // zero-crossing
    int isEgde;
    for (int j = 1; j < inH - 1; j++) {
        for (int k = 1; k < inW - 1; k++) {
            int sum = 0;

            // 좌측 45도 방향에서 부호가 바뀌는지 확인
            if (tmpInImage[j - 1][k - 1] * tmpInImage[j + 1][k + 1] < 0) { // 바뀐다면 그 차이가 임계값보다 큰지 확인
                isEgde = abs(tmpInImage[j - 1][k - 1]) + abs(tmpInImage[j + 1][k + 1]);
                if (isEgde >= t) {
                    sum += 1;
                }
            }

            // 우측 45도 방향에서 부호가 바뀌는지 확인
            if (tmpInImage[j + 1][k - 1] * tmpInImage[j - 1][k + 1] < 0) {
                isEgde = abs(tmpInImage[j - 1][k - 1]) + abs(tmpInImage[j - 1][k + 1]);
                if (isEgde >= t) {
                    sum += 1;
                }
            }

            // 세로 방향에서 부호가 바뀌는지 확인
            if (tmpInImage[j][k - 1] * tmpInImage[j][k + 1] < 0) {
                isEgde = abs(tmpInImage[j][k - 1]) + abs(tmpInImage[j][k + 1]);
                if (isEgde >= t) {
                    sum += 1;
                }
            }

            // 가로 방향에서 부호가 바뀌는지 확인
            if (tmpInImage[j - 1][k] * tmpInImage[j + 1][k] < 0) {
                isEgde = abs(tmpInImage[j - 1][k]) + abs(tmpInImage[j + 1][k]);
                if (isEgde >= t) {
                    sum += 1;
                }
            }

            // 부호가 바뀌는 쌍과 그 차이가 임계값보다 큰 경우가 2쌍 이상이면 에지 처리
            if (sum >= 2) {
                tmpInImage[j][k] = 255.0;
            }
        }
    }
    // 임시 출력 영상 -> 출력 영상
    for (int i = 1; i < outH - 1; i++) {
        for (int j = 1; j < outW - 1; j++) {
            if (tmpInImage[i][j] < 0.0)
                outImage[i-1][j-1] = 0;
            else if (tmpInImage[i][j] > 255.0)
                outImage[i-1][j-1] = 255;
            else
                outImage[i-1][j-1] = (unsigned char)tmpInImage[i][j];
        }
    }
    freeDoubleMemory(tmpInImage, inH + 2);
    freeDoubleMemory(tmpOutImage, outH);
    printImage();
}
// 케니와 유사
void edgeBetterLOG() { // 가우시안 x,y 미분 -> 입력 영상에 적용 -> 에지 강도 계산 -> 이진화
    if (inImage == NULL)
        return;
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    //double mask[9][9] = { // DOG 필터
    //    {0.0, 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0, 0.0},
    //    {0.0, -2.0, -3.0, -3.0, -3.0, -3.0, -3.0, -2.0, 0.0},
    //    {0.0, -3.0, -2.0, -1.0, -1.0, -1.0, -2.0, -3.0, 0.0},
    //    {0.0, -3.0, -1.0, 9.0, 9.0, 9.0, -1.0, -3.0, 0.0},
    //    {-1.0, -3.0, -1.0, 9.0, 19.0, 9.0, -1.0, -3.0, -1.0},
    //    {0.0, -3.0, -1.0, 9.0, 9.0, 9.0, -1.0, -3.0, 0.0},
    //    {0.0, -3.0, -2.0, -1.0, -1.0, -1.0, -2.0, -3.0, 0.0},
    //    {0.0, -2.0, -3.0, -3.0, -3.0, -3.0, -3.0, -2.0, 0.0},
    //    {0.0, 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0, 0.0}
    //    };
    
    int t;
    while (1) {
        printf("에지를 얼마나 찾을까요?(0~255)\n");
        t = getInValue();
        if ((t < 0) || (t > 255))
            printf("잘못된 입력입니다. 다시 시도하세요.(0~255)\n");
        else
            break;
    }
    double gaussMask[3][3];
    double gaussian;
    // 3x3 크기의 시그마 0.5인 가우시안 마스크 생성
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double x = sqrt((pow((i - 1), 2) + pow((j - 1), 2)));
            gaussian = exp(-(x * x) / (2.0 * 0.5 * 0.5)) / (0.5 * sqrt(2.0 * PI));
            gaussMask[i][j] = gaussian;
        }
    }
    // 미분연산을 위한 sobel 마스크
    double sobelX[3][3] = {
        {-1.0, 0.0, 1.0},
        {-2.0, 0.0, 2.0},
        {-1.0, 0.0, 1.0}
    };
    double sobelY[3][3] = {
        {-1.0, -2.0, -1.0},
        {0.0, 0.0, 0.0},
        {1.0, 2.0, 1.0}
    };
    // 가우시안 마스크 미분 연산
    double sumX, sumY;
    double gaussX[5][5] = { 0.0, };
    double gaussY[5][5] = { 0.0, };
    double sobelGaussX[3][3];    double sobelGaussY[3][3];

    // 가우시안 마스크 패딩
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gaussX[i + 1][j + 1] = gaussMask[i][j];
            gaussY[i + 1][j + 1] = gaussMask[i][j];
        }
    }
    // 컨볼루션
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sumX = 0.0;
            sumY = 0.0;
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    sumX += gaussX[i + k][j + q] * sobelX[k][q];
                    sumY += gaussY[i + k][j + q] * sobelY[k][q];
                }
            }
            sobelGaussX[i][j] = sumX; // 미분된 가우시안 마스크
            sobelGaussY[i][j] = sumY;
        }
    }
    // 미분된 가우시안 필터를 영상에 적용
    double** tmpInImageX = mallocDoubleMemory(inH + 2, inW + 2);
    double** tmpInImageY = mallocDoubleMemory(inH + 2,inW + 2);
    double** tmpOutImage = mallocDoubleMemory(outH, outW);
    // 입력 영상 패딩
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            tmpInImageX[i + 1][j + 1] = inImage[i][j];
            tmpInImageY[i + 1][j + 1] = inImage[i][j];
        }
    }
    // 컨볼루션
    double dogX, dogY;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            dogX = 0.0;
            dogY = 0.0;
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    dogX += tmpInImageX[i + k][j + q] * sobelGaussX[k][q];
                    dogY += tmpInImageY[i + k][j + q] * sobelGaussY[k][q];
                }
            }
            tmpOutImage[i][j] = fabs(dogX) + fabs(dogY); // 에지 강도 계산
        }
    }
    // 임계 강도로 이진화
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            if (tmpOutImage[i][j] > t)
                tmpOutImage[i][j] = 255.0;
            else
                tmpOutImage[i][j] = 0.0;
        }
    }
    //임시 출력 영상 -> 출력 영상
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            outImage[i][j] = (unsigned char)tmpOutImage[i][j];
        }
    }
    freeDoubleMemory(tmpInImageX, inH + 2);
    freeDoubleMemory(tmpInImageY, inH + 2);
    freeDoubleMemory(tmpOutImage, outH);
    printImage();
}
void edgeDOG() {
    if (inImage == NULL)  // 입력 이미지가 없으면 함수 종료
        return;
    freeOutputMemory();  // 출력 메모리 해제
    outH = inH;  // 출력 이미지의 높이를 입력 이미지의 높이로 설정
    outW = inW;  // 출력 이미지의 너비를 입력 이미지의 너비로 설정
    mallocOutputMemory();  // 출력 메모리 할당

    double mask[9][9]
        = { {0,0,0,-1,-1,-1,0,0,0},
            {0,-2,-3,-3,-3,-3,-3,-2,0},
            {0,-3,-2,-1,-1,-1,-2,-3,0},
            {0,-3,-1,9,9,9,-1,-3,0},
            {-1,-3,-1,9,19,9,-1,-3,-1},
            {0,-3,-1,9,9,9,-1,-3,0},
            {0,-3,-2,-1,-1,-1,-2,-3,0},
            {0,-2,-3,-3,-3,-3,-3,-2,0},
            {0,0,0,-1,-1,-1,0,0,0}
    };
    // 임시 입력/출력 메모리 준비
    double** tmpInput = mallocDoubleMemory(inH + 8, inW + 8); //엣지구간 마스킹을 간단하게 하기위해.(넓어진 영역들은 삭제될 예정)
    double** tmpOutput = mallocDoubleMemory(outH, outW);
    for (int i = 0; i < inH; i++) {
        for (int k = 0; k < inW; k++) {
            tmpInput[i + 4][k + 4] = inImage[i][k];
        }
    }

    // 진짜 영상 처리 알고리즘 ==> 회선연산
    double S = 0.0; // 마스크9개 X 입력영상 9개의 합...
    for (int i = 0; i < inH; i++) {
        for (int k = 0; k < inW; k++) {
            S = 0.0; // 누적 값은 초기화하는 것 권장
            for (int m = 0; m < 9; m++) {
                for (int n = 0; n < 9; n++) {
                    S += tmpInput[i + m][k + n] * mask[m][n];
                }
            }
            tmpOutput[i][k] = S;
        }
    }

    for (int i = 0; i < outH; i++) {
        for (int k = 0; k < outW; k++) {
            double v = tmpOutput[i][k];
            if (v > 255.0) v = 255.0;
            if (v < 0.0) v = 0.0;
            outImage[i][k] = (unsigned char)v;
        }
    }
    freeDoubleMemory(tmpInput, inH + 8);
    freeDoubleMemory(tmpOutput, outH);
    printImage();
    //int t;
    //while (1) {
    //    printf("에지를 얼마나 찾을까요?(0~255)\n");
    //    t = getInValue();
    //    if ((t < 0) || (t > 255))
    //        printf("잘못된 입력입니다. 다시 시도하세요.(0~255)\n");
    //    else
    //        break;
    //}
    //// Gaussian mask generation
    //double gaussMask1[3][3];
    //double gaussMask2[3][3];
    //double gaussian1, gaussian2;
    //// 서로 다른 표준편차를 갖는 가우시안 마스크 생성
    //for (int i = 0; i < 3; i++) {
    //    for (int j = 0; j < 3; j++) {
    //        double x = sqrt((pow((i - 1), 2) + pow((j - 1), 2)));
    //        gaussian1 = exp(-(x * x) / (2.0 * 2.0 * 2.0)) / (2.0 * sqrt(2.0 * PI));
    //        gaussian2 = exp(-(x * x) / (2.0 * 3.2 * 3.2)) / (3.2 * sqrt(2.0 * PI));
    //        gaussMask1[i][j] = gaussian1;
    //        gaussMask2[i][j] = gaussian2;
    //    }
    //}

    //// Temporary memory allocation
    //double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2);
    //double** tmpOutImage1 = mallocDoubleMemory(outH, outW);
    //double** tmpOutImage2 = mallocDoubleMemory(outH, outW);
    //double** tmpOutImage3 = mallocDoubleMemory(outH, outW);

    //// 임시 메모리 초기화
    //for (int i = 0; i < inH + 2; i++) {
    //    for (int j = 0; j < inW + 2; j++) {
    //        tmpInImage[i][j] = 0.0;
    //    }
    //}

    //// Padding 1
    //// 입력 이미지를 패딩을 포함한 임시 이미지로 복사
    //for (int i = 0; i < inH; i++) {
    //    for (int j = 0; j < inW; j++) {
    //        tmpInImage[i + 1][j + 1] = inImage[i][j];
    //    }
    //}

    //// Applying Gaussian masks to the input image
    //// 가우시안 마스크를 입력 이미지에 적용
    //double sum1, sum2;
    //for (int i = 0; i < inH; i++) {
    //    for (int j = 0; j < inW; j++) {
    //        sum1 = 0.0;
    //        sum2 = 0.0;
    //        for (int k = 0; k < 3; k++) {
    //            for (int q = 0; q < 3; q++) {
    //                sum1 += tmpInImage[i + k][j + q] * gaussMask1[k][q];
    //                sum2 += tmpInImage[i + k][j + q] * gaussMask2[k][q];
    //            }
    //        }
    //        tmpOutImage1[i][j] = sum1;
    //        tmpOutImage2[i][j] = sum2;
    //    }
    //}

    //// Calculating difference between the two filtered images
    //// 두 필터링된 이미지의 차이 계산
    //for (int i = 0; i < outH; i++) {
    //    for (int j = 0; j < outW; j++) {
    //        tmpOutImage3[i][j] = tmpOutImage1[i][j] - tmpOutImage2[i][j];
    //    }
    //}

    //// Copying result from temporary output image to output image
    //// 임시 출력 이미지의 결과를 출력 이미지로 복사
    //for (int i = 0; i < outH; i++) {
    //    for (int j = 0; j < outW; j++) {
    //        if (tmpOutImage3[i][j] < t)
    //            outImage[i][j] = 255;  
    //        else
    //            outImage[i][j] = 0;  
    //    }
    //}

    //// Freeing allocated memory
    //// 할당된 메모리 해제
    //freeDoubleMemory(tmpInImage, inH + 2);
    //freeDoubleMemory(tmpOutImage1, outH);
    //freeDoubleMemory(tmpOutImage2, outH);
    //freeDoubleMemory(tmpOutImage3, outH);

    //printImage();  // 이미지 출력
}

