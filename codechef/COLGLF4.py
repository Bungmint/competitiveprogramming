import sys


def is_possible(x, y, z):
    if 2 * x + z > e or 3 * y + z > h or x < 0 or y < 0 or z < 0:
        return False
    return True


def cost(x, y, z):
    return a * x + b * y + c * z


t = int(sys.stdin.readline().rstrip())

for _ in range(t):
    n, e, h, a, b, c = list(map(int, sys.stdin.readline().rstrip().split()))
    more_eggs = e >= h
    total_cost = 0
    if (more_eggs and n > h + (e - h) // 2) or (not more_eggs and n > e + (h - e) // 3):
        print(-1)
        continue
    if c == min(a, b, c):
        if n <= min(e, h):
            total_cost += c * n
        else:
            if a >= b:
                max_z = min(e, h)
                min_cost = (a + b + c) * n
                while max_z >= 0:
                    y = min(n - max_z, (h - max_z) // 3)
                    x = n - y - max_z
                    if is_possible(x, y, max_z):
                        if min_cost > cost(x, y, max_z):
                            min_cost = cost(x, y, max_z)
                    max_z -= 1
                total_cost += min_cost
            else:
                max_z = min(e, h)
                min_cost = (a + b + c) * n
                while max_z >= 0:
                    x = min(n - max_z, (e - max_z) // 2)
                    y = n - x - max_z
                    if is_possible(x, y, max_z):
                        if min_cost > cost(x, y, max_z):
                            min_cost = cost(x, y, max_z)
                    max_z -= 1
                total_cost += min_cost
    elif b == min(a, b, c):
        max_y = h // 3
        if max_y >= n:
            total_cost += b * n
        else:
            if a >= c:
                min_cost = (a + b + c) * n
                while max_y >= 0:
                    z = min(n - max_y, h - 3 * max_y)
                    x = n - z - max_y
                    if is_possible(x, max_y, z):
                        if min_cost > cost(x, max_y, z):
                            min_cost = cost(x, max_y, z)
                    max_y -= 1
                total_cost += min_cost
            else:
                min_cost = (a + b + c) * n
                while max_y >= 0:
                    if e + h >= max_y + 2 * n:
                        x = min((e - h + 3 * max_y) // 2, e // 2, n - max_y)
                        z = n - x - max_y
                        if is_possible(x, max_y, z):
                            if min_cost > cost(x, max_y, z):
                                min_cost = cost(x, max_y, z)
                        x = min(e - n + max_y, e // 2, n - max_y)
                        if x >= 0.5 * (e - h + 3 * max_y):
                            z = n - max_y - x
                            if is_possible(x, max_y, z):
                                if min_cost > cost(x, max_y, z):
                                    min_cost = cost(x, max_y, z)
                        elif x == n - max_y:
                            z = n - max_y - x
                            if is_possible(x, max_y, z):
                                if min_cost > cost(x, max_y, z):
                                    min_cost = cost(x, max_y, z)
                    max_y -= 1
                total_cost += min_cost
    else:
        max_x = e // 2
        if max_x >= n:
            total_cost += a * n
        else:
            if b >= c:
                min_cost = (a + b + c) * n
                while max_x >= 0:
                    z = min(n - max_x, min(e - 2 * max_x, h))
                    y = n - max_x - z
                    if is_possible(max_x, y, z):
                        if min_cost > cost(max_x, y, z):
                            min_cost = cost(max_x, y, z)
                    max_x -= 1
                total_cost += min_cost
            else:
                min_cost = (a + b + c) * n
                while max_x >= 0:
                    if 2 * e + h >= max_x + 3 * n:
                        y = min((h - n + max_x) // 2, h // 3, n - max_x)
                        z = n - y - max_x
                        if is_possible(max_x, y, z):
                            if min_cost > cost(max_x, y, z):
                                min_cost = cost(max_x, y, z)
                        y = min((h - e + 2 * max_x) // 3, h // 3, n - max_x)
                        if y >= n + max_x - e:
                            z = n - max_x - y
                            if is_possible(max_x, y, z):
                                if min_cost > cost(max_x, y, z):

                                    min_cost = cost(max_x, y, z)
                        elif y == n - max_x:
                            z = n - max_x - y
                            if is_possible(max_x, y, z):
                                if min_cost > cost(max_x, y, z):
                                    min_cost = cost(max_x, y, z)
                    max_x -= 1
                total_cost += min_cost
    print(total_cost)