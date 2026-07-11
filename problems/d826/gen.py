import sys
import random

def main():
    rng = random.Random(int(sys.argv[1]))
    n = rng.randint(1, 10)
    m = n * rng.randint(1, 5)
    rooms = [str(rng.randint(1, n)) for _ in range(m)]
    print(f"{n} {m}")
    print(" ".join(rooms))

if __name__ == "__main__":
    main()
