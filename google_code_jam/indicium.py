from sys import stdin

t = int(stdin.readline().rstrip())

for x in range(1, t + 1):
    n, k = list(map(int, stdin.readline().rstrip().split()))
    is_possible = True
    if k == n + 1 or k == n ** 2 - 1 or (n == 3 and k in (5, 7)):
        is_possible = False

    if is_possible:
        y = "POSSIBLE"
    else:
        y = "IMPOSSIBLE"

    print(f"Case #{x}: {y}")

    if is_possible:
        a, b = divmod(k, n)
        if b == 0:
            arr = list([str(i) for i in range(1, n + 1)])
            for i in range(n):
                print(" ".join(arr[a - 1 + i :] + arr[: a - 1 + i]))
        elif b == 1:
            pass
        elif b == n - 1:
            pass
        else:
            for i in range(n - b - 1):
                arr = list([str(i) for i in range(1, n + 1)])
                print(" ".join(arr[(a - 1 - i) % n :] + arr[: (a - 1 - i) % n]))

            for i in range(b - 1):
                arr = list([str(i) for i in range(1, n + 1)])
                print(" ".join(arr[(a + b - 1 + i) % n :] + arr[: (a + b - 1 + i) % n]))
