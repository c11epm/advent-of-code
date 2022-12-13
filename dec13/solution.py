import sys
import functools
infile = sys.argv[1]
data = open(infile).read().strip()


def compare(one, two):
    if isinstance(one, list) and isinstance(two, list):
        i = 0
        while i < len(one) and i < len(two):
            c = compare(one[i], two[i])
            if c != 0:
                return c
            i += 1
        if i == len(one) and i < len(two):
            return -1
        elif i == len(two) and i < len(one):
            return 1
        else:
            return 0
    elif isinstance(one, int) and isinstance(two, int):
        if one < two:
            return -1
        elif one == two:
            return 0
        else:
            return 1
    elif isinstance(one, list) and isinstance(two, int):
        return compare(one, [two])
    else:
        return compare([one], two)


packs = []
sum = 0
for i, group in enumerate(data.split('\n\n')):
    l1, l2 = group.split('\n')
    #Part 1
    l1 = eval(l1)
    l2 = eval(l2)
    #For part two, save all lists
    packs.append(l1)
    packs.append(l2)
    if compare(l1, l2) == -1:
        print("Index " + str(i) + " was correct order")
        sum += i + 1
    print(i)

#Part 2 add extra packs
packs.append([[2]])
packs.append([[6]])
part2 = 1
#Sort the list using the compare function
packs = sorted(packs, key=functools.cmp_to_key(lambda x,y: compare(x,y)))

for i, pack in enumerate(packs):
    if pack == [[2]] or pack == [[6]]:
        print(f"index = {i}")
        part2 *= (i + 1)

print(sum)
print(part2)
