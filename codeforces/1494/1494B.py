import sys


t = int(sys.stdin.readline())
for i in range(t):
    n, u, r, d, l = list(map(int, sys.stdin.readline().split()))
    u1, r1, d1, l1 = u, r, d, l
    is_true = None
    for i in range(2):
        for j in range(2):
            for k in range(2):
                for m in range(2):
                    u -= i + j
                    r -= j + k
                    d -= k + m
                    l -= m + i
                    if all([(i >= 0 and i <= n - 2) for i in (u, r, d, l)]):
                        is_true = True
                    u, r, d, l = u1, r1, d1, l1
    if is_true:
        print("YES")
    else:
        print("NO")
