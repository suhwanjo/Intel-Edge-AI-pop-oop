# # 1단계 : 파일 열기
# rfp = open('c:/windows/win.ini', 'rt')
# wfp = open('win.txt', 'wt')
#
# # 2단계 : 파일 읽기/쓰기
# while True:
#     line = rfp.readline()
#     if line is None or line == '':
#         break
#     wfp.writelines(line)
#     for ch in line:
#         if '0' <= ch <= '9':
#             print('*', end='')
#         else:
#             print(ch, end='')
#
# # 3단계 : 파일 닫기
# rfp.close()
# wfp.close()

# 퀴즈 : win.ini를 읽어서 win2.txt에 쓰되
# (1) 각 행을 거꾸로 쓰기
# (2) 모든 열도 거꾸로 쓰기

# rfp = open('c:/windows/win.ini', 'rt')
# wfp = open('win2.txt', 'wt')
# reverseLine = ''
#
# while True:
#     line = rfp.readline()
#     if line is None or line == '':
#         break
#     for i in range(len(line)):
#         reverseLine += line[len(line)-1-i]
#     wfp.writelines(reverseLine)
# Open the win.ini file for reading
## 1단계 : 파일 열기
rfp = open('c:/windows/win.ini', 'rt')
wfp = open('win.txt', 'wt')

## 2단계 : 파일 읽기/쓰기
newTxt = ''
while(True) :
    line = rfp.readline()
    reverseLine = ''
    if (line == None or line == '') : # None == NULL
        break
    for ch in line :
        reverseLine = ch + reverseLine
    newTxt = reverseLine + newTxt

wfp.write(newTxt)

## 3단계 : 파일 닫기
rfp.close()
wfp.close()

