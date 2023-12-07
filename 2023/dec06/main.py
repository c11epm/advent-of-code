import sys

file = open(sys.argv[1]).read().strip()
score = 0
rows = file.split('\n')

time, distance = file.split("\n")

_, t = time.split(":")
times = [int(i) for i in list(filter(None, t.strip().split(" ")))]
_, d = distance.split(":")
distances = [int(i) for i in list(filter(None, d.strip().split(" ")))]

record_beating_races = []

for i, race in enumerate(times):
    record_beating_permutations = 0
    for millis in range(race + 1):
        pass
        # TODO implement this
    record_beating_races.append(record_beating_permutations)

print(sum(record_beating_races))
