# # 4의 배수 구하기
# sum = 0
# for i in range(1,100):
#     if i % 4 == 0:
#         sum += i
#
# # 소수 구하기
# def is_prime(n):
#     if n <= 1:
#         return False
#     for i in range(2, int(n**0.5) + 1):
#         if n % i == 0:
#             return False
#     return True
#
# result = 0
# for i in range(2, 1001):
#     if is_prime(i):
#         result += i
#         print(i)
#
# print(result)
#
# # 리스트
# ary = []
# for _ in range(10):
#     ary.append(0)
#
# ary = [0 for _ in range(10)]
# print(ary)
#
# # 리스트 응용
# ary = []
# for _ in range(100):
#     r = random.randint(0,10000)
#     ary.append(r)
#
# print(ary)
#
# maxVal, minVal, sumVal, avgVal = [0]*4
#
# # 함수 사용
# maxVal = max(ary)
# print(maxVal)
# minVal = min(ary)
# print(minVal)
# sumVal = np.sum(ary)
# print(sumVal)
# avgVal = np.mean(ary)
# print(avgVal)
#
# # 계산
# maxVal = minVal = ary[0]
# for i in range(len(ary)):
#     if maxVal > ary[i]:
#         maxVal = ary[i]
#     if minVal < ary[i]:
#         minVal = arr[i]
#     sumVal += ary[i]
#
# avgVal = sumVal / len(ary)
import numpy as np

# 2차원 리스트
image = [[0, 0, 0, 0],
         [0, 0, 0, 0],
         [0, 0, 0, 0]]
image[0][0] = 100
image[2][3] = 100
print(image)

# 가변 배열
height, width = 3, 4
image = []
# 계산
for _ in range(height):
    tmp = []
    for _ in range(width):
        tmp.append(0)
    image.append(tmp)
# List comprehension
image2 = [[0 for _ in range(width)] for _ in range(height)]
# 함수 사용
image3 = np.zeros((3, 4))
