import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    # boundary values: smallest cases, powers of two (no solution), and neighbors
    boundaries = [
        1, 2, 3, 4, 5, 6, 7, 8,
        15, 16, 17,
        31, 32, 33,
        63, 64, 65,
        127, 128, 129,
        255, 256, 257,
        511, 512, 513,
        1023, 1024, 1025,
        2047, 2048, 2049,
        4095, 4096, 4097,
        8191, 8192, 8193,
        16383, 16384, 16385,
    ]
    count = rng.randint(1, 6)
    out = []
    for _ in range(count):
        r = rng.random()
        if r < 0.5:
            val = rng.choice(boundaries)
        elif r < 0.75:
            val = rng.randint(1, 100)
        else:
            val = rng.randint(1, 20000)
        out.append(str(val))
    sys.stdout.write("\n".join(out) + "\n")


main()
