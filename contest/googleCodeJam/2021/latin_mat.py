from itertools import permutations
from math import factorial


def is_latin(mat):
    for i in range(len(mat)):
        if sorted(mat[i]) != [1, 2, 3, 4, 5]:
            return False
        if sorted([j[i] for j in mat]) != [1, 2, 3, 4, 5]:
            return False
    return True


n = 5
matrix = [None] * n
trace = 0
coms = list(permutations(range(1, n + 1), n))
one = [i for i in coms if i[0] == 1]
two = [i for i in coms if i[0] == 2]
three = [i for i in coms if i[0] == 3]
four = [i for i in coms if i[0] == 4]
five = [i for i in coms if i[0] == 5]
trace_set = set()
trace_val = set()
comb_num = factorial(n - 1)

# for i in range(comb_num):
#     for j in range(5):
#         arr = list(one[i][j:])
#         arr.extend(one[i][:j])
#         matrix[j] = arr
#     if is_latin(matrix):
#         trace_set = set()
#         trace_val = set()
#         for m in coms:
#             trace_sum = 0
#             trace_vals = []
#             for z in range(n):
#                 trace_sum += matrix[z][m[z] - 1]
#                 trace_vals.append(matrix[z][m[z] - 1])
#             trace_set.add(trace_sum)
#             trace_val.add(tuple(sorted(trace_vals)))
#         print(trace_set)


for i in range(comb_num):
    for j in range(comb_num):
        for k in range(comb_num):
            for l in range(comb_num):
                for y in range(comb_num):
                    matrix[0], matrix[1], matrix[2], matrix[3], matrix[4] = (
                        one[i],
                        two[j],
                        three[k],
                        four[l],
                        five[y],
                    )
                    matrix = list(matrix)
                    if is_latin(matrix):
                        for m in coms:
                            trace_sum = 0
                            trace_vals = []
                            for z in range(n):
                                trace_sum += matrix[z][m[z] - 1]
                                trace_vals.append(matrix[z][m[z] - 1])
                            trace_set.add(trace_sum)
                            trace_val.add(tuple(sorted(trace_vals)))
