def count_digit(x):
    cnt = 0
    while (x > 0):
        cnt += 1
        x //= 10
    return cnt

def main():
    denom, num, ans = 2, 3, 0
    for i in range(2, 1001):
        dd, nn = denom, num
        denom = dd + nn
        num = 2 * dd + nn
        if (count_digit(num) > count_digit(denom)):
            print(num, denom)
            ans += 1
    print(ans)

if (__name__ == '__main__'):
    main()