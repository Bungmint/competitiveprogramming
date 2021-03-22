import sys
from math import gcd
from collections import deque

t = int(sys.stdin.readline().rstrip())

for _ in range(t):
    n = int(sys.stdin.readline().rstrip())
    genre = list(map(int, sys.stdin.readline().rstrip().split()))
    genre_wit_pos = [(i + 1, genre[i]) for i in range(n)]
    gcds = [gcd(genre[i], genre[(i + 1) % n]) for i in range(n)]
    trashed = []
    for i in range(n):
        if gcds[i] == 1:
            trashed.append(genre_wit_pos[(i + 1) % n][0])
            gcds[(i + 1) % n] = 0
    if not trashed:
        print(0)
        continue
    deq = deque()
    for i in range(n):
        if gcds[(i + 1) % n] == 0 and gcds[i]:
            deq.append((i, (i + 1) % n))
    while len(deq) > 0:
        deleter, deleted = deq.popleft()
        if gcds[deleter] == 0:
            continue
        while gcds[deleted] == 0:
            deleted = (deleted + 1) % n
        if gcd(genre[deleter], genre[deleted]) == 1:
            deq.append((deleter, deleted))
            gcds[deleted] = 0
            trashed.append(genre_wit_pos[deleted][0])
    print(len(trashed), " ".join([str(i) for i in trashed]))
