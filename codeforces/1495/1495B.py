import sys

n = int(sys.stdin.readline().rstrip())
perms = list(map(int, sys.stdin.readline().rstrip().split()))
max_increase = 0
max_decrease = 0
ls = []
is_lost = False
i = 0

while i < n - 1:
    walk = i + 1
    if perms[walk] > perms[i]:
        while walk < n:
            if perms[walk] < perms[walk - 1]:
                break
            walk += 1
        walk -= 1
        if walk - i > max_increase:
            max_increase = walk - i
        ls.append((walk - i, 0))
    else:
        while walk < n:
            if perms[walk] > perms[walk - 1]:
                break
            walk += 1
        walk -= 1
        if walk - i > max_decrease:
            max_decrease = walk - i
        ls.append((walk - i, 1))
    i = walk

max_hike = max(max_increase, max_decrease)
count = 0
for i in range(len(ls)):
    if ls[i][0] == max_hike:
        count += 1
if count >= 3:
    is_lost = True
elif count == 2:
    for i in range(len(ls) - 1):
        if ls[i][0] == max_hike:
            if ls[i + 1][0] == max_hike and ls[i][1] == 0 and max_hike % 2 == 0:
                is_lost = False
                break
            else:
                is_lost = True
elif count == 1:
    is_lost = True


if not is_lost:
    print(1)
else:
    print(0)
