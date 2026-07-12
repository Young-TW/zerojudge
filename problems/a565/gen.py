import sys
from random import Random

def main():
    if len(sys.argv) < 2:
        sys.stderr.write("usage: a565_gen.py <seed>\n")
        sys.exit(1)
    rng = Random(int(sys.argv[1]))

    # Pick a family to exercise different shapes / edge cases.
    family = rng.randint(0, 7)

    if family == 0:
        # Single short string.
        length = rng.randint(1, 6)
    elif family == 1:
        # Tiny string, maybe empty-ish.
        length = rng.randint(0, 4)
    elif family == 2:
        # All dots (no p/q at all).
        length = rng.randint(0, 10)
    elif family == 3:
        # Only p's.
        length = rng.randint(1, 8)
    elif family == 4:
        # Only q's.
        length = rng.randint(1, 8)
    elif family == 5:
        # Balanced-ish pq patterns.
        length = rng.randint(1, 12)
    elif family == 6:
        # Medium random.
        length = rng.randint(1, 20)
    else:
        # Larger random within brute-force budget.
        length = rng.randint(1, 30)

    # Decide the alphabet for the chosen family.
    if family == 2:
        alphabet = "."
    elif family == 3:
        alphabet = "p."
    elif family == 4:
        alphabet = "q."
    elif family == 5:
        alphabet = "pq."
    else:
        alphabet = "pq."

    chars = [rng.choice(alphabet) for _ in range(length)]
    s = "".join(chars)

    sys.stdout.write("1\n")
    sys.stdout.write(s + "\n")

if __name__ == "__main__":
    main()
