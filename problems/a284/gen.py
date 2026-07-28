import sys, random

def main():
    if len(sys.argv) < 2:
        return
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    if seed == 0:
        n = 0
        pts = []
    elif seed == 1:
        n = 1
        pts = [(0, 0)]
    elif seed == 2:
        n = 2
        pts = [(-10**9, -10**9), (10**9, 10**9)]
    else:
        n = rng.randint(3, 2000)
        s = set()
        while len(s) < n:
            x = rng.randint(-10**9, 10**9)
            y = rng.randint(-10**9, 10**9)
            s.add((x, y))
        pts = list(s)

    out = [str(n)]
    out += [f"{x} {y}" for x, y in pts]
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    main()
