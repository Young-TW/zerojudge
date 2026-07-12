import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    n = rng.randint(1, 10)
    lines = [str(n)]
    for _ in range(n):
        c = rng.randint(0, 30)
        w = rng.randint(1, 30)
        lines.append(f"{c} {w}")
    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
