import sys

n = int(sys.stdin.readline())
s = sys.stdin.readline().rstrip()
u, r, d, l = s.count("U"), s.count("R"), s.count("D"), s.count("L")
print(n - (abs(u - d) + abs(r - l)))
