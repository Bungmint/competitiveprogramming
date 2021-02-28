import sys

a, b = list(map(int, sys.stdin.readline().split()))
counter = 0
while a <= b:
    a *= 3
    b *= 2
    counter += 1
print(counter)