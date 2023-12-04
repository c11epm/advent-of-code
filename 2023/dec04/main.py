import sys

def string_to_list(str):
    return list(filter(None, str.strip().split(" ")))

def right_in_left(right_item, left):
    return left.contains(right_item)

def get_score(digits):
    if len(digits) == 0:
        return 0
    return 2 ** (len(digits) - 1)

file = open(sys.argv[1]).read().strip()
score = 0
for line in file.split('\n'):
    parts = line.split(":")
    l1, l2 = parts[1].split("|")
    left = string_to_list(l1)
    right = string_to_list(l2)
    digits = []
    for i in right:
        if i in left:
            digits.append(i)
    score += get_score(digits)

print(score)