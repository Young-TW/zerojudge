import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    mode = rng.randint(0, 9)

    if mode == 0:
        # n = 1 (single piece) boundary: always Yes if area matches
        n = 1
        X = rng.randint(1, 6)
        Y = rng.randint(1, 6)
        parts = [X * Y]
    elif mode == 1:
        # n = 1 but area mismatch -> No
        n = 1
        X = rng.randint(1, 6)
        Y = rng.randint(1, 6)
        parts = [X * Y + 1]
    elif mode == 2:
        # n equals total cells (all 1x1) -> Yes
        X = rng.randint(1, 4)
        Y = rng.randint(1, 4)
        total = X * Y
        n = total
        parts = [1] * n
    elif mode == 3:
        # thin bar: one dimension = 1
        X = 1
        Y = rng.randint(2, 8)
        total = X * Y
        n = rng.randint(2, min(total, 5))
        cuts = sorted(rng.sample(range(1, total), n - 1))
        parts = []
        prev = 0
        for c in cuts:
            parts.append(c - prev)
            prev = c
        parts.append(total - prev)
        rng.shuffle(parts)
    elif mode == 4:
        # random valid partition, sometimes perturbed to be unsolvable
        X = rng.randint(2, 6)
        Y = rng.randint(2, 6)
        total = X * Y
        n = rng.randint(2, min(total, 6))
        cuts = sorted(rng.sample(range(1, total), n - 1))
        parts = []
        prev = 0
        for c in cuts:
            parts.append(c - prev)
            prev = c
        parts.append(total - prev)
        rng.shuffle(parts)
        if rng.random() < 0.4:
            i = rng.randrange(n)
            parts[i] += 1
    elif mode == 5:
        # square bar, prime total (few divisors) stress
        X = rng.randint(2, 5)
        Y = X
        total = X * Y
        n = rng.randint(2, min(total, 5))
        cuts = sorted(rng.sample(range(1, total), n - 1))
        parts = []
        prev = 0
        for c in cuts:
            parts.append(c - prev)
            prev = c
        parts.append(total - prev)
        rng.shuffle(parts)
    elif mode == 6:
        # area mismatch (sum != X*Y) -> guaranteed No
        X = rng.randint(2, 6)
        Y = rng.randint(2, 6)
        n = rng.randint(2, 5)
        parts = [rng.randint(1, X * Y) for _ in range(n)]
    elif mode == 7:
        # n=2 split: Yes iff one part area divisible properly
        X = rng.randint(2, 6)
        Y = rng.randint(2, 6)
        total = X * Y
        # pick a valid cut area
        divs = [c * Y for c in range(1, X)] + [X * r for r in range(1, Y)]
        if divs and rng.random() < 0.6:
            a = rng.choice(divs)
            parts = [a, total - a]
        else:
            parts = [rng.randint(1, total - 1), total - rng.randint(1, total - 1)]
            if sum(parts) != total:
                parts[1] = total - parts[0]
        n = 2
        rng.shuffle(parts)
    elif mode == 8:
        # a piece area larger than total or impossible shape
        X = rng.randint(2, 5)
        Y = rng.randint(2, 5)
        total = X * Y
        n = rng.randint(2, 4)
        parts = [rng.randint(1, total + 3) for _ in range(n)]
    else:
        # general small case, mix of valid/invalid
        X = rng.randint(1, 7)
        Y = rng.randint(1, 7)
        total = X * Y
        if total == 0:
            total = 1
            X = 1
            Y = 1
        n = rng.randint(1, min(total, 7))
        if n > total:
            n = total
        cuts = sorted(rng.sample(range(1, total), n - 1)) if n > 1 else []
        parts = []
        prev = 0
        for c in cuts:
            parts.append(c - prev)
            prev = c
        parts.append(total - prev)
        rng.shuffle(parts)
        if rng.random() < 0.35:
            i = rng.randrange(n)
            parts[i] += 1

    lines = [str(n), f"{X} {Y}", " ".join(map(str, parts)), "0"]
    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
