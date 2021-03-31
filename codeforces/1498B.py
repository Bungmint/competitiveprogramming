from sys import stdin
from math import log2, ceil
from collections import Counter


def convert_num_to_bin(x):
    string = bin(x)[2:]
    return [i for i in range(len(string)) if string[-1 - i] == "1"]


t = int(stdin.readline().rstrip())

for _ in range(t):
    n, w = list(map(int, stdin.readline().rstrip().split()))
    w_arr = [int(log2(int(i))) for i in stdin.readline().rstrip().split()]
    count = Counter(w_arr)

    height = 0
    while n > 0:
        w1 = w
        i = max(count.keys())
        while w1 > 0 and i >= 0:
            bonk = min(w1 // pow(2, i), count[i])
            w1 -= bonk * pow(2, i)
            count[i] -= bonk
            i -= 1
            n -= bonk
        height += 1
    print(height)
