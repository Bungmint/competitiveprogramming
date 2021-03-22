import sys


def power_2(n):
    counter = 0
    while n % 2 == 0:
        n = n // 2
        counter += 1
    return counter


def power_5(n):
    counter = 0
    while n % 5 == 0:
        n = n // 5
        counter += 1
    return counter


def nav(i, j):
    s = []
    while i != n - 1 or j != n - 1:
        cur = mat2[i][j][0]
        if cur == 0:
            i += 1
            s.append("D")
        else:
            j += 1
            s.append("R")
    return "".join(s)


n = int(sys.stdin.readline())
matrix = [[None] * 1001 for _ in range(1001)]
is_zero = False
z_i, z_j = None, None
for i in range(n):
    arr = list(map(int, sys.stdin.readline().split()))
    for j in range(len(arr)):
        if arr[j] == 0:
            is_zero = True
            z_i = i
            z_j = j
            arr[j] = 10
        matrix[i][j] = arr[j]
arr.clear()


if is_zero and matrix[0][0] % 10 == 0:
    print(1)
    print("R" * z_j + "D" * z_i + "R" * (n - 1 - z_j) + "D" * (n - 1 - z_i))
else:
    mat2 = [[None] * 1001 for i in range(1001)]
    for i in range(n + 1):
        mat2[i][n] = (-1, float("inf"))
        mat2[n][i] = (-1, float("inf"))
    if is_zero:
        mat2[n - 1][n - 1] = (-1, power_2(matrix[n - 1][n - 1]))

        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if i == j == n - 1:
                    continue
                cur_num = min(mat2[i][j + 1][1], mat2[i + 1][j][1]) + power_2(
                    matrix[i][j]
                )
                if mat2[i][j + 1][1] > mat2[i + 1][j][1]:
                    cur_str = 0
                else:
                    cur_str = 1
                mat2[i][j] = (cur_str, cur_num)
        a, b = nav(0, 0), mat2[0][0][1]
        if b == 0:
            print(b)
            print(a)
        else:
            mat2[n - 1][n - 1] = (-1, power_5(matrix[n - 1][n - 1]))
            for i in range(n - 1, -1, -1):
                for j in range(n - 1, -1, -1):
                    if i == j == n - 1:
                        continue
                    cur_num = min(mat2[i][j + 1][1], mat2[i + 1][j][1]) + power_5(
                        matrix[i][j]
                    )
                    if mat2[i][j + 1][1] > mat2[i + 1][j][1]:
                        cur_str = 0
                    else:
                        cur_str = 1
                    mat2[i][j] = (cur_str, cur_num)

            c, d = nav(0, 0), mat2[0][0][1]
            if d == 0:
                print(d)
                print(c)
            else:
                print(1)
                print("R" * z_j + "D" * z_i + "R" * (n - 1 - z_j) + "D" * (n - 1 - z_i))
    else:
        mat2[n - 1][n - 1] = (-1, power_2(matrix[n - 1][n - 1]))
        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if i == j == n - 1:
                    continue
                cur_num = min(mat2[i][j + 1][1], mat2[i + 1][j][1]) + power_2(
                    matrix[i][j]
                )
                if mat2[i][j + 1][1] > mat2[i + 1][j][1]:
                    cur_str = 0
                else:
                    cur_str = 1
                mat2[i][j] = (cur_str, cur_num)
        a, b = nav(0, 0), mat2[0][0][1]
        mat2[n - 1][n - 1] = (-1, power_5(matrix[n - 1][n - 1]))
        for i in range(n - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if i == j == n - 1:
                    continue
                cur_num = min(mat2[i][j + 1][1], mat2[i + 1][j][1]) + power_5(
                    matrix[i][j]
                )
                if mat2[i][j + 1][1] > mat2[i + 1][j][1]:
                    cur_str = 0
                else:
                    cur_str = 1
                mat2[i][j] = (cur_str, cur_num)

        c, d = nav(0, 0), mat2[0][0][1]

        if b > d:
            print(d)
            print(c)
        else:
            print(b)
            print(a)