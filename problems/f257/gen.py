import sys
import random

def main():
    if len(sys.argv) < 2:
        seed = 0
    else:
        seed = int(sys.argv[1])
    rng = random.Random(seed)
    
    t = rng.randint(1, 3)
    lines = []
    for _ in range(t):
        n = rng.randint(1, 10)
        k = rng.randint(1, 15)
        lines.append(str(n))
        lines.append(str(k))
        for _ in range(k):
            x = rng.randint(0, n - 1)
            y = rng.randint(0, n - 1)
            lines.append(f"{x} {y}")
    sys.stdout.write("\n".join(lines) + "\n")

if __name__ == "__main__":
    main()
