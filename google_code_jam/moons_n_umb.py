from sys import stdin

t = int(stdin.readline().rstrip())

for x in range(1, t + 1):
    ls = stdin.readline().rstrip().split()
    a, b, s = int(ls[0]), int(ls[1]), list(ls[2])
    cj_neg = False
    jc_neg = False
    if not cj_neg and not jc_neg:
        cost = 0
        prev = s[0]
        for i in range(len(s)):
            cur = s[i]
            if prev == "C" and cur == "J":
                cost += a
            elif prev == "J" and cur == "C":
                cost += b
            if cur == "?":
                s[i] = prev

            prev = s[i]

    elif cj_neg and jc_neg:
        pass
    elif cj_neg:
        pass
    elif jc_neg:
        pass
    print(f"Case #{x}: {cost}")