import sys


def min_pass(seq):
    return


t = int(sys.stdin.readline())
for _ in range(t):
    n = int(sys.stdin.readline())
    tramp_strength = [int(i.strip()) for i in sys.stdin.readline().split()]
    print(min_pass(tramp_strength))