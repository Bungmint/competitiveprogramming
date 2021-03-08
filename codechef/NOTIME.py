import sys

N, H, x = list(map(int, sys.stdin.readline().rstrip().split()))
time_ls = [int(i.rstrip()) for i in sys.stdin.readline().rstrip().split()]
max_timetravel = max(time_ls)
if max_timetravel + x >= H:
    print("YES")
else:
    print("NO")