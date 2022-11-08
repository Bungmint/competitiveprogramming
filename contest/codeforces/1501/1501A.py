import sys, math

t = int(sys.stdin.readline().rstrip())

for _ in range(t):
    n = int(sys.stdin.readline().rstrip())
    exp_arr = []
    exp_depart = []
    total_time = 0

    for _ in range(n):
        a, b = [int(i) for i in sys.stdin.readline().rstrip().split()]
        exp_arr.append(a)
        exp_depart.append(b)

    between = [int(i) for i in sys.stdin.readline().rstrip().split()]

    for i in range(n):
        if i == 0:
            total_time += exp_arr[i] + between[i]
        else:
            total_time += exp_arr[i] + between[i] - exp_depart[i - 1]
        if i != n - 1:
            total_time += max(
                exp_depart[i] - total_time, math.ceil((exp_depart[i] - exp_arr[i]) / 2)
            )
    print(total_time)