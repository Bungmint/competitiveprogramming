from sys import stdin
from collections import deque

t = int(stdin.readline().rstrip())

for x in range(1, t + 1):
    n = int(stdin.readline().rstrip())
    tasks = [None] * n
    c, j = deque(), deque()
    results = [None] * n
    for_c = True
    is_valid = True
    for i in range(n):
        s, e = list(map(int, stdin.readline().rstrip().split()))
        tasks[i] = (s, e, i)
    tasks.sort()
    prev_c = prev_j = -1
    for k in tasks:
        s_j, e_j, i_j = k
        if prev_c <= s_j:
            for_c = True
        elif prev_j <= s_j:
            for_c = False
        else:
            is_valid = False
            break
        if for_c:
            c.append(i_j)
            prev_c = e_j
        else:
            j.append(i_j)
            prev_j = e_j
    if is_valid:
        for i in c:
            results[i] = "C"
        for k in j:
            results[k] = "J"
        y = "".join(results)
    else:
        y = "IMPOSSIBLE"

    print(f"Case #{x}: {y}")