import sys


def does_exist(s):
    f, l = s[0], s[-1]
    m = [i for i in ["A", "B", "C"] if (i != f and i != l)][0]
    if f == l:
        return "NO"
    else:
        a = s.count(f)
        b = s.count(l)
        c = s.count(m)
        if a != b + c and b != c + a:
            return "NO"
        else:
            ls = [0, 0, 0]
            if a == b + c:
                for i in range(len(s)):
                    if s[i] == f:
                        ls[0] += 1
                    elif s[i] == l:
                        ls[1] += 1
                    else:
                        ls[2] += 1
                    if ls[0] < ls[1] + ls[2]:
                        return "NO"

            else:
                for i in range(len(s)):
                    if s[i] == f:
                        ls[0] += 1
                    elif s[i] == l:
                        ls[1] += 1
                    else:
                        ls[2] += 1
                    if ls[1] > ls[0] + ls[2]:
                        return "NO"
        return "YES"


t = int(sys.stdin.readline())
for _ in range(t):
    s = sys.stdin.readline().rstrip()
    print(does_exist(s))