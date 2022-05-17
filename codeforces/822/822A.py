import sys, math

a, b = list(map(int, sys.stdin.readline().rstrip().split()))
print(math.factorial(min(a, b)))
