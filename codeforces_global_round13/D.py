import sys
import math


def is_true(a, b):
    if a == b:
        return True
    elif a > b:
        return False
    else:
        return any(is_true(a + k, b) for k in range(1, a + 1) if a & k == k)


n = 5
m = 15
print(is_true(n, m), n & m, n ^ m, n | m)
# q = int(sys.stdin.readline())


# for _ in range(q):
#     u, v = list(map(int, sys.stdin.readline().split()))
#     if v > u:
#         v = int(str(bin(v))[2:].rstrip("0"), base=2)
#         while v < u:
#             v << 1
#     if is_true(u, v):
#         print("YES")
#     else:
#         print("NO")