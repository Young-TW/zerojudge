import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    # Problem has no input; nothing to generate.
    # Consume RNG for interface/reproducibility consistency.
    _ = rng.random()


if __name__ == "__main__":
    main()
