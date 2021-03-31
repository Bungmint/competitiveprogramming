from sys import stdin, stdout
from collections import deque

t = int(stdin.readline().rstrip())

for k in range(t):
    tup = stdin.readline().strip()
    if len(tup) != 0:
        n, m = tuple(map(int, tup.split()))
    else:
        n, m = list(map(int, stdin.readline().rstrip().split()))
    matrix = [[None] * m for _ in range(n)]
    mat = [[float("inf")] * m for _ in range(n)]
    Q = deque()

    for i in range(n):
        arr = [int(i) for i in stdin.readline().rstrip()]

        for j in range(m):
            matrix[i][j] = arr[j]
            if arr[j] == 1:
                mat[i][j] = 0
                Q.append((i, j))

    else:
        while len(Q) > 0:
            w_i, w_j = Q.popleft()
            dist = mat[w_i][w_j] + 1

            if w_i + 1 < n and dist < mat[w_i + 1][w_j]:
                mat[w_i + 1][w_j] = dist
                Q.append((w_i + 1, w_j))
            if w_i - 1 > -1 and dist < mat[w_i - 1][w_j]:
                mat[w_i - 1][w_j] = dist
                Q.append((w_i - 1, w_j))
            if w_j + 1 < m and dist < mat[w_i][w_j + 1]:
                mat[w_i][w_j + 1] = dist
                Q.append((w_i, w_j + 1))
            if w_j - 1 > -1 and dist < mat[w_i][w_j - 1]:
                mat[w_i][w_j - 1] = dist
                Q.append((w_i, w_j - 1))

        for i in range(n):
            print(" ".join([str(j) for j in mat[i]]))
