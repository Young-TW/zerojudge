import sys
import random


def rand_oct(rng, max_len):
    length = rng.randint(1, max_len)
    if length == 1:
        return str(rng.randint(0, 7))
    first = rng.randint(1, 7)
    rest = "".join(str(rng.randint(0, 7)) for _ in range(length - 1))
    return str(first) + rest


def main():
    rng = random.Random(int(sys.argv[1]))
    N = rng.randint(1, 20)
    boundary = ["0", "7", "77", "777", "7777", "77777", "1", "10", "100", "1000"]
    out = [str(N)]
    for _ in range(N):
        if rng.random() < 0.3:
            a = rng.choice(boundary)
        else:
            a = rand_oct(rng, 5)
        if rng.random() < 0.3:
            b = rng.choice(boundary)
        else:
            b = rand_oct(rng, 5)
        out.append(f"{a} {b}")
    sys.stdout.write("\n".join(out) + "\n")


main()
