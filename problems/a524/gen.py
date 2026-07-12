import sys
import random

def main():
    rng = random.Random(int(sys.argv[1]))
    # Small cases (1..8), a few per input to cover multi-query, with boundary emphasis.
    k = rng.randint(1, 3)
    cases = []
    for _ in range(k):
        # Bias toward boundary values 1 and 8, plus small randoms.
        r = rng.random()
        if r < 0.4:
            n = 1
        elif r < 0.8:
            n = 8
        else:
            n = rng.randint(1, 8)
        cases.append(n)
    out = "".join(f"{n}\n" for n in cases)
    sys.stdout.write(out)

if __name__ == "__main__":
    main()
