import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    num_cases = rng.randint(1, 4)
    lines = []

    for _ in range(num_cases):
        r = rng.random()
        if r < 0.30:
            y = rng.choice([0, 1, 2])
        elif r < 0.50:
            y = rng.randint(0, 1000)
        elif r < 0.70:
            y = rng.randint(0, 100000)
        else:
            y = rng.randint(0, 1000000000)

        rk = rng.random()
        if rk < 0.20:
            p = 0
        elif rk < 0.45:
            p = rng.choice([1, 2, 3])
        elif rk < 0.70:
            p = rng.randint(1, 10)
        else:
            p = rng.randint(1, 20)

        lines.append(f"{y} {p}")
        for _ in range(p):
            rs = rng.random()
            if rs < 0.30:
                s = rng.choice([1, 2, 5, y if y >= 1 else 1])
                if s < 1:
                    s = 1
            elif rs < 0.55:
                s = rng.randint(1, 100)
            elif rs < 0.75:
                if y >= 1:
                    s = rng.randint(max(1, y - 50), y)
                else:
                    s = rng.randint(1, 100)
            else:
                if y >= 1:
                    s = rng.randint(y + 1, y + 1000)
                else:
                    s = rng.randint(1, 1000)
            s = max(1, min(s, 1000000000))

            h = rng.randint(1, 5000)

            ri = rng.random()
            if ri < 0.25:
                i = rng.choice([1, 2, 3])
            elif ri < 0.50:
                i = rng.randint(1, 8)
            else:
                i = rng.randint(1, 20)

            rk2 = rng.random()
            if rk2 < 0.30:
                k = rng.choice([1, 2, 10])
            else:
                k = rng.randint(1, 10)

            lines.append(f"{s} {h} {i} {k}")
            for _ in range(i):
                ra = rng.random()
                if ra < 0.25:
                    a = rng.choice([1, 100])
                else:
                    a = rng.randint(1, 100)

                rb = rng.random()
                if rb < 0.25:
                    b = rng.choice([1, 100])
                else:
                    b = rng.randint(1, 100)

                rc = rng.random()
                if rc < 0.25:
                    c = rng.choice([1, 100])
                else:
                    c = rng.randint(1, 100)

                rd = rng.random()
                if rd < 0.30:
                    d = rng.choice([1, 1000])
                else:
                    d = rng.randint(1, 1000)

                re = rng.random()
                if re < 0.25:
                    e = rng.choice([1, 10])
                else:
                    e = rng.randint(1, 10)

                lines.append(f"{a} {b} {c} {d} {e}")

    sys.stdout.write("\n".join(lines) + "\n")


main()
