from sys import stdin, stdout
from bisect import bisect_left, bisect_right


t = int(stdin.readline().rstrip())

for k in range(t):
    n, m = list(map(int, stdin.readline().rstrip().split()))
    boxes = list(map(int, stdin.readline().rstrip().split()))
    box_set = set(boxes)
    zero_idx = bisect_left(boxes, 0)
    neg_box = [abs(boxes[i]) for i in range(zero_idx - 1, -1, -1)]
    pos_box = boxes[zero_idx:]

    special = list(map(int, stdin.readline().rstrip().split()))
    zero_idx = bisect_left(special, 0)
    neg_special = [abs(special[i]) for i in range(zero_idx - 1, -1, -1)]
    pos_special = special[zero_idx:]
    alr_special_pos = [i for i in pos_special if i in box_set]
    alr_special_neg = [i for i in neg_special if -i in box_set]

    max_pos_box = 0
    for i in range(len(pos_special)):
        special = pos_special[i]
        idx = bisect_left(pos_box, special)
        prev = None
        while idx != prev:
            prev = idx
            idx = bisect_left(pos_box, special + idx, idx)
        num_special_boxes = (
            bisect_left(pos_special, special + idx)
            - i
            + len(alr_special_pos)
            - bisect_left(alr_special_pos, special + idx)
        )
        if max_pos_box < num_special_boxes:
            max_pos_box = num_special_boxes

    max_neg_box = 0
    for i in range(len(neg_special)):
        special = neg_special[i]
        idx = bisect_left(neg_box, special)
        prev = None
        while idx != prev:
            prev = idx
            idx = bisect_left(neg_box, special + idx, idx)
        num_special_boxes = (
            bisect_left(neg_special, special + idx)
            - i
            + len(alr_special_neg)
            - bisect_left(alr_special_neg, special + idx)
        )
        if max_neg_box < num_special_boxes:
            max_neg_box = num_special_boxes
    print(max_pos_box + max_neg_box)
