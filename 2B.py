import sys
from itertools import combinations

n = int(sys.stdin.readline())
matrix = [[int(i.strip()) for i in sys.stdin.readline().split()] for _ in range(n)]
ls = list(combinations(range(n + 1), n - 1))
product_ls = []
for i in ls:
    down_right_ls = ["D" if j in i else "R" for j in range((n - 1) * 2)]
    string = "".join(down_right_ls)
    product = 1
    r, c = 0, 0
    for k in down_right_ls:
        product *= matrix[r][c]
        if k == "D":
            c += 1
        else:
            r += 1
    product_ls.append((string, product))
product_ls = sorted(
    product_ls, key=lambda x: len(str(x[1])) - len(str(x[1]).rstrip("0"))
)
answer_tuple = product_ls[0]
print(len(str(answer_tuple[1])) - len(str(answer_tuple[1].rstrip("0"))))
print(answer_tuple[0])
