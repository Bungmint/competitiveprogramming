import sys

n = int(sys.stdin.readline().rstrip())


def sieve(num):
    A = [True for i in range(num + 1)]
    A[0], A[1] = False, False

    for i in range(len(A)):
        if A[i]:
            for j in range(i ** 2, num + 1, i):
                A[j] = False

    return [i for i in range(num + 1) if A[i]]


if n == 1:
    print(0)
else:
    primes = sieve(n // 2)
    counter = 0
    for i in range(1, n + 1):
        num = 0
        for j in primes:
            if i % j == 0:
                num += 1
        if num == 2:
            counter += 1
    print(counter)