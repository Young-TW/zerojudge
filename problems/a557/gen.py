import sys, random

def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
    rng = random.Random(seed)

    # Small scale so brute (memoized DP) finishes well under 1s, but covering
    # the full legal boundary ranges of the problem.
    Y_MAX = 60
    I_MAX = 12
    Z_MAX = 30

    m = rng.randint(1, 6)
    cases = []
    for _ in range(m):
        # Most cases random; one boundary-ish case per batch with high prob.
        if rng.random() < 0.25:
            y = rng.randint(1, Y_MAX)
            i = 1
            z = y
        elif rng.random() < 0.4:
            y = rng.randint(1, Y_MAX)
            i = rng.randint(1, min(y, I_MAX))
            z = rng.randint(i, max(i, Z_MAX))
        else:
            y = rng.randint(1, Y_MAX)
            i = rng.randint(1, min(y, I_MAX))
            z = rng.randint(1, Z_MAX)
        cases.append((y, i, z))

    # Ensure at least one true boundary minimum (1,1,1) appears occasionally.
    if seed % 7 == 0:
        cases[0] = (1, 1, 1)

    out = [str(len(cases))]
    for (y, i, z) in cases:
        out.append(f"{y} {i} {z}")
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()
