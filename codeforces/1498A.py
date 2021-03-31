from sys import stdin
from math import gcd


def gcd_sum(x):
    s = [int(i) for i in list(str(x))]
    return gcd(x, sum(s))


t = int(stdin.readline().rstrip())

for _ in range(t):
    n = int(stdin.readline().rstrip())
    a, b = divmod(n, 3)

    if b == 0:
        print(n)
    elif b == 1:
        if gcd_sum(n) != 1:
            print(n)
        elif gcd_sum(n + 1) != 1:
            print(n + 1)
        else:
            print(n + 2)
    else:
        if gcd_sum(n) != 1:
            print(n)
        else:
            print(n + 1)
