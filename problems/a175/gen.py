import sys
import random


def gen_group(rng):
    lines = []

    r = rng.random()
    if r < 0.15:
        m = 1
    elif r < 0.30:
        m = rng.randint(2, 10)
    elif r < 0.40:
        m = 200
    else:
        m = rng.randint(1, 200)

    k = rng.randint(1, 50)
    lines.append(f"{k} {m}")

    inserted = set()

    for _ in range(k):
        if inserted:
            op = rng.choice([1, 2, 3])
        else:
            op = rng.choice([1, 1, 3])

        if op == 1:
            r2 = rng.random()
            if r2 < 0.10:
                n = 0
            elif r2 < 0.15:
                n = (2 ** 31) - 2
            else:
                n = rng.randint(0, 1000)
            attempts = 0
            while n in inserted and attempts < 30:
                n = rng.randint(0, 1000)
                attempts += 1
            inserted.add(n)
            lines.append(f"1 {n}")
        elif op == 2:
            r2 = rng.random()
            if r2 < 0.25:
                n = rng.randint(0, 1000)
                while n in inserted:
                    n = rng.randint(0, 1000)
                lines.append(f"2 {n}")
            else:
                n = rng.choice(list(inserted))
                inserted.discard(n)
                lines.append(f"2 {n}")
        else:
            lines.append("3")

    return lines


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    num_groups = rng.choice([1, 1, 1, 1, 2, 3])
    all_lines = []
    for _ in range(num_groups):
        all_lines.extend(gen_group(rng))

    print("\n".join(all_lines))


if __name__ == "__main__":
    main()
