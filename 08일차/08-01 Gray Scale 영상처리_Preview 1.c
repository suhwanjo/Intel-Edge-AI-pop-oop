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
        case 'B': addImage(); break;
        case 'c':
        case 'C': reverseImage(); break;
        case 'd':
        case 'D': binaryImage(); break;
        case 'e':
        case 'E': gammaImage(); break;
        case 'f':
        case 'F': paraImage(); break;
        case 'g':
        case 'G': postImage(); break;
        case 'h':
        case 'H': emphImage(); break;
        case 'i':
        case 'I': scaleImage(); break;
        case 'j':
        case 'J': rotatImage(); break;
        case 'k':
        case 'K': moveImage(); break;
        case 'l':
        case 'L': mirrorImage(); break;
        case 'm':
        case 'M': histoStretch(); break;
        case 'n':
        case 'N': histoEqual(); break;
        case 'o':
        case 'O': emboss(); break;
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
    puts(" ---------------------------------------------------------------");
    puts("|  ## Gray Scale Image Processing (RC 2) ##                     |");
    puts("|---------------------------------------------------------------|");
    puts("|  0. 열기     1. 저장      9. 종료                             |");
    puts("|---------------------------------------------------------------|");
    puts("|  A. 원본             B. 밝기조절  C. 반전                     |");
    puts("|  D. 이진화           E. 감마보정  F. 파라볼릭변환             |");
    puts("|  G. 포스터라이징     H. 범위강조  I. 확대/축소                |");
    puts("|  J. 회전             K. 이동      L. 미러링(대칭)             |");
    puts("|  M. 명암대비스트레칭 N. 평활화    O. 엠보싱/블러링/샤프닝     |");
    puts(" ---------------------------------------------------------------");
}
void printImage() {
    //system("cls");
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            int px = outImage[i][j];
            SetPixel(hdc, j + 500, i + 500, RGB(px, px, px)); // 뿌릴 좌표, RGB 채널 값이 같으면 Gray Scale
        }
    }
}
void loadImage() { // 하나 열고 또 열면 오류 남
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
    for (int i = 0; i < inH; i++) {
        fread(inImage[i], sizeof(unsigned char), inH, rfp);
    }
    fclose(rfp);

    equalImage();
}
void saveImage() {
    if (outImage == NULL)
        return;
    char fullName[200] = "C:/Users/IOT/Desktop/Project1/Intel-Edge-AI-SW-Academy/RAW/";
    char tmpName[50];
    printf("파일명 : "); 
    scanf("%s", &tmpName);
    strcat(fullName, tmpName); 
    strcat(fullName, ".raw"); 
    strcat(fileName, fullName);

    wfp = fopen(fileName, "wb");
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
    double **retMemory = (double**)malloc(sizeof(double*) * h);
    for (int i = 0; i < h; i++) {
        retMemory[i] = (double*)malloc(sizeof(double) * w);
    }

    return retMemory;
}
void freeDoubleMemory(double **memory, int h) {
    if (memory == NULL)
        return;
    for (int i = 0; i < outH; i++) {
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
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    printf("밝기 조절 정도를 입력하세요.(-:어둡게, +:밝게)");
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
        if (count >= (inH*inW / 2)) {
            median = i;
            break;
        }
    }
    printf("영상의 중앙 값: %d\n", median);
    return median;
}
void gammaImage() { // 감마보정
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
            printf("잘못된 입력입니다. 다시 시도하세요.(0.5~25)\n");
    }
    printImage();
}
void paraImage() { // 파라볼릭변환
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
            printf("잘못된 입력입니다. 다시 시도하세요.(0~1)\n");
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
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    // new = (old - low) / (high - low) * 255
    int high  = inImage[0][0]; // 최대, 최소 구할 때 처음 값으로 설정
    int low = inImage[0][0];
    
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            if (inImage[i][j] < low)
                low = inImage[i][j];
            if (inImage[i][j] > high)
                high = inImage[i][j];
        }
    }
    // End-In 탐색 : 최대 최소값 사이를 좁혀 스트레칭 효과를 극대화
    // high -= 50;
    // low += 50;  
    //
    int old, new;
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            old = inImage[i][j];
            new = (int)((old - low) / (double)(high - low) * 255.0);
            outImage[i][j] = new;
        }
    }
    printImage();
}
void histoEqual() { // 히스토그램 평활화
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();
    
    // 1단계 : 빈도수 세기(=히스토그램) histo[256]
    int histo[256] = { 0, };
    for (int i = 0; i < inH; i++)
        for (int j = 0; j < inW; j++)
            histo[inImage[i][j]]++;
    // 2단계 : 누적히스토그램 생성
    int sumHisto[256] = { 0, };
    sumHisto[0] = histo[0];
    for (int i = 1; i < 256; i++)
        sumHisto[i] = sumHisto[i - 1] + histo[i];
    // 3단계 : 정규화된 히스토그램 생성  normalHisto = sumHisto * (1.0 / (inH*inW) ) * 255.0;
    double normalHisto[256] = { 1.0, };
    for (int i = 0; i < 256; i++) {
        normalHisto[i] = sumHisto[i] * (1.0 / (inH * inW)) * 255.0;
    }
    // 4단계 : inImage를 정규화된 값으로 치환
    for (int i = 0; i < inH; i++) {
        for (int j = 0; j < inW; j++) {
            outImage[i][j] = (unsigned char)normalHisto[inImage[i][j]];
        }
    }
    printImage();
}
// 기하 변환
void scaleImage() { // 확대/축소
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
                        histo[inImage[k][q]] += 1;
                    }
                }
                count = 0;
                for (int a = 0; a < 256; a++) {
                    count += histo[a];
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
        printImage();
    }
}
void rotatImage() { // 회전
    int degree = getInValue();
    double radian = -degree * PI / 180.0;
    freeOutputMemory();
    outH = (int)(inH * fabs(cos(radian)) + inW * fabs(sin(radian)));
    outW = (int)(inW * fabs(cos(radian)) + inH * fabs(sin(radian)));
    mallocOutputMemory();
    printf("%d %d", outH, outW);
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

    // 왜 정확히 중심으로 안 이동하는지 모르겠음
    int cx = outW / 2;
    int cy = outH / 2;
 
    int xs, ys;
    for (int i = 0; i < outH; i++) { // 백워딩 + 중앙으로 이동
        for (int j = 0; j < outW; j++) {
            int xd = i;
            int yd = j;
            xs = (int)(cos(-radian) * (xd - cx) + sin(-radian) * (yd - cy));
            ys = (int)(-sin(-radian) * (xd - cx) + cos(-radian) * (yd - cy));
            xs += cx;
            ys += cy;
            if ((0 <= xs && xs < inH) && (0 <= ys && ys < inW))
                outImage[xd][yd] = inImage[xs][ys];
        }
    }
    printImage();
}
void moveImage() { // 이동
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    int move = getInValue();
    if (move >= 0) { // 우측 하단으로 이동
        for (int i = 0; i < outH - move; i++) {
            for (int j = 0; j < outW - move; j++) {
                if ((0 <= i && i < outH) && (0 <= j && j < outW))
                    outImage[i + move][j + move] = inImage[i][j];
            }
        }
    }
    else // 좌측 상단으로 이동
        for (int i = 0; i < outH; i++) {
            for (int j = 0; j < outW; j++) {
                if ((0 - move <= i && i < outH) && (0 - move <= j && j < outW))
                    outImage[i + move][j + move] = inImage[i][j];
            }
        }
    printImage();
}
void mirrorImage() { // 미러링(대칭)
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
                    outImage[i][-(j - outW + 1)] = inImage[i][j];
                }
            }
            break;
        }
        else if (mirror == 0) {
            for (int i = 0; i < outH; i++) {
                for (int j = 0; j < outW; j++) {
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
    freeOutputMemory();
    outH = inH;
    outW = inW;
    mallocOutputMemory();

    int type;
    int size = 0;
    double embossMask[3][3];
    while (1) {
        printf("영역 처리 타입을 선택하세요.(0.엠보싱 1.블러링 2.스무딩 3.샤프닝)\n");
        type = getInValue();
        printf("적용 정도를 선택하세요.(홀수만 가능)\n");
        size = getInValue();

        if (type == 0) { // 엠보싱 : 처음에 -1,  끝에 1
            double mask[3][3] = { // 마스크(. 필수)
                { -1.0, 0.0, 0.0 },
                {0.0, 0.0, 0.0 },
                {0.0, 0.0, 1.0 } };
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    embossMask[i][j] = mask[i][j];
                }
            }
            break;
        }
        else if (type == 1) { // 블러링 : size * size 로 나눔
            double mask[3][3] = {
                { 1 / 9., 1 / 9., 1 / 9. },
                {1 / 9., 1 / 9., 1 / 9. },
                {1 / 9., 1 / 9., 1 / 9. } };
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    embossMask[i][j] = mask[i][j];
                }
            }
            break;
        }
        else if (type == 2) { // 스무딩 : exp(-(x * x) / (2 * sigma * sigma)) / (sigma * sqrt(2 * PI))
            double mask[3][3] = {
                { 1 / 16., 1 / 8., 1 / 16. },
                {1 / 8., 1 / 4., 1 / 8. },
                {1 / 16., 1 / 8., 1 / 16. } };
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    embossMask[i][j] = mask[i][j];
                }
            }
            break;
        }
        else if (type == 3) { // 샤프닝 : 주변은 -1, 중앙은 주변의 (-합)
            double mask[3][3] = {
                { -1.0, -1.0, -1.0 },
                {-1.0, 9.0, -1.0 },
                {-1.0, -1.0, -1.0 } };
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    embossMask[i][j] = mask[i][j];
                }
            }
            break;
        }
        else
            printf("잘못된 입력입니다. 다시 시도하세요.(0~3)\n");
    }
    // 임시 이미지 할당(실수) : 패딩을 위한
    double** tmpInImage = mallocDoubleMemory(inH + 2, inW + 2); // 필터 크기에 따라 패딩 변화
    double** tmpOutImage = mallocDoubleMemory(outH + 2, outW + 2);
    // 임시 이미지 초기화(127)
    for (int i = 0; i < inH + 2; i++) {
        for (int j = 0; j < inW + 2; j++) {
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
            for (int k = 0; k < 3; k++) {
                for (int q = 0; q < 3; q++) {
                    sum += tmpInImage[i + k][j + q] * embossMask[k][q];
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
        //임시 출력 영상 -> 출력 영상
    for (int i = 0; i < outH; i++) {
        for (int j = 0; j < outW; j++) {
            if (tmpOutImage[i][j] < 0.0) 
                outImage[i][j] = 0;
            else if (tmpOutImage[i][j] > 255.0)
                outImage[i][j] = 255;
            else
                outImage[i][j] = (unsigned char)tmpOutImage[i][j];
        }
    }

    freeDoubleMemory(tmpInImage, inH + 2);
    freeDoubleMemory(tmpOutImage, outH);
    printImage();
        
    
}