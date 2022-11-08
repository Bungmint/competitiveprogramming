import sys, math


def sieve(num):
    A = [True for i in range(num + 1)]
    A[0], A[1] = False, False
    for i in range(2, 1 + int(math.sqrt(num))):
        if A[i]:
            for j in range(i ** 2, num + 1, i):
                A[j] = False
    return set([i ** 2 for i in range(num + 1) if A[i]])


n = int(sys.stdin.readline().rstrip())
ls = list(map(int, sys.stdin.readline().rstrip().split()))
prime_ls = sieve(int(math.sqrt(max(ls))))
for x in ls:
    if x in prime_ls:
        print("YES")
    else:
        print("NO")
