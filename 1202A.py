import sys

T = int(sys.stdin.readline())
for _ in range(T):
    x = sys.stdin.readline().rstrip()
    y = sys.stdin.readline().rstrip()
    x, y = x[::-1], y[::-1]
    pos_y = y.find("1")
    pos_x = x.find("1", pos_y)
    print(pos_x - pos_y)
