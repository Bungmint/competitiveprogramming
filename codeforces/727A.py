import sys, math


def is_possible(num1, num2):
    if num1 > num2:
        return False
    elif num1 == num2:
        return True
    else:
        if is_possible(num1 * 2, num2):
            arr.append(num1 * 2)
            return True
        elif is_possible(num1 * 10 + 1, num2):
            arr.append(num1 * 10 + 1)
            return True
        return False


a, b = list(map(int, sys.stdin.readline().rstrip().split()))
arr = []
if is_possible(a, b):
    print("YES")
    print(len(arr) + 1)
    arr.reverse()
    print(f"{a} " + " ".join([str(i) for i in arr]))
else:
    print("NO")
