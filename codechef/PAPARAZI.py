import sys, math
from decimal import Decimal


t = int(sys.stdin.readline().rstrip())
for _ in range(t):
    n = int(sys.stdin.readline().rstrip())
    ls = list(map(int, sys.stdin.readline().rstrip().split()))
    diff = [((i, i + 1), ls[i + 1] - ls[i]) for i in range(n - 1)]
    group = []
    while True:
        i = 0
        while i < len(diff):
            has_change = False
            first_start, first_end, first_grad = (
                Decimal(str(diff[i][0][0])),
                Decimal(str(diff[i][0][1])),
                Decimal(str(diff[i][1])),
            )
            next_end, next_grad = first_end, first_grad
            while round(next_grad, 9) >= round(first_grad, 9) and i < len(diff):
                has_change = True
                first_grad = (
                    first_grad * (first_end - first_start)
                    + next_grad * (next_end - first_end)
                ) / (next_end - first_start)
                first_end = next_end
                if i == len(diff) - 1:
                    i += 1
                    break
                i += 1
                next_end, next_grad = diff[i][0][1], diff[i][1]
            group.append(((first_start, first_end), first_grad))
            if not has_change:
                i += 1
        diff_len = len(diff)
        diff.clear()
        i = 0
        while i < len(group):
            has_change = False
            first_start, first_end, first_grad = (
                Decimal(str(group[i][0][0])),
                Decimal(str(group[i][0][1])),
                Decimal(str(group[i][1])),
            )
            next_end, next_grad = first_end, first_grad
            while round(next_grad, 9) >= round(first_grad, 9) and i < len(group):
                has_change = True
                first_grad = (
                    first_grad * (first_end - first_start)
                    + next_grad * (next_end - first_end)
                ) / (next_end - first_start)
                first_end = next_end
                if i == len(group) - 1:
                    i += 1
                    break
                i += 1
                next_end, next_grad = group[i][0][1], group[i][1]
            diff.append(((first_start, first_end), first_grad))
        if diff_len == len(group):
            break
        group.clear()
    max_interval = 0
    for i in diff:
        if i[0][1] - i[0][0] > max_interval:
            max_interval = i[0][1] - i[0][0]
    print(max_interval)