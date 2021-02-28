import sys

n, k = list(map(int, sys.stdin.readline().split()))
for _ in range(k):
    if n % 10 != 0:
        n -= 1
    else:
        n //= 10
print(n)