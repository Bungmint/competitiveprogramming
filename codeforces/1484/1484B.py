import sys, math

t = int(sys.stdin.readline().rstrip())
for _ in range(t):
    n = int(sys.stdin.readline().rstrip())
    arr = list(map(int, sys.stdin.readline().rstrip().split()))
    diff = []
    for i in range(1, n):
        diff.append(arr[i] - arr[i - 1])
    prev = None
    biggest_m = 0
    for i in diff:
        if prev is None:
            prev = i
            continue
        if abs(i - prev) != biggest_m:
            biggest_m = math.gcd(biggest_m, abs(i - prev))
        if biggest_m == 0 and abs(prev - i) > 0:
            biggest_m = abs(prev - i)
        prev = i
    if biggest_m == 0:
        print(0)
    else:
        if biggest_m == 1:
            print(-1)
        else:
            is_valid = True
            for i in arr:
                if i >= biggest_m:
                    is_valid = False
            if is_valid:
                print(biggest_m, diff[0] % biggest_m)
            else:
                print(-1)
