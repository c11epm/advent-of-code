import sys

infile = sys.argv[1]
data = open(infile).read().strip()
lines = [x for x in data.split('\n')]

rocks = set()
for line in lines:
    splits = line.split('->')
    prev_pos = None
    for point in splits:
        x, y = point.split(',')
        x = int(x)
        y = int(y)
        pos = (x, y)
        if prev_pos is not None:
            delta_x = pos[0] - prev_pos[0]
            delta_y = pos[1] - prev_pos[1]
            if abs(delta_y) > 0:
                y_min = min(pos[1], prev_pos[1])
                for i in range(y_min, y_min + abs(delta_y) + 1, 1):
                    new_x = x
                    new_y = i
                    rocks.add((new_x, new_y))

            elif abs(delta_x) > 0:
                x_min = min(pos[0], prev_pos[0])
                for i in range(x_min, x_min + abs(delta_x) + 1, 1):
                    new_x = i
                    new_y = y
                    rocks.add((new_x, new_y))

        prev_pos = (x, y)

abyss = max(rock[1] for rock in rocks) + 2




not_done = True
for i in range(99999999):
    sand = (500, 0)
    while not_done:
        if sand[1] > abyss and (not not_done):
            not_done = False
            print(i)
        if (sand[0], sand[1] + 1) not in rocks:
            print(f"{i} move down")
            sand = (sand[0], sand[1] + 1)
        elif (sand[0] - 1, sand[1] + 1) not in rocks:
            print(f"{i} move left")
            sand = (sand[0] - 1, sand[1] + 1)
        elif (sand[0] + 1, sand[1] + 1) not in rocks:
            print(f"{i} move right")
            sand = (sand[0] - 1, sand[1] + 1)
        else:
            print(f"{i} at rest")
            break
    if sand == (500, 0):
        print(i + 1)
        break
    rocks.add(sand)

# print(rocks)
