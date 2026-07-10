import sys
import random

def main():
    rng = random.Random(int(sys.argv[1]))

    N1 = rng.randint(1, 15)
    N2 = rng.randint(1, 15)

    tower1 = [rng.randint(1, 5) for _ in range(N1)]
    tower2 = [rng.randint(1, 5) for _ in range(N2)]

    print(f"{N1} {N2}")
    print(" ".join(map(str, tower1)))
    print(" ".join(map(str, tower2)))
    print("0 0")

main()
