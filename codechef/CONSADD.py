import sys


def shrink_matrix(matrix, is_row_large=True):
    if len(matrix) > x:
        if r <= 2 * x - 1:
            for i in range(1, r - x):
                for j in range(len(matrix[0])):
                    matrix[i][j] = matrix[i][j] + matrix[i + x][j] - matrix[x][j]
            for i in range(r - x, x):
                for j in range(len(matrix[0])):
                    matrix[i][j] -= matrix[x][j]
            while len(matrix) > x:
                matrix.pop()
        else:
            while len(matrix) > 2 * x - 1:
                for i in range(x - 1):
                    for j in range(len(matrix[0])):
                        matrix[-1 - x - i][j] += matrix[-1 - i][j] - matrix[-x][j]
                for i in range(x):
                    matrix.pop()
            if len(matrix) > x and len(matrix) <= 2 * x - 1:
                for i in range(1, len(matrix) - x):
                    for j in range(len(matrix[0])):
                        matrix[i][j] = matrix[i][j] + matrix[i + x][j] - matrix[x][j]
                for i in range(len(matrix) - x, x):
                    for j in range(len(matrix[0])):
                        matrix[i][j] -= matrix[x][j]
                while len(matrix) > x:
                    matrix.pop()
    if len(matrix[0]) > x:
        if c <= 2 * x - 1:
            for i in range(1, c - x):
                for j in range(len(matrix)):
                    matrix[j][i] += matrix[j][i + x] - matrix[j][x]
            for i in range(c - x, x):
                for j in range(len(matrix)):
                    matrix[j][i] -= matrix[j][x]
            while len(matrix[0]) > x:
                for i in matrix:
                    i.pop()
        else:
            while len(matrix[0]) > 2 * x - 1:
                for i in range(x - 1):
                    for j in range(len(matrix)):
                        matrix[j][-1 - x - i] += matrix[j][-1 - i] - matrix[j][-x]
                for i in range(x):
                    for j in matrix:
                        j.pop()
            if len(matrix[0]) > x:
                for i in range(1, len(matrix[0]) - x):
                    for j in range(len(matrix)):
                        matrix[j][i] += matrix[j][i + x] - matrix[j][x]
                for i in range(len(matrix[0]) - x, x):
                    for j in range(len(matrix)):
                        matrix[j][i] -= matrix[j][x]
                while len(matrix[0]) > x:
                    for i in matrix:
                        i.pop()
    if len(matrix[0]) == x:
        for i in range(len(matrix)):
            target = matrix[i][-1]
            for j in range(x):
                matrix[i][-1 - j] -= target
            matrix[i].pop()


def is_possible(matrix):
    for i in range(x - 1):
        target = matrix[0][i]
        for j in range(1, x):
            if matrix[j][i] != target:
                return False
    return True


t = int(sys.stdin.readline().rstrip())
for _ in range(t):
    r, c, x = list(map(int, sys.stdin.readline().rstrip().split()))
    matrix1 = []
    matrix2 = []
    for _ in range(r):
        matrix1.append(list(map(int, sys.stdin.readline().rstrip().split())))
    for _ in range(r):
        matrix2.append(list(map(int, sys.stdin.readline().rstrip().split())))
    differ_matrix = [
        [matrix1[i][j] - matrix2[i][j] for j in range(len(matrix1[0]))]
        for i in range(len(matrix1))
    ]
    shrink_matrix(differ_matrix)
    if is_possible(differ_matrix):
        print("Yes")
    else:
        print("No")