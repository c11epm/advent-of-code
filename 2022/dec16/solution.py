import sys

"""

Make a recursive function that traverse the graph to find the highest flow for least amount of time
Maybe a take on Dijkstras?
make sure to not count nodes passing the second time (check isOpen attibure of valves)

"""


def get_neighbour_with_highest_rate(valve_name):
    valve = get_valve(valve_name)
    max = 0
    highest = None
    for neighbour in valve.connections:
        if max < neighbour.rate:
            max = neighbour.rate
            highest = neighbour

    return max, neighbour

def get_rate_of_valve_with_name(valve_name):
    valve = get_valve(valve_name)
    return valve.rate


def get_valve(valve_name):
    for valve in valves:
        if valve.name == valve_name:
            return valve


class Valve:
    def __init__(self, name, rate, connections):
        self.name = name
        self.rate = rate
        self.connections = connections
        self.isOpen = False

    def __str__(self):
        return f"name={self.name}, rate={self.rate}, connections={self.connections}, isOpen={self.isOpen}"


infile = sys.argv[1]
data = open(infile).read().strip()
file_rows = [x for x in data.split('\n')]
valves = set()

#Read input
for row in file_rows:
    split = row.split(' ')
    print(split)
    valve = split[1]
    rate = split[4]
    rate = int(rate[5:-1])
    print(rate)
    connections = split[9:]
    valves.add(Valve(valve, rate, connections))

start = get_valve("AA")
print(start)


"""
split = file_rows[3].split(' ')
valve = split[1]
rate = split[4]
rest = split[9:]
"""