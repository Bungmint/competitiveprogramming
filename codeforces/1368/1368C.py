import sys


def recur_draw(n):
    if n == 1:
        print(0, 0)
        print(1, 0)
        print(0, 1)
        print(1, 1)
        print(2, 1)
        print(1, 2)
        print(2, 2)
    else:
        recur_draw(n - 1)
        print(n + 1, n)
        print(n, n + 1)
        print(n + 1, n + 1)


n = int(sys.stdin.readline())
print(7 + (n - 1) * 3)
recur_draw(n)
