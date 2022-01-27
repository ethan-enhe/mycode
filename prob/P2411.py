#!/usr/bin/env python3
from decimal import Decimal, getcontext
getcontext().prec = 50

def main():
    n = int(input())
    if n == 1:
        print(1)
    elif n == 2:
        print(5)
    else: # 生成基尔霍夫矩阵A
        A = [[Decimal(3 * int(i == j) - int(j == (i-1+n)%n or j == (i+1+n) % n)) \
             for j in range(n)] for i in range(n)]
        for i in range(n): # 高斯消元
            r = i
            for j in range(i+1, n):
                if abs(A[j][i]) > abs(A[r][i]):
                    r = j
            if r != i:
                A[r], A[i] = A[i], A[r]
            for t in range(i+1, n):
                k = A[t][i] / A[i][i]
                for j in range(n):
                    A[t][j] -= A[i][j] * k
        Ans = Decimal('1')
        for i in range(n):
            Ans *= A[i][i]
        print("{:.0f}".format(Ans))
if __name__ == '__main__':
    main()
