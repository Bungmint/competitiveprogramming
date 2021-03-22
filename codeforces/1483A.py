import sys

t = int(sys.stdin.readline().rstrip())

for _ in range(t):
    n, m = list(map(int, sys.stdin.readline().rstrip().split()))
    LIMIT = (m + 1) // 2
    avail_friends = {}
    days = set(range(m))
    ans_dict = {k: None for k in range(m)}
    occur = [0] * n
    is_incomplete = False

    for day in range(m):
        line = sys.stdin.readline().rstrip()
        i = line.find(" ")
        arr = list(map(int, line[i + 1 :].rstrip().split()))
        if len(arr) == 1:
            ans_dict[day] = arr[0]
            occur[arr[0] - 1] += 1
            days.remove(day)
        else:
            for j in arr:
                avail_friends.setdefault(day, [])
                avail_friends[day].append(j)
    for i in occur:
        if i > LIMIT:
            is_incomplete = True
    if is_incomplete:
        print("NO")
    else:
        for i in days:
            option1 = avail_friends[i][0]
            option2 = avail_friends[i][1]
            if occur[option1 - 1] == LIMIT:
                ans_dict[i] = option2
                occur[option2 - 1] += 1
            else:
                ans_dict[i] = option1
                occur[option1 - 1] += 1
        print("YES")
        print(" ".join([str(i) for i in ans_dict.values()]))