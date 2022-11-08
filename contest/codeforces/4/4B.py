import sys
from collections import deque

d, sumTime = list(map(int, sys.stdin.readline().split()))
L = []
time_ls = []
sum_time_ls = 0
for _ in range(d):
    minTime, maxTime = list(map(int, sys.stdin.readline().split()))
    L.append((minTime, maxTime))
totalminTime = sum([i[0] for i in L])
totalmaxTime = sum([i[1] for i in L])
if totalmaxTime < sumTime or totalminTime > sumTime:
    print("NO")
else:
    for i in L:
        minTime, maxTime = i
        t = min(maxTime, sumTime + minTime - sum_time_ls - totalminTime)
        time_ls.append(t)
        totalmaxTime -= maxTime
        totalminTime -= minTime
        sum_time_ls += t

    print("YES")
    print(" ".join([str(i) for i in time_ls]))
