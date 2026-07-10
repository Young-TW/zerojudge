import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Small scale so brute force runs quickly, but cover boundaries.
    # Mix of tiny n (edge cases) and slightly larger n.
    r = rng.randint(0, 3)
    if r == 0:
        n = 1  # boundary: single day
    elif r == 1:
        n = 2  # boundary: two days
    elif r == 2:
        n = rng.randint(3, 20)  # small
    else:
        n = rng.randint(1, 200)  # up to 200 -> O(n^2) is instant

    out = [str(n)]
    for _ in range(n):
        # cover boundary revenue values incl. negatives and extremes
        choice = rng.randint(0, 3)
        if choice == 0:
            a = rng.choice([-1000000, 1000000, 0, -1, 1])
        elif choice == 1:
            a = rng.randint(-5, 5)  # small range -> many duplicates
        elif choice == 2:
            a = rng.randint(-100, 100)
        else:
            a = rng.randint(-1000000, 1000000)
        out.append(str(a))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
