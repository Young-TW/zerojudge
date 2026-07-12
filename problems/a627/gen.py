import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    level = rng.choice([0, 1, 5])
    # Maximum achievable array capacity (excluding mirror/parity) per level,
    # using 8 disks of 750GB:
    #   RAID 0: 8 * 750 = 6000
    #   RAID 1: (8/2) * 750 = 3000
    #   RAID 5: (8-1) * 750 = 5250
    maxc = {0: 6000, 1: 3000, 5: 5250}[level]

    mode = rng.randint(0, 5)
    if mode == 0:
        # minimum boundary
        required = 1
    elif mode == 1:
        # exact single-disk capacity (forces exact-fit considerations)
        required = rng.choice([250, 400, 500, 750])
    elif mode == 2:
        # maximum solvable boundary
        required = maxc
    elif mode == 3:
        # very small required (cheap arrays dominate)
        required = rng.randint(1, 50)
    elif mode == 4:
        # near-maximum (forces large qty / 750GB usage)
        required = rng.randint(max(1, maxc - 200), maxc)
    else:
        # generic random within full solvable range
        required = rng.randint(1, maxc)

    print(f"{required} {level}")


if __name__ == "__main__":
    main()
