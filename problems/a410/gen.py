import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    mode = rng.randint(0, 8)
    vals = []

    if mode == 0:
        # General small random values.
        vals = [rng.randint(-10, 10) for _ in range(6)]

    elif mode == 1:
        # General larger random values.
        vals = [rng.randint(-1000, 1000) for _ in range(6)]

    elif mode == 2:
        # Force a unique solution with a known integer (x, y).
        x = rng.randint(-20, 20)
        y = rng.randint(-20, 20)
        a = rng.randint(-8, 8)
        b = rng.randint(-8, 8)
        if a == 0 and b == 0:
            a = 1
        d = rng.randint(-8, 8)
        e = rng.randint(-8, 8)
        if d == 0 and e == 0:
            d = 1
        tries = 0
        while a * e - b * d == 0 and tries < 20:
            e = rng.randint(-8, 8)
            if d == 0 and e == 0:
                e = 1
            tries += 1
        if a * e - b * d == 0:
            e = a + 1
        c = a * x + b * y
        f = d * x + e * y
        vals = [a, b, c, d, e, f]

    elif mode == 3:
        # Force "Too many": eq2 is an exact multiple of eq1.
        a = rng.randint(-8, 8)
        b = rng.randint(-8, 8)
        c = rng.randint(-8, 8)
        if a == 0 and b == 0:
            a = 1
        k = rng.randint(-5, 5)
        if k == 0:
            k = 2
        vals = [a, b, c, k * a, k * b, k * c]

    elif mode == 4:
        # Force "No answer": det == 0 but constants break proportionality.
        a = rng.randint(-8, 8)
        b = rng.randint(-8, 8)
        c = rng.randint(-8, 8)
        if a == 0 and b == 0:
            a = 1
        k = rng.randint(-5, 5)
        if k == 0:
            k = 2
        f = k * c + rng.choice([-2, -1, 1, 2, 3])
        vals = [a, b, c, k * a, k * b, f]

    elif mode == 5:
        # Edge case: first equation is 0x + 0y = c.
        c = rng.randint(-5, 5)
        d = rng.randint(-8, 8)
        e = rng.randint(-8, 8)
        f = rng.randint(-8, 8)
        vals = [0, 0, c, d, e, f]

    elif mode == 6:
        # Edge case: second equation is 0x + 0y = f.
        a = rng.randint(-8, 8)
        b = rng.randint(-8, 8)
        c = rng.randint(-8, 8)
        f = rng.randint(-5, 5)
        vals = [a, b, c, 0, 0, f]

    elif mode == 7:
        # Near-zero / tiny values, heavy on zeros.
        vals = [rng.choice([0, 0, 1, -1, 2, -2]) for _ in range(6)]

    else:
        # mode 8: rounding-boundary friendly, small determinant.
        a = rng.randint(1, 4)
        e = rng.randint(1, 4)
        b = rng.randint(-3, 3)
        d = rng.randint(-3, 3)
        if a * e - b * d == 0:
            e = a + 1
        c = rng.randint(-100, 100)
        f = rng.randint(-100, 100)
        vals = [a, b, c, d, e, f]

    sys.stdout.write(" ".join(str(v) for v in vals) + "\n")


if __name__ == "__main__":
    main()
