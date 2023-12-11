import sys

file = open(sys.argv[1]).read().strip()
rows = file.split('\n')


def only_contains_zeroes(input):
    return len(input) == len(list(filter(lambda elem: elem == 0, input)))


def calc_different_list(input):
    difference = []
    for elem in range(len(input) - 1):
        difference.append(input[elem + 1] - input[elem])
    print(difference)
    if only_contains_zeroes(difference):
        return input[-1]
    else:
        return input[-1] + calc_different_list(difference)
    # return difference


sum = 0;

for i, line in enumerate(file.split("\n")):
    int_row = [int(j) for j in line.split(" ")]
    sum += calc_different_list(int_row)
print(sum)
