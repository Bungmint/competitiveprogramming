from sys import stdin
from math import sqrt, floor


def cheap_func(cost, n):
    return cost > n * (n - 1) // 2 - 1


def array_gen():
    cost = c - 1
    start_val = 1
    start_point, end_point = 0, n - 1
    ls = [None] * n
    has_reversed = False
    while start_val < n + 1:
        if cheap_func(cost, end_point - start_point + 1):
            cost -= end_point - start_point + 1
            if has_reversed:
                ls[start_point] = start_val
                start_point += 1
            else:
                ls[end_point] = start_val
                end_point -= 1
            start_val += 1

            has_reversed = not has_reversed
        else:
            if has_reversed:
                ls[end_point] = start_val
                end_point -= 1
            else:
                ls[start_point] = start_val
                start_point += 1
            start_val += 1
            cost -= 1

    return [str(i) for i in ls]


t = int(stdin.readline().rstrip())

for x in range(1, t + 1):
    n, c = list(map(int, stdin.readline().rstrip().split()))
    is_possible = (n - 1 <= c) and (c <= n * (n + 1) // 2 - 1)

    if is_possible:
        y = " ".join(array_gen())
    else:
        y = "IMPOSSIBLE"

    print(f"Case #{x}: {y}")