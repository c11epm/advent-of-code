import sys

file = open(sys.argv[1]).read().strip()
score = 1
rows = file.split('\n')

time, distance = file.split("\n")

_, t = time.split(":")
times = [int(i) for i in list(filter(None, t.strip().split(" ")))]
_, d = distance.split(":")
distances = [int(i) for i in list(filter(None, d.strip().split(" ")))]

record_beating_races = []

print(times)

for i, race in enumerate(times):
    record_beating_permutations = 0
    print(race)
    for hold_for_millis in range(race + 1):
        speed = hold_for_millis
        dist = (times[i]-hold_for_millis) * speed
        if(dist > distances[i]):
            record_beating_permutations += 1
        # TODO implement this
    record_beating_races.append(record_beating_permutations)

for i in record_beating_races:
    score *= i
print(score)
