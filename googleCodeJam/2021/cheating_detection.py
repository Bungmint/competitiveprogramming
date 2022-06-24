from sys import stdin
import numpy as np


def sigmoid(num):
    return 1 / (1 + np.exp(-num))


def skill_to_auc(num):
    return 3333 / 2 * np.log((np.exp(3) + np.exp(-num)) / (np.exp(-3) + np.exp(-num)))


def find_nearest(array, value):
    array = np.asarray(array)
    idx = (np.abs(array - value)).argmin()
    return idx + 1


# f = open("./google_code_jam/cheeto.txt")
t = int(stdin.readline().rstrip())
p = int(stdin.readline().rstrip())
np_skill_convert = np.frompyfunc(skill_to_auc, 1, 1)
matrix = np.zeros((100, 10_000))
even_score = np_skill_convert(np.linspace(-3, 3, 100))


for x in range(1, t + 1):
    for i in range(100):
        matrix[i] = list(int(i) for i in stdin.readline().rstrip())

    peeps = np.sum(matrix, axis=1)
    sorted_peeps = np.sort(peeps)
    peep_sort = np.argsort(peeps)
    naive_diff = sorted_peeps - even_score
    min_std, idx = np.Infinity, 99
    for i in range(len(peeps)):
        cur_skill = sorted_peeps[i]
        if cur_skill > 5000:
            arr = sorted_peeps.copy()
            cur_skill = (cur_skill - 5000) * 2
            arr[i] = cur_skill
            np.sort(arr)
            std = np.std(arr - even_score)
            if std < min_std:
                min_std, idx = std, i

    y = peep_sort[idx] + 1
    print(f"Case #{x}: {y}")
