import sys


def is_valid(n, k, s):
    if k == 0:
        return "YES"
    elif k == n // 2 and n % 2 == 0:
        return "NO"
    else:
        for i in range(k):
            if s[i] != s[-i - 1]:
                return "NO"
        return "YES"


t = int(sys.stdin.readline().rstrip())
for _ in range(t):
    n, k = list(map(int, sys.stdin.readline().rstrip().split()))
    s = sys.stdin.readline().rstrip()
    print(is_valid(n, k, s))
