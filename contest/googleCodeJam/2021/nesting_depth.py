from sys import stdin

t = int(stdin.readline().rstrip())

for i in range(1, t + 1):
    s = stdin.readline().rstrip()
    brackets = []
    prev = 0
    for j in range(len(s)):
        num = int(s[j])
        if prev < num:
            brackets.append("(" * (num - prev))
        else:
            brackets.append(")" * (prev - num))

        brackets.append(s[j])
        prev = num
    if prev > 0:
        brackets.append(")" * (prev))

    y = "".join(brackets)

    print(f"Case #{i}: {y}")