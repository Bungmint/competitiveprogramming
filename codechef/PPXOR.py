import sys


def bin_one(num):
    s = bin(num)[2:]
    return set([(len(s) - i - 1) for i in range(len(s)) if s[i] == "1"])


t = int(sys.stdin.readline())

for _ in range(t):
    n = int(sys.stdin.readline())
    A = [int(i) for i in sys.stdin.readline().rstrip().split()]
    max_bin_len = len(bin(max(A))[2:])
    C = [0] * max_bin_len
    S = 0
    total_sum = 0
    for i in range(0, n):
        S ^= A[i]
        index_ones = bin_one(S)
        for j in range(len(C)):
            if j in index_ones:
                total_sum += (i + 1 - C[j]) * pow(2, j)
                C[j] += 1
            else:
                total_sum += C[j] * pow(2, j)

    print(total_sum)
