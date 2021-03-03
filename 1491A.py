import sys


def k_largest_value(seq, k):
    num_one = sum(seq)
    if num_one >= k:
        return 1
    else:
        return 0


n, q = [int(i) for i in sys.stdin.readline().split()]
ls = [int(i.strip()) for i in sys.stdin.readline().split()]
total = sum(ls)
for _ in range(q):
    t, x = [int(i) for i in sys.stdin.readline().split()]
    if t == 1:
        if ls[x - 1] == 0:
            ls[x - 1] = 1
            total += 1
        else:
            ls[x - 1] = 0
            total -= 1
    else:
        if total >= x:
            print(1)
        else:
            print(0)
