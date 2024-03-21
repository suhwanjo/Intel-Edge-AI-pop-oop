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
def openImage():
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


def saveImage():
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


def displayImage():
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


# 영상 처리 함수
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


# 화소 점 처리
def addSubImage(option):
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


def reverseImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    arrayImage = np.array(inImage)  # 스칼라 값과의 연산을 위해 변환
    outImage = 255 - arrayImage

    displayImage()


def binaryImage(option):
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    if option == 0:
        val = askinteger("정수 입력", '-255~255 입력', maxvalue=255, minvalue=-255)
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


def gammaImage():
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


def paraImage(option):
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


def postImage():
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


def emphImage():
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


def histoStretch():
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


def histoEqual():
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


def scaleImage():
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
                subMat = inImage[i * scale:i * scale + scale][j * scale:j * scale + scale]  # 이미지를 축소할 영역 추출
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


def rotatImage():
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return

    angle = askinteger("회전 각도 입력", '정수 입력')
    tmp_angle = angle % 90 * 3.141592 / 180.0
    tmp_angle90 = (90 - angle % 90) * 3.141592 / 180.0
    outH = int(inH * np.cos(tmp_angle90) + inW * np.cos(tmp_angle))
    outW = int(inW * np.cos(tmp_angle) + inH * np.cos(tmp_angle90))
    outImage = malloc2D(outH, outW)
    degree = angle * 3.141592 / 180.0

    dx = (outW - inW) // 2
    dy = (outH - inH) // 2

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


def moveImage():
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


def mirrorImage(option):
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


def emboss(option):
    global window, canvas, paper
    global inImage, outImage, inH, inW, outH, outW
    if inImage is None:
        return
    outH = inH
    outW = inW
    outImage = malloc2D(outH, outW)

    if option == 0:  # 엠보싱
        maskSize = askinteger("효과 적용 정도 입력(홀수)", '정수 입력')
        mask = np.zeros((maskSize, maskSize), dtype=float)
        mask[0] = -1.0
        mask[-1] = 1.0
    elif option == 1:  # 블러링
        maskSize = askinteger("효과 적용 정도 입력(홀수)", '정수 입력')
        mask = np.zeros((maskSize, maskSize), dtype=float)
        mask = 1.0 / (maskSize * maskSize)
    elif option == 2:
        maskSize = askinteger("효과 적용 정도 입력(홀수)", '정수 입력')
        mask = np.zeros((maskSize, maskSize), dtype=float)
        center = maskSize // 2
        sigma = askfloat("마스크이 Sigma 값 입력", '소수 입력')

        for i in range(maskSize):
            for j in range(maskSize):
                # 가우시안 마스크 생성
                x = np.sqrt((np.power((i - center), 2) + np.power((j - center), 2)))
                gaussian = np.exp(-(x * x) / (2.0 * sigma * sigma)) / (sigma * np.sqrt(2.0 * np.pi))
                mask[i][j] = gaussian
    elif option == 3:
        maskSize = askinteger("효과 적용 정도 입력(홀수)", '정수 입력')
        mask = np.zeros((maskSize, maskSize), dtype=float)
        center = maskSize // 2
        mask = -1.0
        mask[center][center] = float(maskSize * maskSize)

    tmpImage = malloc2D(inH, inW, maskSize - 1)
    tmpImage[1:-2][1:-2] = inImage

    for i in range(outH):
        for j in range(outW):
            subMat = inImage[i * scale:i * scale + scale][j * scale:j * scale + scale]  # 이미지를 축소할 영역 추출
            sum = np.sum(subMat)

# 변수부
window, canvas, paper = None, None, None
inImage, outImage = [], []
inH, inW, outH, outW = [0] * 4

window = Tk()
window.resizable(width=False, height=False)
window.title("영상처리(Beta 1)")
# 메뉴 만들기
mainMenu = Menu(window)
window.config(menu=mainMenu)

fileMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='파일', menu=fileMenu)  # 펼쳐짐
fileMenu.add_command(label='열기', command=openImage)  # 실행됨
fileMenu.add_command(label='저장', command=saveImage)
fileMenu.add_separator()
fileMenu.add_command(label='종료', command=None)

## 점 변환
pixelMenu = Menu(mainMenu, tearoff=0)  # 상위 메뉴
mainMenu.add_cascade(label='화소 변환', menu=pixelMenu)  # 펼쳐짐
pixelMenu.add_command(label='원본', command=equalImage)  # 실행됨

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

pixelMenu.add_command(label='반전', command=reverseImage)
pixelMenu.add_command(label='감마 보정', command=gammaImage)

# 파라볼라 변환
paraMenu = Menu(pixelMenu, tearoff=0)  # 하위 메뉴
pixelMenu.add_cascade(label='파라볼라 변환', menu=paraMenu)
paraMenu.add_command(label='CAP(밝은 곳이 입체적으로)', command=lambda: paraImage(0))
paraMenu.add_command(label='CUP(어두운 곳이 입체적으로)', command=lambda: paraImage(1))

pixelMenu.add_command(label='포스터라이징', command=postImage)
pixelMenu.add_command(label='범위 강조', command=emphImage)
pixelMenu.add_separator()
pixelMenu.add_command(label='히스토그램 스트레칭', command=histoStretch)
pixelMenu.add_command(label='히스토그램 평활화', command=histoEqual)

## 기하 변환 (모핑 추가)
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
# spaMenu.add_command(label='엠보싱', command=lambda: emboss(0))
# spaMenu.add_command(label='블러링', command=lambda: emboss(1))
# spaMenu.add_command(label='스무딩', command=lambda: emboss(2))
# spaMenu.add_command(label='샤프닝', command=lambda: emboss(3))

edgeMenu = Menu(spaMenu, tearoff=0)
# spaMenu.add_command(label='에지 검출', menu=edgeMenu)
# edgeMenu.add_command(label='LOG', command=lambda: )
# edgeMenu.add_command(label='DOG', command=lambda: )







# 컨트롤 == 위젯
# label1 = Label(window, text='나는 글자다', font=('궁서체',20), fg='red', bg='yellow')
# button1 = Button(window, text='나를 클릭해줘~')



# label1.pack()
# button1.pack(side=BOTTOM)
window.mainloop()