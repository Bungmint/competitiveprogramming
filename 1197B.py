import sys


def is_valid(ls):
    n = len(ls)
    k = ls.index(n)
    prev = 0
    for i in range(n):
        if i < k:
            if prev > ls[i]:
                return False
        if i > k:
            if prev < ls[i]:
                return False
        prev = ls[i]
    return True


n = int(sys.stdin.readline())
disk_ls = [int(i) for i in sys.stdin.readline().split()]
if is_valid(disk_ls):
    print("YES")
else:
    print("NO")
