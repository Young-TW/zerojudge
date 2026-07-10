import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    r = rng.randint(0, 6)
    if r == 0:
        # small boundary: Vt just above V0 (so only n=1 valid, or none)
        V0 = rng.randint(1, 5)
        Vt = V0 + rng.randint(0, 3)
    elif r == 1:
        # Vt exactly equal to V0 => cannot make even one piece
        V0 = rng.randint(1, 50)
        Vt = V0
    elif r == 2:
        # force a tie: pick V0 and Vt so that Vt/(2*V0) lands on x.5
        V0 = rng.randint(1, 30)
        k = rng.randint(1, 30)
        Vt = (2 * k + 1) * V0  # Vt/(2*V0) = k + 0.5
    elif r == 3:
        # force peak exactly on an integer: Vt = 2*k*V0
        V0 = rng.randint(1, 30)
        k = rng.randint(1, 30)
        Vt = 2 * k * V0
    else:
        # generic small random
        V0 = rng.randint(1, 50)
        Vt = V0 + rng.randint(1, 200)

    # keep within problem bounds
    Vt = max(1, min(Vt, 59999))
    V0 = max(1, min(V0, 599))

    print(Vt)
    print(V0)


main()
