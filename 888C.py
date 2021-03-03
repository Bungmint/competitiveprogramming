import sys
from collections import Counter


def max_d(string, alpha, occur):
    if occur == 1:
        return len(string) // 2 + 1
    prev = -1
    max_d = 0
    for index, i in enumerate(s):
        if i == alpha:
            if index - prev > max_d:
                max_d = index - prev
            prev = index
    return max(max_d, len(s) - prev)


s = sys.stdin.readline().rstrip()
c = Counter(s)
print(min(max_d(s, k, v) for k, v in c.items()))
