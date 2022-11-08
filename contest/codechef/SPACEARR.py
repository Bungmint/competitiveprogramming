import sys
from collections import Counter


def winner(arr):
    for i in range(len(arr)):
        if arr[i] > i + 1:
            return "Second"
    if (len(arr) * (len(arr) + 1) / 2 - sum(arr)) % 2 == 0:
        return "Second"
    else:
        return "First"


t = int(sys.stdin.readline().rstrip())

for _ in range(t):
    n = int(sys.stdin.readline().rstrip())
    arr = list(map(int, sys.stdin.readline().rstrip().split()))
    arr.sort()

    print(winner(arr))
