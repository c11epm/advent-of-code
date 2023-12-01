#!/usr/bin/python3
import sys

infile = sys.argv[1]
data = open(infile).read().strip()
file_rows = [x for x in data.split('\n')]

rocks = set()
for line in file_rows:
    prev_pos = None
    for point in line.split('->'):
        x, y = point.split(',')
        x = int(x)
        y = int(y)
        if prev_pos is not None:
            dx = x - prev_pos[0]
            dy = y - prev_pos[1]
            length = max(abs(dx), abs(dy))
            for i in range(length + 1):
                new_x = prev_pos[0] + i * (1 if dx > 0 else (0 if dx == 0 else -1))
                new_y = prev_pos[1] + i * (1 if dy > 0 else (0 if dy == 0 else -1))
                rocks.add((new_x, new_y))
        prev_pos = (x, y)

abyss = 2 + max(r[1] for r in rocks)
# print(floor)
lo_x = min(r[0] for r in rocks) - 5000
hi_x = max(r[0] for r in rocks) + 5000
for x in range(lo_x, hi_x):
    rocks.add((x, abyss))

p1_completed = False
for t in range(1000000):
    rock = (500, 0)
    while True:
        if rock[1] + 1 >= abyss and (not p1_completed):
            p1_completed = True
            print(f"p1: {t}")
        if (rock[0], rock[1] + 1) not in rocks:
            rock = (rock[0], rock[1] + 1)
        elif (rock[0] - 1, rock[1] + 1) not in rocks:
            rock = (rock[0] - 1, rock[1] + 1)
        elif (rock[0] + 1, rock[1] + 1) not in rocks:
            rock = (rock[0] + 1, rock[1] + 1)
        else:
            break
    if rock == (500, 0):
        print(f"p2: {t + 1}")
        break
    rocks.add(rock)
