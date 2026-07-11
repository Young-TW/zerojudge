import sys
import random

def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    n = rng.randint(10, 30)
    for _ in range(n):
        x = rng.randint(-1000, 1000)
        print(x)

main()
