import sys, math


t = int(sys.stdin.readline())
for _ in range(t):
    n, k = list(map(int, sys.stdin.readline().rstrip().split()))
    prev = 0
    for i in range(1, 1 + int(math.sqrt(n))):
        if n % i == 0:
            if n // i <= k and prev < n // i:
                prev = n // i
            else:
                if k >= i and i > prev:
                    prev = i
    print(n // prev)
