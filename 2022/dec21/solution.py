import sys

infile = sys.argv[1]
data = open(infile).read().strip()
file_rows = [x for x in data.split('\n')]


class Monkey:
    def __init__(self, name, value = None, left = None, operation = None, right = None):
        self.name = name
        self.left = left
        self.operation = operation
        self.right = right
        self.value = value

    def __str__(self):
        if self.value is None:
            val = f"{self.name} {self.left} {self.operation} {self.right}"
        else:
            val = f"{self.value}"
        return f"{self.name} : {val}"

monkeys = {}

for row in file_rows:
    splits = row.split(':')
    name = splits[0]
    value = splits[1].strip()
    if (" " in value):
        left, op, right = value.split(" ")
        monkey = Monkey(name, left=left, operation=op, right=right)
        monkeys[monkey.name] = monkey
    else:
        monkey = Monkey(name, value=value)
        monkeys[monkey.name] = monkey

def get_monkey_value(monkey_name, mode = 1):
    monkey = monkeys[monkey_name]

    if(monkey.value is not None):
        return monkey.value

    monkey.left = get_monkey_value(monkey.left)
    monkey.right = get_monkey_value(monkey.right)

    #None check of value and calculate correct value instead by switching the operation "Backwards"
    if monkey.left is None:
        pass
    if monkey.right is None:
        pass



    monkey.value = eval(f"{monkey.left} {monkey.operation} {monkey.right}")

    #print(monkey.value)
    try:
        value = int(monkey.value)
        return monkey.value
    except ValueError:
        print(f"{monkey.value} was not an Int")
        return 0

monkeys["humn"].value = None
right_path = 37175119093215
#            156882979171071
monkeys['root'].operation = '=='
