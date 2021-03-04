#
import sys

n = int(sys.stdin.readline())
choc_ls = [int(i.strip()) for i in sys.stdin.readline().rstrip().split()]
sum_choc = sum(choc_ls)
a_choc_t = a = b_choc_t = b = 0
is_equal = False
for i in choc_ls:
    a_choc_t += i
    a += 1
    if a_choc_t > 1 / 2 * sum_choc:
        a_choc_t -= i
        a -= 1
        break
    elif a_choc_t == 1 / 2 * sum_choc:
        is_equal = True
        break

if is_equal:
    print(a, n - a)
else:
    for i in range(n):
        b_choc_t += choc_ls[n - 1 - i]
        b += 1
        if b_choc_t > 1 / 2 * sum_choc:
            b_choc_t -= choc_ls[n - 1 - i]
            b -= 1
            break
    if a_choc_t <= b_choc_t:
        print(a + 1, b)
    else:
        print(a, b + 1)
