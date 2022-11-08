import sys

n = int(sys.stdin.readline())
x = 0
for _ in range(n):
    statement = sys.stdin.readline()
    if "--" in statement:
        x -= 1
    else:
        x += 1
print(x)