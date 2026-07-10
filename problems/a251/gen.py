import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    t = rng.randint(1, 5)
    print(t)
    odds = [5, 7, 9, 11, 13, 15, 17, 19]
    for _ in range(t):
        n = rng.choice(odds)
        s1 = rng.randint(0, 5)
        s2 = rng.randint(0, 5)
        s3 = rng.randint(0, 5)
        s4 = rng.randint(0, 5)
        print(f"{n} {s1} {s2} {s3} {s4}")


main()
