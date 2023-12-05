import sys

def string_to_list(str):
    return list(filter(None, str.strip().split(" ")))

def get_score(digits):
    if len(digits) == 0:
        return 0
    return 2 ** (len(digits) - 1)

file = open(sys.argv[1]).read().strip()
score = 0
scraps = {}
rows = file.split('\n')

for i in range(len(rows)):
    scraps[i] = 1

for i, line in enumerate(file.split('\n')):
    parts = line.split(":")
    l1, l2 = parts[1].split("|")
    left = string_to_list(l1)
    right = string_to_list(l2)
    digits = []
    for item in right:
        if item in left:
            digits.append(item)

    if len(digits) > 0:
        for j in range(len(digits)):
            scraps[i + j + 1] += scraps[i]
    score += get_score(digits)

print(score)
print(sum(scraps.values()))