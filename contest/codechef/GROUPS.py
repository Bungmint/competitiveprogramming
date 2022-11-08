import sys

t = int(sys.stdin.readline().rstrip())
for _ in range(t):
    s = sys.stdin.readline().rstrip()
    prev = "0"
    groups = 0
    for i in s:
        if prev == "0" and i == "1":
            groups += 1
        prev = i
    print(groups)