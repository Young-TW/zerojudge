import sys, random

def main():
    if len(sys.argv) != 2:
        return
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    # Special edge cases for small seeds
    if seed == 0:
        n = 0  # empty set
        print(n)
        return
    elif seed == 1:
        n = 1
        # extreme values: minimum investment, maximum current value
        m, p = 1, 100000
        print(n)
        print(f"{m} {p}")
        return
    elif seed == 2:
        n = 5
        # all identical values (zero profit)
        m, p = 50000, 50000
        print(n)
        for _ in range(n):
            print(f"{m} {p}")
        return

    # General case for larger seeds
    n = rnd.randint(1, 1000)          # reasonable size
    print(n)
    for _ in range(n):
        m = rnd.randint(1, 100000)
        p = rnd.randint(1, 100000)
        print(f"{m} {p}")

if __name__ == "__main__":
    main()
