import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    n = rng.randint(1, 20)
    q = rng.randint(1, 20)

    lines = [f"{n} {q}"]

    for _ in range(q):
        v = rng.choice([1, 2])
        if v == 1:
            i = rng.randint(1, n)
            lines.append(f"1 {i}")
        else:
            l = rng.randint(1, n)
            r = rng.randint(l, n)
            lines.append(f"2 {l} {r}")

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
