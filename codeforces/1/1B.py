import sys
from string import ascii_uppercase


def convert(string):
    if string.startswith("R") and string[1].isdigit() and string.find("C") != -1:
        row, column = [int(i) for i in string[1:].split("C")]
        num_to_alpha = ""
        while column != 0:
            a, b = divmod(column - 1, 26)
            num_to_alpha += ascii_uppercase[b]
            column = a
        return num_to_alpha[::-1] + str(row)
    else:
        column_alpha = [i for i in list(string) if i.isalpha()]
        column = 0
        n = len(column_alpha)
        row = string[n:]
        for index, item in enumerate(column_alpha):
            column += (ord(item) - ord("A") + 1) * pow(26, n - index - 1)
        return "R" + row + "C" + str(column)


n = int(sys.stdin.readline())
for _ in range(n):
    s = sys.stdin.readline().rstrip()
    print(convert(s))