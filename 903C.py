import sys

n = int(sys.stdin.readline())
ls = list(map(int, sys.stdin.readline().split()))
count_dict = {}
for i in ls:
    count_dict.setdefault(i, 0)
    count_dict[i] += 1
ls1 = sorted([(k, v) for k, v in count_dict.items()], key=lambda x: x[1])
print(ls1[-1][1])