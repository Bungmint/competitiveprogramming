import sys, math


def mex(seq):
    for i in range(len(seq)):
        if seq[i] != i:
            return i
    return len(seq)


t = int(sys.stdin.readline().rstrip())
for _ in range(t):
    n, k = list(map(int, sys.stdin.readline().rstrip().split()))
    multiset = set(map(int, sys.stdin.readline().rstrip().split()))
    ls = list(multiset)
    ls.sort()
    maximum = max(multiset)
    meximum = mex(ls)
    counter = 0
    if k == 0:
        counter = 0
    else:
        if maximum > meximum:
            new = math.ceil((maximum + meximum) / 2)
            if new not in multiset:
                counter += 1
        else:
            counter = k
    print(n + counter)
