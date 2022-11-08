import sys

n = int(sys.stdin.readline())
ls = list(map(int, sys.stdin.readline().rstrip().split()))
cafe_set = set(ls)
for i in range(n):
    if len(cafe_set) == 1:
        print(cafe_set.pop())
        break
    if ls[-i - 1] in cafe_set:
        cafe_set.remove(ls[-i - 1])
