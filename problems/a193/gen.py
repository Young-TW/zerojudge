import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    scenario = seed % 8

    # Sizes are kept tiny so a naive (maxA+1)^M enumeration brute finishes
    # well under 1 second. maxA is capped at 4 and M at 7 -> 5^7 = 78125 leaves.
    if scenario == 0:
        N, M, amax = 1, 1, 4                       # minimal 1x1
    elif scenario == 1:
        N, M, amax = 1, rng.randint(1, 4), 4       # single day, several types
    elif scenario == 2:
        N, M, amax = rng.randint(1, 5), 1, 4       # single type covering run
    elif scenario == 3:
        N, M, amax = rng.randint(1, 5), rng.randint(1, 4), 0  # all-zero demand
    elif scenario == 4:
        N, M, amax = rng.randint(2, 6), rng.randint(2, 6), 4  # general small
    elif scenario == 5:
        N, M, amax = rng.randint(2, 6), rng.randint(2, 6), 4  # force single-day type
    elif scenario == 6:
        N, M, amax = rng.randint(3, 7), rng.randint(3, 7), 4  # slightly bigger
    else:
        N, M, amax = rng.randint(1, 4), rng.randint(1, 4), 4  # small random

    if amax == 0:
        A = [0] * N
    else:
        A = [rng.randint(0, amax) for _ in range(N)]

    types = []
    for _ in range(M):
        Si = rng.randint(1, N)
        Ti = rng.randint(Si, N)
        Ci = rng.randint(1, 15)
        types.append((Si, Ti, Ci))

    # scenario 5: force at least one single-day (Si == Ti) type
    if scenario == 5 and M >= 1 and N >= 1:
        d = rng.randint(1, N)
        s, t, c = types[-1]
        types[-1] = (d, d, c)

    # guarantee feasibility: every day 1..N must be covered by some type.
    covered = set()
    for (s, t, c) in types:
        for d in range(s, t + 1):
            covered.add(d)
    uncovered = [d for d in range(1, N + 1) if d not in covered]
    if uncovered:
        if M >= 1:
            s, t, c = types[0]
            types[0] = (1, N, c)          # widen first type to span everything
        else:
            types.append((1, N, rng.randint(1, 15)))
            M += 1

    out = [f"{N} {M}", " ".join(map(str, A))]
    for (s, t, c) in types:
        out.append(f"{s} {t} {c}")
    sys.stdout.write("\n".join(out) + "\n")


main()
