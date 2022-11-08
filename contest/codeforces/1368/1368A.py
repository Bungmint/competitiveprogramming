import sys

t = int(sys.stdin.readline())
for _ in range(t):
    a, b, n = [int(i) for i in sys.stdin.readline().split()]
    counter = 0
    while max(a, b) <= n:
        if a <= b:
            a, b = a + b, b
        else:
            a, b = a, a + b
        counter += 1
    print(counter)