import sys


def is_sorted(arr):
    prev = 0
    for i in arr:
        if i < prev:
            return False
        prev = i
    return True


t = int(sys.stdin.readline().rstrip())
for _ in range(t):
    n = int(sys.stdin.readline().rstrip())
    arr = list(map(int, sys.stdin.readline().rstrip().split()))
    if is_sorted(arr):
        print(0)
        continue
    prev = cur = n - 1
    while arr[cur] - arr[prev] >= 0 and cur >= 0:
        prev = cur
        cur -= 1
    if prev == 0:
        print(0)
        continue
    else:
        while arr[cur] - arr[prev] <= 0 and cur >= 0:
            prev = cur
            cur -= 1
        print(prev)
