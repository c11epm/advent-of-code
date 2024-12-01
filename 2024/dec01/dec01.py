import sys
import re
import math
import functools

file = open(sys.argv[1]).read().strip()
first = []
second = []
result = []
occurances = {}
for j, line in enumerate(file.split("\n")):
    res = re.match("(\d+) {3}(\d+)", line)
    first.append(int(res.groups()[0]))
    second.append(int(res.groups()[1]))
first.sort()
second.sort()
for i, val in enumerate(first):
    result.append(math.fabs(first[i]-second[i]))
    occurances[val] = second.count(val)
sum_star1 = functools.reduce(lambda x, y: x + y, result)
sum_star2 = 0
for key, val in occurances.items():
    sum_star2 += key * val
print(sum_star1)
print(sum_star2)
