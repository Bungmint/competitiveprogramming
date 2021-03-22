import sys


def good(t):
    if l <= t <= r:
        return 1
    return 0


n, h, l, r = list(map(int, sys.stdin.readline().rstrip().split()))
arr = list(map(int, sys.stdin.readline().rstrip().split()))
dp = [[0] * h for _ in range(n + 1)]
for i in range(n - 1, -1, -1):
    for j in range(h):
        t1 = (j + arr[i]) % h
        t2 = (j + arr[i] - 1) % h
        dp[i][j] = max(good(t1) + dp[i + 1][t1], good(t2) + dp[i + 1][t2])
print(dp[0][0])
