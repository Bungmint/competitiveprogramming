import sys

n = int(sys.stdin.readline())
point_dict = {}
ls = []
possible_winners = []

for _ in range(n):
    name, points = sys.stdin.readline().split()
    points = int(points)
    ls.append((name, points))
    point_dict.setdefault(name, 0)
    point_dict[name] += points


max_point = max(point_dict.values())
for k, v in point_dict.items():
    if v == max_point:
        possible_winners.append(k)
point_dict.clear()

for i in ls:
    name, points = i
    point_dict.setdefault(name, 0)
    point_dict[name] += points
    if point_dict[name] >= max_point and name in possible_winners:
        print(name)
        break
