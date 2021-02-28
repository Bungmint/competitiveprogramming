import sys

n = int(sys.stdin.readline())
string = sys.stdin.readline()

prev = None
counter = 0
for i in list(string):
    if i != prev:
        counter += 1
    prev = i
print(len(string) - counter)
