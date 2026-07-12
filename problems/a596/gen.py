import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Keep N small so brute force (2^N) runs well within 1 second,
    # but cover boundaries: minimal lengths and edge values.
    # Bias toward small-to-mid sizes, occasionally hit extremes.
    r = rng.random()
    if r < 0.15:
        n = rng.randint(1, 2)        # too short -> answer 0
    elif r < 0.30:
        n = 3                         # minimal valid length
    elif r < 0.85:
        n = rng.randint(4, 12)        # typical small
    else:
        n = rng.randint(13, 16)       # a bit larger but still 2^16 = 65536

    # Heights: 0 <= h <= 30000. Mix boundary values and random values.
    def gen_height():
        r2 = rng.random()
        if r2 < 0.25:
            return 0                  # boundary: zero
        elif r2 < 0.45:
            return rng.choice([0, 1, 2, 3, 30000])  # boundary/extreme values
        elif r2 < 0.70:
            return rng.randint(0, 5)  # small range -> more equal neighbours
        else:
            return rng.randint(0, 30000)

    # Occasionally force all-equal arrays (answer should be 0)
    if rng.random() < 0.10:
        h = rng.randint(0, 30000)
        heights = [h] * n
    elif rng.random() < 0.15:
        # Two-value alternating pattern to stress zigzag counting
        x = rng.randint(0, 30000)
        y = rng.randint(0, 30000)
        heights = [x if i % 2 == 0 else y for i in range(n)]
    else:
        heights = [gen_height() for _ in range(n)]

    out = []
    out.append(str(n))
    out.append(" ".join(str(h) for h in heights))
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()
