import sys

t = int(sys.stdin.readline().rstrip())

for _ in range(t):
    s = sys.stdin.readline().rstrip()
    d = 0
    prev = 0
    for i in range(len(s)):
        if s[i] == "R":
            if i + 1 - prev > d:
                d = i + 1 - prev
            prev = i + 1
    if d == 0:
        print(len(s) + 1)
    else:
        if len(s) + 1 > d + prev:
            d = len(s) + 1 - prev
        print(d)