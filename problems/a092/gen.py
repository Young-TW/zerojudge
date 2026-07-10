import sys
import random


def solvable(C, P, L):
    # A solution M exists iff no pair of savages meets on the same year
    # as plain integers (a meeting at integer level is inescapable for
    # every M). If integer trajectories stay apart, a large enough M works.
    n = len(C)
    for i in range(n):
        for j in range(i + 1, n):
            lim = min(L[i], L[j])
            for t in range(lim + 1):
                if C[i] + t * P[i] == C[j] + t * P[j]:
                    return False
    return True


def main():
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    # Small N (<=5) and small C/P/L so the brute simulation finishes in 1s.
    n = rnd.choice([1, 2, 2, 3, 3, 4, 5])

    # Draw parameters until a solution exists (the problem guarantees one).
    # Distinct starting caves are necessary; retrying also rules out the
    # inescapable integer-level collisions.
    while True:
        caves = rnd.sample(range(1, 12), n)
        P = [rnd.choice([1, 1, rnd.randint(1, 8)]) for _ in range(n)]
        L = [rnd.choice([0, 1, rnd.randint(0, 8)]) for _ in range(n)]
        if solvable(caves, P, L):
            break

    out = [str(n)]
    for i in range(n):
        out.append(f"{caves[i]} {P[i]} {L[i]}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
