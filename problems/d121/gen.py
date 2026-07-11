import sys
import random

def main():
    rng = random.Random(int(sys.argv[1]))
    lines = []
    num_cases = rng.randint(15, 40)
    for _ in range(num_cases):
        r = rng.randint(1, 5)
        if r == 1:
            n = rng.randint(-50, 50)
        elif r == 2:
            n = rng.randint(-10000, 10000)
        elif r == 3:
            n = rng.randint(-1000000, 1000000)
        elif r == 4:
            n = rng.randint(-2147483647, 2147483647)
        else:
            # powers of two and nearby for interesting factorizations
            base = 2 ** rng.randint(1, 30)
            sign = rng.choice([-1, 1])
            n = sign * (base + rng.randint(-5, 5))
        # ensure within valid range and not zero (zero terminates input)
        if n == 0:
            n = 1
        if n <= -2147483648:
            n = -2147483647
        if n >= 2147483648:
            n = 2147483647
        lines.append(str(n))
    lines.append("0")
    sys.stdout.write("\n".join(lines) + "\n")

main()
