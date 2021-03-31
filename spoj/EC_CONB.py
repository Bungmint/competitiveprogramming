from sys import stdin, stdout

n = int(stdin.readline().rstrip())
for _ in range(n):
    a = int(stdin.readline().rstrip())
    if a % 2 == 0:
        binary = bin(a)[2:][::-1]
        print(int(binary, 2))
    else:
        print(a)