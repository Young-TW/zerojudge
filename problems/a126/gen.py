import sys
import random


def main():
    if len(sys.argv) < 2:
        sys.exit("usage: a126_gen.py <seed>")
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Small scale so a naive brute (re-sorting on every F) finishes well under
    # 1s, while still exercising the boundary cases below.
    mode = rng.randint(0, 7)

    if mode == 0:
        # general small
        n = rng.randint(1, 30)
        minSal = rng.randint(0, 50)
    elif mode == 1:
        # tiny, fine-grained
        n = rng.randint(1, 12)
        minSal = rng.randint(0, 20)
    elif mode == 2:
        # floor at 0 (everyone hired stays forever unless S drives them under)
        n = rng.randint(1, 30)
        minSal = 0
    elif mode == 3:
        # high floor -> most I commands rejected immediately
        n = rng.randint(1, 30)
        minSal = rng.randint(80, 120)
    elif mode == 4:
        # zero floor, only A/S/F (no hiring): empty queries
        n = rng.randint(1, 20)
        minSal = 0
    elif mode == 5:
        # heavy on F queries with few employees (k > count boundary)
        n = rng.randint(1, 25)
        minSal = rng.randint(0, 30)
    elif mode == 6:
        # lots of S forcing departures
        n = rng.randint(1, 30)
        minSal = rng.randint(10, 40)
    else:
        # mixed, medium
        n = rng.randint(1, 40)
        minSal = rng.randint(0, 60)

    lines = [f"{n} {minSal}"]
    for _ in range(n):
        r = rng.random()
        if mode == 4:
            # no I commands in this mode
            choices = [('A', 0, 30), ('S', 0, 30), ('F', 1, 5)]
        elif mode == 5:
            # bias toward F
            if r < 0.2:
                choices = [('I', 0, 60)]
            elif r < 0.4:
                choices = [('A', 0, 20), ('S', 0, 20)]
            else:
                choices = [('F', 1, 8)]
        elif mode == 6:
            # bias toward S and I
            if r < 0.45:
                choices = [('I', 0, 80)]
            elif r < 0.85:
                choices = [('S', 0, 30)]
            else:
                choices = [('A', 0, 20), ('F', 1, 5)]
        else:
            if r < 0.4:
                choices = [('I', 0, 100)]
            elif r < 0.55:
                choices = [('A', 0, 30)]
            elif r < 0.75:
                choices = [('S', 0, 30)]
            else:
                choices = [('F', 1, 6)]

        cmd, lo, hi = rng.choice(choices)
        if cmd == 'F':
            k = rng.randint(lo, hi)
        else:
            k = rng.randint(lo, hi)
        lines.append(f"{cmd} {k}")

    sys.stdout.write("\n".join(lines) + "\n")


main()
