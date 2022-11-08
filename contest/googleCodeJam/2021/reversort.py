from sys import stdin

t = int(stdin.readline().rstrip())

for x in range(1, t + 1):
    n = int(stdin.readline().rstrip())
    arr = list(map(int, stdin.readline().rstrip().split()))
    indexes = [None] * n
    for i in range(n):
        indexes[arr[i] - 1] = i
    y = 0

    for i in range(n - 1):
        j = indexes[i]
        for k in range(i, i + (j - i + 1) // 2):
            indexes[arr[k] - 1], indexes[arr[j - k + i] - 1], arr[k], arr[j - k + i] = (
                indexes[arr[j - k + i] - 1],
                indexes[arr[k] - 1],
                arr[j - k + i],
                arr[k],
            )
        y += j - i + 1

    print(f"Case #{x}: {y}")
