import sys, math

t = int(sys.stdin.readline().rstrip())
for _ in range(t):
    n = int(sys.stdin.readline().rstrip())
    miners = []
    mines = []
    for _ in range(2 * n):
        loc = tuple(map(int, sys.stdin.readline().rstrip().split()))
        if loc[0] == 0:
            miners.append(abs(loc[1]))
        else:
            mines.append(abs(loc[0]))
    miners.sort()
    mines.sort()
    energy = 0
    for _ in range(n):
        miner = miners.pop()
        mine = mines.pop()
        energy += math.sqrt(miner ** 2 + mine ** 2)
    print(energy)
