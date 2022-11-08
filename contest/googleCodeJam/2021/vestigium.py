from sys import stdin, stdout
from collections import defaultdict

t = int(stdin.readline().rstrip())

for i in range(1, t + 1):
    n = int(stdin.readline().rstrip())
    k = r = c = 0
    row_dic = defaultdict(set)
    col_dic = defaultdict(set)

    for j in range(n):
        ls = list(map(int, stdin.readline().rstrip().split()))
        k += ls[j]
        for l in range(n):
            val = ls[l]
            if val in row_dic[j] and -1 not in row_dic[j]:
                r += 1
                row_dic[j].add(-1)
            if val in col_dic[l] and -1 not in col_dic[l]:
                c += 1
                col_dic[l].add(-1)
            row_dic[j].add(val)
            col_dic[l].add(val)
    print(f"Case #{i}: {k} {r} {c}")