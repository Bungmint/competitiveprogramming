import sys

n = int(sys.stdin.readline().rstrip())

print(n // 2)
if n % 2 == 0:
    print(" ".join(["2" for _ in range(n // 2)]))
else:
    print(" ".join(["2" for _ in range(n // 2 - 1)]) + " 3")
