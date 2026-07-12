import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # At most 10 test cases, terminated by 0.
    # Keep sizes small so a naive brute force runs well under 1s,
    # but cover edge cases: single digit, 17, multiples, non-multiples,
    # numbers near 10, large-ish (up to ~30 digits, within reason).
    T = rng.randint(1, 10)

    for _ in range(T):
        choice = rng.randint(0, 4)
        if choice == 0:
            # edge: single-digit number (1..9), never a multiple of 17
            print(rng.randint(1, 9))
        elif choice == 1:
            # edge: small exact multiples of 17
            k = rng.randint(1, 6)
            print(17 * k)
        elif choice == 2:
            # edge: exactly 10 (boundary of theorem applicability)
            print(10)
        elif choice == 3:
            # general small number, 2..4 digits
            ndig = rng.randint(2, 4)
            lo = 10 ** (ndig - 1)
            hi = 10 ** ndig - 1
            print(rng.randint(lo, hi))
        else:
            # larger, up to ~30 digits (still trivial for brute force)
            ndig = rng.randint(5, 30)
            digits = [rng.randint(1, 9)] + [rng.randint(0, 9) for _ in range(ndig - 1)]
            print(''.join(str(d) for d in digits))

    # terminator
    print(0)


main()
