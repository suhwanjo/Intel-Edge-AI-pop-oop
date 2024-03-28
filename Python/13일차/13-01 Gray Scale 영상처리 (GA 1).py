import tkinter.simpledialog
from tkinter import *
from tkinter import messagebox
from tkinter.filedialog import *
from tkinter.simpledialog import *
import numpy as np
import os
import math
# 핵심만 빠르게


# 함수부
def openImage():  # 열기
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return

    # fullName = 'C:/Users/IOT/Desktop/Project1/Intel-Edge-AI-SW-Academy/RAW/cat01_256.raw'
    fullName = askopenfilename(parent=window, filetypes=(('RAW 파일', '*.raw'), ('모든 파일', '*.*')))
    fsize = os.path.getsize(fullName)  # 파일 크기
    inH = inW = int(math.sqrt(fsize))
    # 입력 메모리 할당
    inImage = malloc2D(inH, inW)
    rfp = open(fullName, 'rb')
    for i in range(inH):
        for k in range(inW):
            inImage[i][k] = ord(rfp.read(1))  # 파일 에서 읽어올 때 문자열 로 읽어 오기 때문에 ord 를 통해 숫자로 변환
    rfp.close()

    equalImage()


def saveImage():  # 저장
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if outImage is None or len(outImage) == 0:
        return
    wfp = asksaveasfile(parent=window, mode='wb', defaultextension='*.raw',
                        filetypes=(('RAW 파일', '*.raw'), ('모든 파일', '*.*')))
    import struct
    for i in range(outH):
        for k in range(outW):
            wfp.write(struct.pack('B', outImage[i][k]))
    wfp.close()
    messagebox.showinfo('성공', wfp.name + '저장 완료.')


def closeApp():  # 종료
    window.destroy()


