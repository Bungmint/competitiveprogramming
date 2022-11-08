import math

def digit_sum(x):
    sum = int(0)
    while x > int(0):
        sum += int(x) % 10
        x //= int(10)
    return sum

ans = int(0)
for a in range(1, 100):
    for b in range(1, 100):
        z = digit_sum(int(pow(int(a), int(b))))
        if ans < z:
            print(a, b, z)
            ans = z
print(ans)
