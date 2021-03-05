import sys
from functools import reduce


def min_2_trailing(matrix):
    if len(matrix) == 1:
        return (sum([power_2(i) for i in matrix[0]]), "R" * (len(matrix[0]) - 1))
    elif len(matrix[0]) == 1:
        return (
            sum([power_2(i[0]) for i in matrix]),
            "D" * (len(matrix) - 1),
        )
    else:
        start = power_2(matrix[0][0])
        matrix1 = [i[1:] for i in matrix]
        matrix2 = matrix[1:]
        mat11, mat12 = min_2_trailing(matrix1)
        mat21, mat22 = min_2_trailing(matrix2)
        if mat11 < mat21:
            return (mat11 + start, "R" + mat12)
        else:
            return (mat21 + start, "D" + mat22)


def min_5_trailing(matrix):
    if len(matrix) == 1:
        return (sum([power_5(i) for i in matrix[0]]), "R" * (len(matrix[0]) - 1))
    elif len(matrix[0]) == 1:
        return (
            sum([power_5(i[0]) for i in matrix]),
            "D" * (len(matrix) - 1),
        )
    else:
        start = power_5(matrix[0][0])
        matrix1 = [i[1:] for i in matrix]
        matrix2 = matrix[1:]
        mat11, mat12 = min_5_trailing(matrix1)
        mat21, mat22 = min_5_trailing(matrix2)
        if mat11 < mat21:
            return (mat11 + start, "R" + mat12)
        else:
            return (mat21 + start, "D" + mat22)


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


n = int(sys.stdin.readline())
matrix = [[int(i.strip()) for i in sys.stdin.readline().split()] for _ in range(n)]
a, b = min_2_trailing(matrix)
c, d = min_5_trailing(matrix)
if a < c:
    print(a, b, sep="\n")
else:
    print(c, d, sep="\n")
