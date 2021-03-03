import sys

t = int(sys.stdin.readline())
for _ in range(t):
    x, y, n = tuple(map(int, sys.stdin.readline().split()))
    a = (n - y) // x
    k = a * x + y
    print(k)
