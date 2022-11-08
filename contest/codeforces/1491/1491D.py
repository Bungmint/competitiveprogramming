import sys
import math


def is_true(a, b):
    if a > b:
        return False
    else:
        while b > 0:
            if lsb(b) < lsb(a) or a == 0:
                return False
            a -= lsb(a)
            b -= lsb(b)
        return True


def lsb(num):
    return num & (-num)


q = int(sys.stdin.readline())


for _ in range(q):
    u, v = list(map(int, sys.stdin.readline().split()))
    if is_true(u, v):
        print("YES")
    else:
        print("NO")