import sys


def calculate(seq, u, v):
    prev = None
    num = []
    counter = 0
    for i in seq:
        if prev:
            if abs(prev - i) >= 2:
                return 0
            elif abs(prev - i) == 1:
                counter = 1
        prev = i
    if counter == 0:
        return min(u + v, 2 * v)
    else:
        return min(u, v)


t = int(sys.stdin.readline())

for _ in range(t):
    n, u, v = list(map(int, sys.stdin.readline().split()))
    obstacles = [int(i.strip()) for i in sys.stdin.readline().split()]
    print(calculate(obstacles, u, v))