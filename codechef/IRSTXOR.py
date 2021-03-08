import sys


def one_pos(num):
    s = bin(num)[2:]
    return [len(s) - i - 1 for i in range(len(s)) if s[i] == "1"]


def zero_pos(num):
    s = bin(num)[2:]
    return [len(s) - i - 1 for i in range(len(s)) if s[i] == "0"]


t = int(sys.stdin.readline().rstrip())

for _ in range(t):
    c = int(sys.stdin.readline().rstrip())
    a = b = 0
    ones = one_pos(c)
    for i in zero_pos(c):
        a += 2 ** i
        b += 2 ** i
    for j in range(len(ones)):
        if j == 0:
            a += 2 ** ones[j]
        else:
            b += 2 ** ones[j]
    print(a * b)
