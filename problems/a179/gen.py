import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep N small so brute force (2^N) runs well under 1s.
    # Bias toward very small N to exercise boundary cases, but also
    # reach the upper end (N=16 => 65536 subsets) sometimes.
    if rng.randint(1, 4) == 1:
        N = rng.randint(1, 4)
    else:
        N = rng.randint(1, 16)

    # M may be 0 (no users at all -> answer 0) up to a modest cap.
    M = rng.randint(0, 20)

    costs = [rng.randint(1, 10) for _ in range(N)]

    out = []
    out.append(f"{N} {M}")
    out.append(" ".join(map(str, costs)))
    for _ in range(M):
        # Allow Ai == Bi as an edge case (problem does not forbid it).
        a = rng.randint(1, N)
        b = rng.randint(1, N)
        c = rng.randint(1, 10)
        out.append(f"{a} {b} {c}")

    sys.stdout.write("\n".join(out) + "\n")


main()
