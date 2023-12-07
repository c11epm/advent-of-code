import sys

file = open(sys.argv[1]).read().strip()

rules = {}
rules["red"] = 12
rules["green"] = 13
rules["blue"] = 14

impossible_games = []
rows = len(file.split('\n'))
power_sum = 0

for i, line in enumerate(file.split('\n')):
    found_impossible = False
    _, sets = line.split(":")
    sets = sets.strip()
    t = sets.split(";")
    turns = [j.strip() for j in t]
    power = {}
    for turn in turns:
        cubes = [k.strip() for k in turn.split(",")]
        for cube in cubes:
            number, cube_name = cube.split(" ")
            if cube_name in power:
                power[cube_name] = max(power[cube_name], int(number))
            else:
                power[cube_name] = int(number)

            if not found_impossible and rules[cube_name] < int(number):
                found_impossible = True
                impossible_games.append(i + 1)
    power_sum += power["red"] * power["green"] * power["blue"]

print(sum(list(i + 1 for i in range(rows))) - sum(impossible_games))
print(power_sum)
