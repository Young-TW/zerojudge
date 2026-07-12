import sys
import random


LOWER = "abcdefghijklmnopqrstuvwxyz"
UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
DIGITS = "0123456789"
# printable symbols (no space; password contains no spaces per problem)
SYMS = "!@#$%^&*()-_=+[]{};:,.<>?/|~`"


def main():
    rng = random.Random(int(sys.argv[1]))

    r = rng.randint(0, 9)

    if r == 0:
        # single character: very weak (no property)
        pw = rng.choice(LOWER + UPPER + DIGITS)
    elif r == 1:
        # boundary length exactly 7 vs 8
        n = rng.choice([7, 8])
        pw = "".join(rng.choice(LOWER) for _ in range(n))
    elif r == 2:
        # only lowercase, long -> only length property
        n = rng.randint(8, 30)
        pw = "".join(rng.choice(LOWER) for _ in range(n))
    elif r == 3:
        # mixed case but short -> only case property
        n = rng.randint(2, 7)
        chars = []
        for _ in range(n):
            chars.append(rng.choice(LOWER + UPPER))
        rng.shuffle(chars)
        # guarantee at least one of each
        if not any(c in LOWER for c in chars):
            chars[0] = rng.choice(LOWER)
        if not any(c in UPPER for c in chars):
            chars[-1] = rng.choice(UPPER)
        rng.shuffle(chars)
        pw = "".join(chars)
    elif r == 4:
        # lower + digit, long -> length + letter/digit, no case => GOOD
        n = rng.randint(8, 30)
        chars = []
        for _ in range(n):
            chars.append(rng.choice(LOWER + DIGITS))
        if not any(c in LOWER for c in chars):
            chars[0] = rng.choice(LOWER)
        if not any(c in DIGITS for c in chars):
            chars[-1] = rng.choice(DIGITS)
        rng.shuffle(chars)
        pw = "".join(chars)
    elif r == 5:
        # mixed case + digit, short -> case + letter/digit => GOOD
        n = rng.randint(2, 7)
        chars = []
        for _ in range(n):
            chars.append(rng.choice(LOWER + UPPER + DIGITS))
        if not any(c in LOWER for c in chars):
            chars[0] = rng.choice(LOWER)
        if not any(c in UPPER for c in chars):
            chars[1] = rng.choice(UPPER)
        if not any(c in DIGITS for c in chars):
            chars[-1] = rng.choice(DIGITS)
        rng.shuffle(chars)
        pw = "".join(chars)
    elif r == 6:
        # mixed case + digit/sym, long -> STRONG
        n = rng.randint(8, 30)
        pool = LOWER + UPPER + DIGITS + SYMS
        chars = []
        for _ in range(n):
            chars.append(rng.choice(pool))
        # guarantee all categories
        if not any(c in LOWER for c in chars):
            chars[0] = rng.choice(LOWER)
        if not any(c in UPPER for c in chars):
            chars[1] = rng.choice(UPPER)
        if not any(c in (DIGITS + SYMS) for c in chars):
            chars[-1] = rng.choice(DIGITS + SYMS)
        rng.shuffle(chars)
        pw = "".join(chars)
    elif r == 7:
        # symbols only, long -> length + (no letter) => only length = ACCEPTABLE
        n = rng.randint(8, 30)
        pw = "".join(rng.choice(SYMS) for _ in range(n))
    elif r == 8:
        # max length 30, fully random printable
        n = 30
        pool = LOWER + UPPER + DIGITS + SYMS
        pw = "".join(rng.choice(pool) for _ in range(n))
    else:
        # general random
        n = rng.randint(1, 30)
        pool = LOWER + UPPER + DIGITS + SYMS
        pw = "".join(rng.choice(pool) for _ in range(n))

    sys.stdout.write(pw + "\n")


main()
