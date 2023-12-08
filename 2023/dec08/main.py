import sys

file = open(sys.argv[1]).read().strip()
rows = file.split('\n')

L = 0
R = 1

instruction, _, *data = file.split("\n")
instruction_map = {}

def insert_string_signs(line_to_add):
    line_to_add = line_to_add[:1] + "'" + line_to_add[1:]
    line_to_add = line_to_add[:5] + "'" + line_to_add[5:]
    line_to_add = line_to_add[:8] + "'" + line_to_add[8:]
    line_to_add = line_to_add[:-1] + "'" + line_to_add[-1:]
    return line_to_add


for i, line in enumerate(data):
    key, tple = line.split("=")
    tple = eval(insert_string_signs(tple.strip()))
    #print("'" + key.strip() + "'")
    #print(tuple[R])

    key = key.strip()
    print(key)
    print("Adding: " + key + " = " + "("+ tple[0] +", " + tple[1] + ")")

    instruction_map[key] = tple

current_instruction = ''
next_instruction = "AAA"
steps = 0
for i in range(100000):
    instr = instruction[i % len(instruction)]
    steps += 1
    current_instruction = next_instruction
    if(instr == 'L'):
        next_instruction = instruction_map[current_instruction][L]
    else:
        next_instruction = instruction_map[current_instruction][R]

    print("----" + next_instruction)

    if next_instruction == 'ZZZ':
        break

print(steps)