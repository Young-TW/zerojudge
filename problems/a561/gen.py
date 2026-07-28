#!/usr/bin/env python3
import sys, random

def main():
    if len(sys.argv) < 2:
        return
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    if seed == 0:
        # empty set
        print(0)
        return
    if seed == 1:
        # single element, smallest possible value
        print(1)
        print(0)
        return
    if seed == 2:
        # two extreme values
        print(2)
        print("0 9999999")
        return

    # regular case
    # choose a size that is reasonable for output but respects the limits
    n = rnd.randint(1, 200000)          # up to 2e5 elements
    # generate n distinct numbers in [0, 10_000_000)
    numbers = rnd.sample(range(0, 10_000_000), n)

    print(n)
    # output numbers in one line, space separated
    sys.stdout.write(' '.join(map(str, numbers)))
    sys.stdout.write('\n')

if __name__ == "__main__":
    main()
