import sys

q = int(sys.stdin.readline())
for _ in range(q):
    n = int(sys.stdin.readline())
    factor2 = factor3 = factor5 = 0
    while n % 2 == 0:
        n //= 2
        factor2 += 1
    while n % 3 == 0:
        n //= 3
        factor3 += 1
    while n % 5 == 0:
        n //= 5
        factor5 += 1
    if n != 1:
        print("-1")
    else:
        print(factor5 + factor3 + 2 * factor5 + factor3 + factor2)
