import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    num_cases = rng.randint(1, 5)
    lines = []
    for _ in range(num_cases):
        # n: break time, 1..100, bias toward boundaries
        if rng.random() < 0.25:
            n = rng.choice([1, 2, 99, 100])
        else:
            n = rng.randint(1, 100)

        # 4 climbing times, each 1..100, bias toward boundaries
        times = []
        for _ in range(4):
            if rng.random() < 0.25:
                times.append(rng.choice([1, 100]))
            else:
                times.append(rng.randint(1, 100))

        # 8 classroom floors, each 1..5, bias toward boundaries / extremes
        floors = []
        for _ in range(8):
            r = rng.random()
            if r < 0.15:
                floors.append(1)
            elif r < 0.30:
                floors.append(5)
            else:
                floors.append(rng.randint(1, 5))

        lines.append(str(n))
        lines.append(" ".join(map(str, times)))
        lines.append(" ".join(map(str, floors)))

    sys.stdout.write("\n".join(lines) + "\n")


main()
