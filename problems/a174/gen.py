import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    lines = []
    num_cases = rng.randint(1, 3)

    for _ in range(num_cases):
        # Small k so the brute-force O(k^2)-ish simulation finishes instantly.
        k = rng.randint(1, 80)

        # m: bias towards small values (more collisions, the interesting case),
        # but also cover the boundaries m=1 and m=200.
        r = rng.random()
        if r < 0.15:
            m = 1
        elif r < 0.30:
            m = 2
        elif r < 0.55:
            m = rng.randint(3, 10)
        elif r < 0.75:
            m = rng.randint(11, 50)
        elif r < 0.90:
            m = 200
        else:
            m = rng.randint(1, 200)

        lines.append(f"{k} {m}")

        inserted = []  # track for duplicate inserts and targeted deletes

        for _ in range(k):
            r = rng.random()
            if r < 0.45:
                # Insert
                r2 = rng.random()
                if r2 < 0.30 and inserted:
                    # Duplicate insert of an existing value (set dedup test)
                    N = rng.choice(inserted)
                elif r2 < 0.55:
                    N = rng.randint(0, 20)          # small => many collisions
                elif r2 < 0.70:
                    N = rng.randint(0, 200)
                elif r2 < 0.80:
                    N = 0                            # boundary: zero
                elif r2 < 0.90:
                    N = rng.randint(2147483640, 2147483646)  # near 2^31-2
                else:
                    N = rng.randint(0, 2147483646)  # full range
                lines.append(f"1 {N}")
                inserted.append(N)
            elif r < 0.70:
                # Delete
                r2 = rng.random()
                if r2 < 0.50 and inserted:
                    N = rng.choice(inserted)         # delete something present
                elif r2 < 0.70:
                    N = rng.randint(0, 20)           # small (may or may not exist)
                else:
                    N = rng.randint(0, 2147483646)  # likely absent
                lines.append(f"2 {N}")
            else:
                # Print entire table
                lines.append("3")

    sys.stdout.write("\n".join(lines) + "\n")


main()
