from sys import stdin, stdout


def recur(arr, compare, far_right=False):
    if len(arr) <= 1:
        return arr
    elif len(arr) == 2:
        if far_right:
            print(f"{arr[0]} {arr[1]} {compare}")
            stdout.flush()
            smaller = int(stdin.readline().rstrip())
            if smaller == arr[0]:
                return [smaller, arr[1]]
            return [smaller, arr[0]]
        print(f"{arr[0]} {arr[1]} {compare}")
        stdout.flush()
        bigger = int(stdin.readline().rstrip())
        if bigger == arr[0]:
            return [arr[1], bigger]
        return [arr[0], bigger]
    else:
        print(f"{arr[0]} {arr[1]} {arr[2]}")
        ls1 = [arr[0], arr[1], arr[2]]
        stdout.flush()
        mid = int(stdin.readline().rstrip())
        ls1.remove(mid)
        low, high = min(ls1), max(ls1)
        if far_right:
            print(f"{low} {high} {compare}")
            stdout.flush()
            if low != int(stdin.readline().rstrip()):
                low, high = high, low
        else:
            print(f"{low} {high} {compare}")
            stdout.flush()
            if low == int(stdin.readline().rstrip()):
                low, high = high, low
        a_ll, a_lr, a_rl, a_rr = [], [], [], []
        for i in range(3, len(arr)):
            print(f"{arr[i]} {low} {mid}")
            stdout.flush()
            med = int(stdin.readline().rstrip())
            if med == arr[i]:
                a_lr.append(arr[i])
            elif med == low:
                a_ll.append(arr[i])
            else:
                print(f"{arr[i]} {high} {mid}")
                stdout.flush()
                med1 = int(stdin.readline().rstrip())
                if med1 == arr[i]:
                    a_rl.append(arr[i])
                elif med1 == high:
                    a_rr.append(arr[i])
        return (
            recur(a_ll, low)
            + [low]
            + recur(a_lr, mid)
            + [mid]
            + recur(a_rl, high)
            + [high]
            + recur(a_rr, high, far_right=True)
        )


t, n, Q = list(map(int, stdin.readline().rstrip().split()))
q = Q // t

for _ in range(t):
    arr_ll, arr_lr, arr_rl, arr_rr = [], [], [], []
    base = [1, 2, 3]
    print("1 2 3")
    stdout.flush()
    mid1 = int(stdin.readline().rstrip())
    base.remove(mid1)
    left, right = min(base), max(base)

    for i in range(4, n + 1):
        print(f"{i} {left} {mid1}")
        stdout.flush()
        med = int(stdin.readline().rstrip())
        if med == i:
            arr_lr.append(i)
        elif med == left:
            arr_ll.append(i)
        else:
            print(f"{i} {right} {mid1}")
            stdout.flush()
            med1 = int(stdin.readline().rstrip())
            if med1 == i:
                arr_rl.append(i)
            elif med1 == right:
                arr_rr.append(i)
    assert len(arr_ll) + len(arr_lr) + len(arr_rl) + len(arr_rr) == n - 3
    total = recur(arr_ll, left)
    total.append(left)
    total.extend(recur(arr_lr, mid1))
    total.append(mid1)
    total.extend(recur(arr_rl, right))
    total.append(right)
    total.extend(recur(arr_rr, right, far_right=True))

    print(" ".join([str(i) for i in total]))
    stdout.flush()
    if int(stdin.readline().rstrip()) != 1:
        break
