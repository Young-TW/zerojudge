import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    mode = rng.randint(0, 4)

    if mode == 0:
        # General small case
        L = rng.randint(3, 50)
        W = rng.randint(3, L)
    elif mode == 1:
        # Square floor (L == W)
        L = rng.randint(3, 50)
        W = L
    elif mode == 2:
        # Minimum border thickness (t = 1), larger floor
        L = rng.randint(3, 200)
        W = rng.randint(3, L)
    elif mode == 3:
        # Thick border (t near maximum)
        L = rng.randint(5, 60)
        W = rng.randint(5, L)
    else:
        # Inner rectangle is 1x1 (R = 1)
        t = rng.randint(1, 25)
        L = 2 * t + 1
        W = 2 * t + 1
        R = 1
        B = L * W - R
        print(f"{B} {R}")
        return

    max_t = (W - 1) // 2
    if max_t < 1:
        L = 3
        W = 3
        max_t = 1

    if mode == 2:
        t = 1
    elif mode == 3:
        t = rng.randint(max(1, max_t - 1), max_t)
    else:
        t = rng.randint(1, max_t)

    R = (L - 2 * t) * (W - 2 * t)
    B = L * W - R

    print(f"{B} {R}")


main()