def displayImage():  # 영상 출력
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    # 기존에 영상을 연 적이 있으면, 캔버스 뜯어내기
    if canvas is not None:
        canvas.destroy()
    # 벽, 캔버스, 종이 설정
    window.geometry(str(outH)+'x'+str(outW))  # 출력 화면 크기 조정
    canvas = Canvas(window, height=outH, width=outH, bg='yellow')  # 칠판
    paper = PhotoImage(height=outH, width=outH)  # 종이
    canvas.create_image(outH // 2, outH // 2, image=paper, stat='normal')
    # 화면에 픽셀 찍기
    # for i in range(inH):
    #     for k in range(inW):
    #         r = g = b = outImage[i][k]
    #
    #         paper.put('#%02x%02x%02x' % (r, g, b), (k, i))

    # 메모리 사용해서 화면에 빠르게 띄우기
    rgbString = ""  # 전체에 대한 16진수 문자열
    for i in range(outH):
        oneString = ""  # 한 줄에 대한 16진수 문자열
        for k in range(outW):
            r = g = b = outImage[i][k]
            oneString += '#%02x%02x%02x ' % (r, g, b)
        rgbString += '{' + oneString + '} '
    paper.put(rgbString)

    canvas.pack()


def malloc2D(h, w, initVal=0):
    # memory = [[0 for _ in range(w)] for _ in range(h)]
    memory = np.zeros((h+initVal, w+initVal), dtype=np.uint32)
    return memory


####################### 영상 처리 함수
def equalImage():
    global inImage, outImage, inH, inW, outH, outW
    # (중요!) 출력 이미지 크기 결정 --> 알고 리즘에 의존
    outH = inH
    outW = inW
    # 출력 이미지 메모리 확보
    outImage = malloc2D(outH, outW)
    # 진짜 영상 처리 알고 리즘
    # for i in range(inH):
    #     for k in range(inW):
    #         outImage[i][k] = inImage[i][k]
    outImage = inImage

    displayImage()


############## 화소 변환
def addSubImage(option):  # 밝기 조절
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    if option == 0:
        val = askinteger("정수 입력", '0~255 입력', maxvalue=255, minvalue=0)
        # np.clip 을 사용할 수 있긴 함,,
        for i in range(inH):
            for k in range(inW):
                px = inImage[i][k] + val
                if px > 255:
                    px = 255
                if px < 0:
                    px = 0
                outImage[i][k] = px
    elif option == 1:
        val = askinteger("정수 입력", '0~255 입력', maxvalue=255, minvalue=0)
        # np.clip 을 사용할 수 있긴 함,,
        for i in range(inH):
            for k in range(inW):
                px = inImage[i][k] - val
                if px > 255:
                    px = 255
                if px < 0:
                    px = 0
                outImage[i][k] = px

    displayImage()


def reverseImage():  # 반전
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    arrayImage = np.array(inImage)  # 스칼라 연산을 위해 변환
    outImage = 255 - arrayImage

    displayImage()


def binaryImage(option):  # 이진화
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    if option == 0:
        val = askinteger("정수 입력", '0~255 입력', maxvalue=255, minvalue=-255)
    elif option == 1:
        val = int(np.mean(inImage))
        messagebox.showinfo('평균 값으로 이진화', '영상의 평균 값은 ' + str(int(val)) + ' 입니다.')
    elif option == 2:
        val = np.median(inImage)
        messagebox.showinfo('중앙 값으로 이진화', '영상의 중앙 값은 ' + str(int(val)) + ' 입니다.')

    for i in range(inH):
        for k in range(inW):
            if inImage[i][k] > val:
                outImage[i][k] = 255
            else:
                outImage[i][k] = 0

    displayImage()


def gammaImage():  # 감마 보정
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    arrayImage = np.array(inImage, dtype=float)

    gam = askfloat("소수 입력", '0.0~5.0 입력', maxvalue=5.0, minvalue=0.0)
    outImage = pow((arrayImage / 255.0), gam) * 255.0
    outImage = outImage.astype(np.uint32)  # 자료형 변환

    displayImage()


def paraImage(option):  # 파라볼라 변환
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    arrayImage = np.array(inImage, dtype=float)
    if option == 0:
        outImage = 255.0 * pow((arrayImage / 127.0 - 1.0), 2.0)
        outImage = outImage.astype(np.uint32)
    elif option == 1:
        outImage = 255.0 - 255.0 * pow((arrayImage / 127.0 - 1.0), 2.0)
        outImage = outImage.astype(np.uint32)

    displayImage()


def postImage():  # 포스터라이징
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

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

    displayImage()


def emphImage():  # 범위 강조
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    startVal = askinteger("강조 시작 값 입력", '0~255 입력', maxvalue=255, minvalue=0)
    endVal = askinteger("강조 끝 값 입력", '0~255 입력', maxvalue=255, minvalue=0)
    for i in range(inH):
        for k in range(inW):
            if (startVal < inImage[i][k] < endVal) or (endVal < inImage[i][k] < startVal):
                outImage[i][k] = 255
            else:
                outImage[i][k] = inImage[i][k]

    displayImage()


def histoStretch():  # 히스토그램 스트레칭
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

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
            # End-In 탐색 : 최대 최소값 사이를 좁혀 스트 레칭 효과를 극대화
            # new = (old - low) / (high - low) * 255
            old = inImage[i][k]
            new = int(((old - low) / (high - low)) * 255.0)
            if new > 255:
                new = 255
            if new < 0:
                new = 0
            outImage[i][k] = new

    displayImage()


def histoEqual():  # 히스토그램 평활화
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    histogram, _ = np.histogram(inImage, bins=256, range=(0, 256))
    cumHisto = np.cumsum(histogram)
    normCumHisto = cumHisto * (1.0 / (inH * inW)) * 255.0
    for i in range(inH):
        for k in range(inW):
            outImage[i][k] = normCumHisto[inImage[i][k]]

    displayImage()


def morphImages():  # 모핑
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW

    # 두 번째 영상 열기
    fullName = askopenfilename(parent=window, filetypes=(('RAW 파일', '*.raw'), ('모든 파일', '*.*')))
    fsize = os.path.getsize(fullName)  # 파일 크기
    inH = inW = int(math.sqrt(fsize))
    # 입력 메모리 할당
    inImage2 = malloc2D(inH, inW)
    rfp = open(fullName, 'rb')
    for i in range(inH):
        for k in range(inW):
            inImage2[i][k] = ord(rfp.read(1))  # 파일 에서 읽어올 때 문자열 로 읽어 오기 때문에 ord 를 통해 숫자로 변환
    rfp.close()

    if canvas is not None:
        canvas.destroy()
    # 벽, 캔버스, 종이 설정
    window.geometry(str(outH) + 'x' + str(outW))  # 출력 화면 크기 조정
    canvas = Canvas(window, height=outH, width=outH, bg='yellow')  # 칠판
    paper = PhotoImage(height=outH, width=outH)  # 종이
    canvas.create_image(outH // 2, outH // 2, image=paper, stat='normal')
    # 메모리 사용해서 화면에 빠르게 띄우기
    rgbString = ""  # 전체에 대한 16진수 문자열
    for i in range(outH):
        oneString = ""  # 한 줄에 대한 16진수 문자열
        for k in range(outW):
            r = g = b = inImage2[i][k]
            oneString += '#%02x%02x%02x ' % (r, g, b)
        rgbString += '{' + oneString + '} '
    paper.put(rgbString)

    canvas.pack()

    if inImage.shape != inImage2.shape:
        messagebox.showerror('에러', '이미지의 크기는 같아야 합니다.')
        return

    # Prompt the user to enter the blend factor
    blend_factor = askfloat("혼합 정도 입력", "0.0(두 번째 영상 많이)~1.0(첫 번째 영상 많이) 입력:", minvalue=0.0, maxvalue=1.0)

    # 영상 블렌딩
    outImage = blend_factor * inImage + (1 - blend_factor) * inImage2
    outImage = outImage.astype(np.uint8)

    # Display the result
    displayImage()

############## 기하 변환
def scaleImage():  # 크기 조절(축소:중간값으로, 확대:양선형 보간)
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return

    scale = askinteger("확대/축소 배율 입력", '-10~10(축소는 짝수만) 입력', maxvalue=10, minvalue=-10)
    if scale < 0:  # 평균값 축소
        scale = -scale
        outH = inH // scale
        outW = inW // scale
        outImage = malloc2D(outH, outW)

        for i in range(outH):
            for j in range(outW):
                subMat = inImage[i * scale:i * scale + scale, j * scale:j * scale + scale]  # 축소 영역
                histo, _ = np.histogram(subMat, bins=256, range=(0, 256))  # 히스토그램 계산
                cumsum = np.cumsum(histo)  # 누적 히스토그램 계산
                median = np.argmax(cumsum >= (scale * scale) // 2)  # 중간값 계산
                outImage[i][j] = median

    elif scale > 0:  # 양선형 보간
        outH = inH * scale
        outW = inW * scale
        outImage = malloc2D(outH, outW)

        # 참고
        for y in range(outH):
            for x in range(outW):
                # 원본 이미지에서 해당 위치의 실수 좌표 계산  ex) 확대(3,4) -> 원본(1.5,2)
                y_orig = y / scale
                x_orig = x / scale
                # 원본 이미지에서 가장 가까운 4개 픽셀의 정수 좌표 계산
                y1 = int(y_orig)  # 좌측 상단
                x1 = int(x_orig)
                y2 = min(y1 + 1, inH - 1)  # 우측 하단
                x2 = min(x1 + 1, inW - 1)
                # 원본 이미지에서 해당 위치와 4개 픽셀 사이의 거리 계산
                y_diff = y_orig - y1
                x_diff = x_orig - x1
                # 가장 가까운 4개 픽셀의 값 가져오기
                val1 = inImage[y1][x1]
                val2 = inImage[y1][x2]
                val3 = inImage[y2][x1]
                val4 = inImage[y2][x2]
                # z = (1-p)(1-q)a + p(1-q)b + (1-p)qc + pqd
                outImage[y][x] = int(val1 * (1 - x_diff) * (1 - y_diff) +
                                         val2 * x_diff * (1 - y_diff) +
                                         val3 * y_diff * (1 - x_diff) +
                                         val4 * x_diff * y_diff)
    else:
        outImage = inImage

    displayImage()


def rotatImage():  # 회전(안 잘리게)
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return

    angle = askinteger("회전 각도 입력", '정수 입력')
    tmp_angle = angle % 90 * 3.141592 / 180.0
    tmp_angle90 = (90 - angle % 90) * 3.141592 / 180.0
    # 회전 각도에 따라 변화하는 출력 영상 크기 계산
    outH = int(inH * np.cos(tmp_angle90) + inW * np.cos(tmp_angle))
    outW = int(inW * np.cos(tmp_angle) + inH * np.cos(tmp_angle90))
    outImage = malloc2D(outH, outW)
    degree = angle * 3.141592 / 180.0

    dx = (outW - inW) // 2
    dy = (outH - inH) // 2
    # 회전의 시작은 입력 영상 위치에서
    tmp_image = np.zeros((outH, outW), dtype=np.uint32)
    tmp_image[dx:dx+inH, dy:dy+inW] = inImage

    cx = outH // 2
    cy = outH // 2

    for i in range(outH):
        for k in range(outW):
            xd = i
            yd = k
            xs = int(np.cos(degree) * (xd - cx) + np.sin(degree) * (yd - cy)) + cx
            ys = int(-np.sin(degree) * (xd - cx) + np.cos(degree) * (yd - cy)) + cy
            if (0 <= xs < outH) and (0 <= ys < outW):
                outImage[xd][yd] = tmp_image[xs][ys]

    displayImage()


def moveImage():  # 이동
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    move = askinteger("이동할 값 입력", '정수 입력')
    if move >= 0:  # 우측 하단으로 이동
        for i in range(outH - move):
            for k in range(outW - move):
                if (0 <= i < outH) and (0 <= k < outW):
                    outImage[i + move][k + move] = inImage[i][k]
    else:  # 좌측 상단으로 이동
        for i in range(outH):
            for k in range(outW):
                if (0 - move <= i < outH) and (0 - move <= k < outW):
                    outImage[i + move][k + move] = inImage[i][k]

    displayImage()


def mirrorImage(option):  # 미러링(대칭)
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    if option == 0:
        outImage[::-1, :] = inImage
    elif option == 1:
        outImage[:, ::-1] = inImage

    displayImage()

############## 영역 변환
def emboss(option, masksize):  # 엠보싱/블러링/스무딩/샤프닝 처리
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    mask = np.zeros((masksize, masksize), dtype=float)
    center = masksize // 2
    if option == 0:  # 엠보싱
        mask[0, 0] = -1.0
        mask[masksize - 1, masksize - 1] = 1.0
    elif option == 1:  # 블러링
        mask = (1.0 / (masksize * masksize))
    elif option == 2:  # 스무딩
        sigma = askfloat("마스크 Sigma 값 입력", '소수 입력')
        for i in range(masksize):
            for j in range(masksize):
                # 가우시안 마스크 생성
                x = np.sqrt((np.power((i - center), 2) + np.power((j - center), 2)))
                gaussian = np.exp(-(x * x) / (2.0 * sigma * sigma)) / (sigma * np.sqrt(2.0 * np.pi))
                mask[i][j] = gaussian
    elif option == 3:  # 샤프닝
        for i in range(masksize):
            for j in range(masksize):
                if i == center and j == center:
                    mask[i, j] = float(masksize * masksize)
                else:
                    mask[i, j] = -1.0
    # 입력 이미지 -> 임시 이미지에 넣기(패딩 완료)
    tmpInput = np.pad(inImage, masksize // 2, mode='constant')
    tmpOutput = np.zeros_like(outImage, dtype=float)
    for i in range(outH):
        for k in range(outW):
            S = np.sum(tmpInput[i:i + masksize, k:k + masksize] * mask)
            tmpOutput[i, k] = S

    outImage = np.clip(tmpOutput, 0, 255).astype(np.uint8)

    displayImage()


def edge(option, axis=None):  # 소벨/프레윗/라플라시안/LOG/DOG 에지 검출
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    if option == 0:  # Sobel
        if axis == 0:
            mask = np.array([[-1, -2, -1],
                            [0,  0,  0],
                            [1,  2,  1]])

        elif axis == 1:
            mask = np.array([[-1,  0,  1],
                            [-2,  0,  2],
                            [-1,  0,  1]])
        masksize = mask.shape[0]
    if option == 1:  # Prewitt
        if axis == 0:
            mask = np.array([[-1, -1, -1],
                            [0,  0,  0],
                            [1,  1,  1]])
        elif axis == 1:
            mask = np.array([[-1,  0,  1],
                            [-1,  0,  1],
                            [-1,  0,  1]])
        masksize = mask.shape[0]
    if option == 2:  # Lapacian
        mask = np.array([[0,  1,  0],
                        [1, -4,  1],
                        [0,  1,  0]])
        masksize = mask.shape[0]
    if option ==3:  # LOG
        mask = np.array([[0, 0, -1, 0, 0],
                       [0, -1, -2, -1, 0],
                       [-1, -2, 16, -2, -1],
                       [0, -1, -2, -1, 0],
                       [0, 0, -1, 0, 0]])
        masksize = mask.shape[0]
    if option == 4:  # DOG
        mask = np.array([[0, 0, -1, -1, -1, 0, 0],
                        [0, -2, -3, -3, -3, -2, 0],
                        [-1, -3,  5,  5,  5, -3, -1],
                        [-1, -3,  5, 16,  5, -3, -1],
                        [-1, -3,  5,  5,  5, -3, -1],
                        [ 0, -2, -3, -3, -3, -2, 0],
                        [ 0, 0, -1, -1, -1, 0, 0]
                    ])
        masksize = mask.shape[0]

    tmpInput = np.pad(inImage, masksize // 2, mode='constant')
    tmpOutput = np.zeros_like(outImage, dtype=float)
    for i in range(outH):
        for k in range(outW):
            S = np.sum(tmpInput[i:i + masksize, k:k + masksize] * mask)
            tmpOutput[i, k] = S

    outImage = np.clip(tmpOutput, 0, 255).astype(np.uint8)

    displayImage()


def canny():  # 케니 에지 검출
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW

    if inImage is None:
        return

    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    # 가우시안 마스크
    gaussian_blurred = gaussian_blur(inImage, (3, 3), 0.5)

    # 소벨 마스크에 가우시안 블러링
    sobel_x = np.array([[-1., 0., 1.], [-2., 0., 2.], [-1., 0., 1.]])
    sobel_y = np.array([[-1., -2., -1.], [0., 0., 0.], [1., 2., 1.]])
    sobel_x_gaussian = convolve(gaussian_blurred, sobel_x)
    sobel_y_gaussian = convolve(gaussian_blurred, sobel_y)

    # 에지 강도 및 방향 계산
    gradient_magnitude = np.sqrt(sobel_x_gaussian ** 2 + sobel_y_gaussian ** 2)
    gradient_direction = np.arctan2(sobel_y_gaussian, sobel_x_gaussian)

    # 비최대 억제 처리
    suppressed = nonmax_suppression(gradient_magnitude, gradient_direction)

    # 이중 임계값 처리
    low_th = askinteger("최소 임계값", '정수 입력')
    high_th = askinteger("최대 임계값", '정수 입력')
    canny_edges = hysteresis_thresholding(suppressed, low_th, high_th)

    for i in range(outH):
        for j in range(outW):
            outImage[i][j] = int(canny_edges[i][j])

    displayImage()


# 케니 관련 함수
def gaussian_blur(image, kernel_size, sigma):
    kernel = gaussian_kernel(kernel_size, sigma)
    return convolve(image, kernel)


def gaussian_kernel(kernel_size, sigma):
    kernel = np.fromfunction(lambda x, y: (1 / (2 * np.pi * sigma ** 2)) * np.exp(
        -((x - (kernel_size[0] - 1) / 2) ** 2 + (y - (kernel_size[1] - 1) / 2) ** 2) / (2 * sigma ** 2)), kernel_size)
    return kernel / np.sum(kernel)


def convolve(image, kernel):
    image_rows, image_cols = image.shape
    kernel_rows, kernel_cols = kernel.shape
    pad_height = kernel_rows // 2
    pad_width = kernel_cols // 2
    padded_image = np.zeros((image_rows + 2 * pad_height, image_cols + 2 * pad_width))
    padded_image[pad_height:padded_image.shape[0] - pad_height, pad_width:padded_image.shape[1] - pad_width] = image
    output_image = np.zeros_like(image)
    for i in range(image_rows):
        for j in range(image_cols):
            output_image[i, j] = np.sum(kernel * padded_image[i:i + kernel_rows, j:j + kernel_cols])
    return output_image


def nonmax_suppression(sobel, direction):
    rows, cols = sobel.shape
    suppressed = np.zeros_like(sobel)
    for i in range(1, rows - 1):
        for j in range(1, cols - 1):
            angle = direction[i, j] * 180.0 / np.pi
            if (0 <= angle < 22.5) or (157.5 <= angle <= 180):
                q, r = sobel[i, j + 1], sobel[i, j - 1]
            elif (22.5 <= angle < 67.5):
                q, r = sobel[i - 1, j + 1], sobel[i + 1, j - 1]
            elif (67.5 <= angle < 112.5):
                q, r = sobel[i - 1, j], sobel[i + 1, j]
            else:
                q, r = sobel[i + 1, j + 1], sobel[i - 1, j - 1]
            if sobel[i, j] >= q and sobel[i, j] >= r:
                suppressed[i, j] = sobel[i, j]
    return suppressed


def hysteresis_thresholding(suppressed, low_threshold, high_threshold):
    rows, cols = suppressed.shape
    edges = np.zeros_like(suppressed)
    for i in range(1, rows - 1):
        for j in range(1, cols - 1):
            if suppressed[i, j] >= high_threshold:
                edges[i, j] = 255
            elif low_threshold <= suppressed[i, j] < high_threshold:
                if (suppressed[i - 1:i + 2, j - 1:j + 2] >= high_threshold).any():
                    edges[i, j] = 255
    return edges

# 변수부
window, canvas, paper = None, None, None
inImage, outImage = [], []
inH, inW, outH, outW = [0] * 4

window = Tk()
window.resizable(width=False, height=False)
window.title("영상처리(GA 1)")
# 메뉴 만들기
mainMenu = Menu(window)
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='파일', menu=fileMenu)  # 펼쳐짐
fileMenu.add_command(label='열기', command=openImage)  # 실행됨
fileMenu.add_command(label='저장', command=saveImage)
fileMenu.add_separator()
fileMenu.add_command(label='종료', command=closeApp)

## 점 변환
pixelMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='화소 변환', menu=pixelMenu)  # 펼쳐짐
pixelMenu.add_command(label='원본', command=equalImage)  # 실행됨
pixelMenu.add_command(label='반전', command=reverseImage)
pixelMenu.add_command(label='포스터라이징', command=postImage)
pixelMenu.add_command(label='범위 강조', command=emphImage)
pixelMenu.add_command(label='감마 보정', command=gammaImage)
# 밝기 조절
addSubMenu = Menu(pixelMenu, tearoff=0)  # 하위 메뉴
pixelMenu.add_cascade(label='밝기 조절', menu=addSubMenu)  # 펼쳐짐
addSubMenu.add_command(label='밝게', command=lambda: addSubImage(0))
addSubMenu.add_command(label='어둡게', command=lambda: addSubImage(1))
# 이진화
binaryMenu = Menu(pixelMenu, tearoff=0)  # 하위 메뉴
pixelMenu.add_cascade(label='이진화', menu=binaryMenu)  # 펼쳐짐
binaryMenu.add_command(label='직접 입력', command=lambda: binaryImage(0))
binaryMenu.add_command(label='평균값으로', command=lambda: binaryImage(1))
binaryMenu.add_command(label='중앙값으로', command=lambda: binaryImage(2))
# 파라볼라 변환
paraMenu = Menu(pixelMenu, tearoff=0)  # 하위 메뉴
pixelMenu.add_cascade(label='파라볼라 변환', menu=paraMenu)
paraMenu.add_command(label='CAP(밝은 곳이 입체적으로)', command=lambda: paraImage(0))
paraMenu.add_command(label='CUP(어두운 곳이 입체적으로)', command=lambda: paraImage(1))

pixelMenu.add_separator()

pixelMenu.add_command(label='히스토그램 스트레칭', command=histoStretch)
pixelMenu.add_command(label='히스토그램 평활화', command=histoEqual)

pixelMenu.add_separator()

pixelMenu.add_command(label='모핑', command=morphImages)


## 기하 변환
geoMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='기하 변환', menu=geoMenu)
geoMenu.add_command(label='크기 조절', command=scaleImage)
geoMenu.add_command(label='회전', command=rotatImage)
geoMenu.add_command(label='이동', command=moveImage)
# 미러링
mirrorMenu = Menu(geoMenu, tearoff=0)  # 하위 메뉴
geoMenu.add_cascade(label='미러링(대칭)', menu=mirrorMenu)
mirrorMenu.add_command(label='상하 반전', command=lambda: mirrorImage(0))
mirrorMenu.add_command(label='좌우 반전', command=lambda: mirrorImage(1))

## 영역 변환
spaMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='영역 변환', menu=spaMenu)
# 엠보싱
embossMenu = Menu(spaMenu, tearoff=0)
spaMenu.add_cascade(label='엠보싱', menu=embossMenu)
embossMenu.add_command(label='3x3', command=lambda: emboss(0, 3))
embossMenu.add_command(label='5x5', command=lambda: emboss(0, 5))
embossMenu.add_command(label='7x7', command=lambda: emboss(0, 7))
embossMenu.add_command(label='9x9', command=lambda: emboss(0, 9))
# 블러링
blurMenu = Menu(spaMenu, tearoff=0)
spaMenu.add_cascade(label='블러링', menu=blurMenu)
blurMenu.add_command(label='3x3', command=lambda: emboss(1, 3))
blurMenu.add_command(label='5x5', command=lambda: emboss(1, 5))
blurMenu.add_command(label='7x7', command=lambda: emboss(1, 7))
blurMenu.add_command(label='9x9', command=lambda: emboss(1, 9))
# 스무딩
smoothMenu = Menu(spaMenu, tearoff=0)
spaMenu.add_cascade(label='스무딩', menu=smoothMenu)
smoothMenu.add_command(label='3x3', command=lambda: emboss(2, 3))
smoothMenu.add_command(label='5x5', command=lambda: emboss(2, 5))
smoothMenu.add_command(label='7x7', command=lambda: emboss(2, 7))
smoothMenu.add_command(label='9x9', command=lambda: emboss(2, 9))
# 샤프닝
sharpMenu = Menu(spaMenu, tearoff=0)
spaMenu.add_cascade(label='샤프닝', menu=sharpMenu)
sharpMenu.add_command(label='3x3', command=lambda: emboss(3, 3))
sharpMenu.add_command(label='5x5', command=lambda: emboss(3, 5))
sharpMenu.add_command(label='7x7', command=lambda: emboss(3, 7))
sharpMenu.add_command(label='9x9', command=lambda: emboss(3, 9))

spaMenu.add_separator()
# 에지 검출
edgeMenu = Menu(spaMenu, tearoff=0)
spaMenu.add_cascade(label='에지 검출', menu=edgeMenu)
# 소벨
sobelMenu = Menu(edgeMenu, tearoff=0)
edgeMenu.add_cascade(label='소벨', menu=sobelMenu)
sobelMenu.add_command(label='수평', command=lambda: edge(0, 0))
sobelMenu.add_command(label='수직', command=lambda: edge(0, 1))
# 프레윗
prewittMenu = Menu(edgeMenu, tearoff=0)
edgeMenu.add_cascade(label='프레윗', menu=prewittMenu)
prewittMenu.add_command(label='수평', command=lambda: edge(1, 0))
prewittMenu.add_command(label='수직', command=lambda: edge(1, 1))

edgeMenu.add_command(label='라플라시안', command=lambda: edge(2, None))
edgeMenu.add_command(label='LOG', command=lambda: edge(3, None))
edgeMenu.add_command(label='DOG', command=lambda: edge(4, None))
spaMenu.add_command(label='케니', command=canny)

window.mainloop()