import sys

n = int(sys.stdin.readline().rstrip())

if n > 0:
    print(n)
else:
    if len(str(n)) == 1:
        print(0)
    else:
        a, b = int(str(n)[:-1]), int(str(n)[:-2] + str(n)[-1])
        print(max(a, b))
