import sys

fs, rs = list(sys.stdin.readline().rstrip())
fe, re = list(sys.stdin.readline().rstrip())
fs = ord(fs) - ord("a")
fe = ord(fe) - ord("a")
rs, re = int(rs), int(re)
d = max(abs(fs - fe), abs(rs - re))

print(d)
while re - rs != 0 and fe - fs != 0:
    if re > rs:
        if fe > fs:
            print("RU")
            rs += 1
            fs += 1
        else:
            print("LU")
            rs += 1
            fs -= 1
    else:
        if fe > fs:
            print("RD")
            rs -= 1
            fs += 1
        else:
            print("LD")
            rs -= 1
            fs -= 1

while re != rs or fe != fs:
    if re == rs:
        if fe > fs:
            print("R")
            fs += 1
        else:
            print("L")
            fs -= 1
    else:
        if re > rs:
            print("U")
            rs += 1
        else:
            print("D")
            rs -= 1
