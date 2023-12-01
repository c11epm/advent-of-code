import sys

file = open(sys.argv[1]).read().strip()
score = 0
for line in file.split('\n'):
    digits = []
    for position, char in enumerate(line):
        if char.isdigit():
            digits.append(int(char))
        for digit_index, digit_string in enumerate(['one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']):
            if line[position:].startswith(digit_string):
                digits.append(digit_index + 1)

    score += digits[0]*10 + digits[-1]

print(score)
