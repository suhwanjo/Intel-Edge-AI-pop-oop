import random
import numpy as np

# 함수부
def printImage():
    global inImage, outImage, inH, inW, outH, outW
    for i in range(outH//2-5, outH//2+5, 1):
        for k in range(outW//2-5, outW//2+5, 1):
            print(f"{outImage[i][k]:3d}", end=' ')
        print()
    print()


def malloc2D(h, w):
    #memory = [[0 for _ in range(w)] for _ in range(h)]
    memory = np.zeros((h, w), dtype=np.uint8)
    return memory


def equalImage():
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    # 진짜 영상처리 알고리즘
    # for i in range(inH):
    #     for k in range(inW):
    #         outImage[i][k] = inImage[i][k]
    outImage = inImage

    printImage()


# 화소 점 처리
def addSubImage():
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    val = int(input("밝기 조절 정도를 입력하세요.(-:어둡게, +:밝게) : "))
    # np.clip을 사용할 수 있긴 함,,
    for i in range(inH):
        for k in range(inW):
            if val < 0:
                if inImage[i][k] + val >= 0:
                    outImage[i][k] = inImage[i][k] + val
                else:
                    outImage[i][k] = 0
            else:
                if inImage[i][k] + val <= 255:
                    outImage[i][k] = inImage[i][k] + val
                else:
                    outImage[i][k] = 255

    printImage()


def reverseImage():
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    outImage = 255 - inImage

    printImage()


def binaryImage():
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    while True:
        option = int(input("임계값 설정 방법을 선택하세요.(0.직접입력 1.평균값 2.중앙값) : "))
        if option == 0:
            val = int(input("임계값을 입력하세요.(0~255) : "))
            break
        elif option == 1:
            val = np.mean(inImage)
            print(f"영상의 평균값은 {result}입니다.")
            break
        elif option == 2:
            val = np.median(inImage)
            print(f"영상의 중앙값은 {median}입니다.")
            break
        else:
            print("잘못된 입력입니다. 다시 시도하세요.(0,1,2)")

    for i in range(inH):
        for k in range(inW):
            if inImage[i][k] > val:
                outImage[i][k] = 255
            else:
                outImage[i][k] = 0

    printImage()


# def avgCalc():
#     global inImage, outImage, inH, inW, outH, outW
#     if inImage is None:
#         return
#     hap = 0
#     for i in range(inH):
#         for k in range(inW):
#             hap += inImage[i][k]
#     result = hap // (inH * inW)
#     print(f"영상의 평균값은 {result}입니다.")
#
#     return result
#
#
# def medCalc():
#     global inImage, outImage, inH, inW, outH, outW
#     if inImage is None:
#         return
#     arr = [0 for _ in range(256)]
#     count, median = 0, 0
#     for i in range(inH):
#         for k in range(inW):
#             arr[inImage[i][k]] += 1
#     for i in range(256):
#         count += arr[i]
#         if count >= (inH * inW / 2):
#             median = i
#             break
#     print(f"영상의 중앙값은 {median}입니다.")
#
#     return median


def gammaImage():
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    while True:
        gam = float(input("감마(Gamma) 값을 소수 형태로 입력하세요.(0.0~5.0) : "))
        if 0.0 <= gam < 5.0:
            outImage = pow((inImage / 255.0), gam) * 255.0
            outImage = outImage.astype(np.uint8) # 자료형 변환
            break
        else:
            print("잘못된 입력입니다. 다시 시도하세요.(0.0~5.0)")

    printImage()


def paraImage():
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    while True:
        option = input("변환 방법을 입력하세요.(CAP:밝은 곳이 입체적으로 CUP:어두운 곳이 입체적으로) : ")
        option = option.lower()
        if option == "cap":
            outImage = 255.0 * pow((inImage / 127.0 - 1.0), 2.0)
            outImage = outImage.astype(np.uint8)
            break
        elif option == "cup":
            outImage = 255.0 - 255.0 * pow((inImage / 127.0 - 1.0), 2.0)
            outImage = outImage.astype(np.uint8)
            break
        else:
            print("잘못된 입력입니다. 다시 시도하세요(CAP,CUP)")

    printImage()


def postImage():
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW

    for i in range(inH):
        for k in range(inW):
            if 0 <= inImage[i][k] <= 31:
                outImage[i][k] = 31
            elif 32 <= inImage[i][k] <= 63:
                outImage[i][k] = 63
            elif 64 <= inImage[i][k] <= 95:
                outImage[i][k] = 95
            elif 96 <= inImage[i][k] <= 127:
                outImage[i][k] = 127
            elif 128 <= inImage[i][k] <= 159:
                outImage[i][k] = 159
            elif 160 <= inImage[i][k] <= 191:
                outImage[i][k] = 191
            elif 192 <= inImage[i][k] <= 223:
                outImage[i][k] = 223
            elif 224 <= inImage[i][k] <= 255:
                outImage[i][k] = 255

    printImage()


def emphImage():
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    while True:
        print("강조할 픽셀 값의 범위를 입력하세요.(0~255)")
        startVal = int(input("시작 픽셀 : "))
        endVal = int(input("끝 픽셀 : "))
        if 0 <= startVal <= 255 and 0 <= endVal <= 255:
            break
        else:
            print("잘못된 입력입니다. 다시 시도하세요(0~255)")

    for i in range(inH):
        for k in range(inW):
            if ((startVal < inImage[i][k] < endVal) or (endVal < inImage[i][k] < startVal)):
                outImage[i][k] = 255
            else:
                outImage[i][k] = inImage[i][k]

    printImage()


def histoStretch():
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW

    high = np.max(inImage)
    low = np.min(inImage)
    # print(high, low)
    # high = inImage[0][0]
    # low = inImage[0][0]
    #
    # for i in range(inH):
    #     for j in range(inW):
    #         if inImage[i][j] < low:
    #             low = inImage[i][j]
    #         if inImage[i][j] > high:
    #             high = inImage[i][j]

    for i in range(inH):
        for k in range(inW):
            # End-In 탐색 : 최대 최소값 사이를 좁혀 스트레칭 효과를 극대화
            # new = (old - low) / (high - low) * 255
            old = inImage[i][k]
            new = int(((old - low) / (high - low)) * 255.0)
            if new > 255:
                new = 255
            if new < 0:
                new = 0
            outImage[i][k] = new

    printImage()


def histoEqual():
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW

    histogram, _ = np.histogram(inImage, bins=256, range=(0, 256))
    cumHisto = np.cumsum(histogram)
    normCumHisto = cumHisto * (1.0/ (inH * inW)) * 255.0
    for i in range(inH):
        for k in range(inW):
            outImage[i][k] = normCumHisto[inImage[i][k]]

    printImage()

# 메인부
inImage, outImage = [], []
inH, inW, outH, outW = [0] * 4

inH = int(input("입력 이미지 높이(128, 256, 512...) : "))
inW = int(input("입력 이미지 너비(128, 256, 512...) : "))

inImage = malloc2D(inH, inW)

for i in range(inH):
    for k in range(inW):
        inImage[i][k] = random.randint(0, 255)

equalImage()
#binaryImage()
#addSubImage()
#gammaImage()
#paraImage()

#histoStretch()
histoEqual()
## 미션 : C언어의 화소 점 처리/화소 영역 처리/기하학 처리/히스토그램 등 함수 구현하기