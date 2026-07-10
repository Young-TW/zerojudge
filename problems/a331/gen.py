import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Keep the scale small so the brute-force solution finishes well within
    # 1 second, while still exercising boundary conditions.
    n = rng.randint(1, 100)
    m = rng.randint(1, 50)

    # n distinct integers with absolute value <= 10^9.
    values = set()
    while len(values) < n:
        values.add(rng.randint(-(10**9), 10**9))
    a = list(values)
    rng.shuffle(a)

    out = []
    out.append(f"{n} {m}")
    out.append(" ".join(map(str, a)))

    for _ in range(m):
        # Bias a portion of the queries toward boundary shapes so that
        # single-element segments, full-range queries, and extreme k
        # values are exercised across seeds.
        r = rng.random()
        if r < 0.15:
            i = rng.randint(1, n)
            j = i                       # single-element segment
        elif r < 0.30:
            i = 1
            j = n                       # full-range query
        else:
            i = rng.randint(1, n)
            j = rng.randint(i, n)

        seg_len = j - i + 1

        r2 = rng.random()
        if r2 < 0.20:
            k = 1                       # smallest in segment
        elif r2 < 0.40:
            k = seg_len                 # largest in segment
        else:
            k = rng.randint(1, seg_len)

        out.append(f"{i} {j} {k}")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
