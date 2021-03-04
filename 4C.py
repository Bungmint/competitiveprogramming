import sys

n = int(sys.stdin.readline().rstrip())
name_dict = {}
for _ in range(n):
    s = sys.stdin.readline().rstrip()
    if s in name_dict:
        s1 = f"{s}{name_dict[s]}"
        print(s1)
        name_dict[s] += 1
        name_dict[s1] = 1
    else:
        print("OK")
        name_dict[s] = 1