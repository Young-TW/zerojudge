import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Problem constraints: each test line has 4..10 uppercase letters, at most
    # 50 test cases per input. We keep the batch small (<= ~30 lines) so the
    # brute force (10000 ST * reduction per line) finishes well under a second.

    lines = []
    r = rng.randint(1, 6)

    if r == 1:
        # Minimum length boundary: exactly 4 letters each.
        for _ in range(rng.randint(4, 8)):
            n = 4
            lines.append("".join(rng.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
                                 for _ in range(n)))

    elif r == 2:
        # Maximum length boundary: exactly 10 letters each.
        for _ in range(rng.randint(4, 8)):
            n = 10
            lines.append("".join(rng.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
                                 for _ in range(n)))

    elif r == 3:
        # All-same-letter strings (e.g. AAAAAAAA) -> degenerate reduction.
        ch = rng.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
        n = rng.randint(4, 10)
        lines.append(ch * n)
        ch2 = rng.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
        n2 = rng.randint(4, 10)
        lines.append(ch2 * n2)

    elif r == 4:
        # Mixed lengths spanning the full 4..10 range.
        cnt = rng.randint(6, 12)
        for _ in range(cnt):
            n = rng.randint(4, 10)
            lines.append("".join(rng.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
                                 for _ in range(n)))

    elif r == 5:
        # Hand-picked near-edge seeds likely to produce small or boundary ST,
        # including the sample-style inputs (JYFTYR, ABCDEF, ...).
        pool = [
            "JYFTYR",
            "ABCDEF",
            "YTHHLS",
            "YTHLML",
            "LYXM",
            "JYFLY",
            "CBTZX",
            "LXYZLE",
            "LXYLYR",
            "QWERTY",
            "AAAA",
            "ZZZZ",
            "AZAZ",
            "JZJZ",
        ]
        rng.shuffle(pool)
        k = rng.randint(4, min(len(pool), 8))
        lines.extend(pool[:k])

    else:
        # General random: a handful of lines with lengths drawn from 4..10.
        cnt = rng.randint(5, 10)
        for _ in range(cnt):
            n = rng.randint(4, 10)
            lines.append("".join(rng.choice("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
                                 for _ in range(n)))

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
