from sys import stdin


mod = pow(10, 9) + 7
t = int(stdin.readline().rstrip())
matrix_l = [[0] * (1001) for _ in range(1000)]
matrix_r = [[0] * (1001) for _ in range(1000)]

for _ in range(t):
    n, k = list(map(int, stdin.readline().rstrip().split()))
    for i in range(k):
        matrix_l[i][0] = 1
        matrix_r[i][0] = 1
    for i in range(n + 1):
        matrix_l[0][i] = 1
        matrix_r[0][i] = 1

    for i in range(1, k):
        for j in range(1, n + 1):
            matrix_l[i][j] = (matrix_l[i][j - 1] + matrix_r[i - 1][n - j]) % mod
            matrix_r[i][j] = (matrix_l[i - 1][n - j] + matrix_r[i][j - 1]) % mod
    print(matrix_r[k - 1][n])
