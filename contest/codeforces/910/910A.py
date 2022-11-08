import sys


def is_possible(n, d, s):
    prev = 0
    lilypads = []
    for index in range(len(s)):
        if s[index] == "1":
            lilypads.append(index)
            if index - prev > d:
                return -1
            prev = index
    current = counter = 0
    while current < n - 1:
        current = max([i for i in lilypads if i <= current + d and i >= current])
        counter += 1
    return counter


n, d = list(map(int, sys.stdin.readline().split()))
s = str(sys.stdin.readline())
print(is_possible(n, d, s))
