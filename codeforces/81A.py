import sys
from collections import deque

s = sys.stdin.readline().rstrip()
ls = list(s)
stack = deque()


for i in s:
    if len(stack) == 0:
        stack.append(i)
    else:
        if stack[-1] != i:
            stack.append(i)
        else:
            stack.pop()
print("".join(stack))