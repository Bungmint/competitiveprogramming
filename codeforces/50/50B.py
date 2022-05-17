import sys
from collections import Counter

s = sys.stdin.readline().rstrip()
c = Counter(s)
print(sum([i ** 2 for i in c.values()]))
