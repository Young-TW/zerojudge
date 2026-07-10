import sys
import random
from itertools import combinations


def main() -> None:
    if len(sys.argv) < 2:
        sys.exit(1)
    rnd = random.Random(int(sys.argv[1]))

    N = rnd.randint(3, 9)  # 2 < N < 10
    M = N * (N - 1) // 2

    # Small range so brute force runs well under 1s; cover negatives/zero/positives.
    lo = rnd.choice([-10, -5, -2, 0, 0, 1, 1, 1])
    hi = lo + rnd.choice([3, 5, 8, 10, 15, 20])
    nums = [rnd.randint(lo, hi) for _ in range(N)]

    sums = [a + b for a, b in combinations(nums, 2)]
    rnd.shuffle(sums)

    # Occasionally perturb one sum -> may yield an unsolvable instance (Impossible path).
    if rnd.random() < 0.2:
        sums[rnd.randrange(len(sums))] = rnd.randint(lo * 2 - 5, hi * 2 + 5)

    parts = [str(N)] + [str(s) for s in sums]
    sys.stdout.write(" ".join(parts) + "\n")


if __name__ == "__main__":
    main()
