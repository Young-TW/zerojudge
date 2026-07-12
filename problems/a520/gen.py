import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # Pool of non-space characters: letters, digits, punctuation (no TAB, no newline).
    # Per problem: letters, digits, punctuation, and spaces. No trailing spaces.
    letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    digits = "0123456789"
    puncts = ".,!?:;\"'()-"
    nonspace = letters + digits + puncts

    lines = []

    r = rng.randint(1, 6)

    if r == 1:
        # Boundary cases: mix of tiny edge lines.
        # - empty-ish: single non-space char (no spaces at all -> answer 0)
        # - single space between two tokens (maxRun=1 -> 0)
        # - two consecutive spaces (maxRun=2 -> 1)
        # - long run of leading spaces (maxRun large)
        # - no spaces, just tokens
        lines.append("A")                       # 0
        lines.append("A B")                     # 0
        lines.append("A  B")                    # 1
        lines.append("  A")                     # 1 (maxRun=2)
        lines.append("    A")                   # 2 (maxRun=4)
        lines.append("A    B  C     D")         # 3 (maxRun=5)
        lines.append("         Goodbye!")       # 4 (maxRun=9 leading)
        lines.append("x")                       # 0
        lines.append("x y z")                   # 0
        lines.append("         x")              # 4 (9 leading spaces)

    elif r == 2:
        # Lines made entirely of leading spaces followed by one token.
        # Exercises long runs to test the ceil(log2) behavior.
        for _ in range(8):
            run = rng.randint(0, 40)
            tok_len = rng.randint(1, 5)
            tok = "".join(rng.choice(nonspace) for _ in range(tok_len))
            lines.append(" " * run + tok)

    elif r == 3:
        # Lines with multiple runs of spaces between tokens of varying lengths.
        for _ in range(8):
            ntok = rng.randint(1, 6)
            parts = []
            for _ in range(ntok):
                tl = rng.randint(1, 4)
                parts.append("".join(rng.choice(nonspace) for _ in range(tl)))
            seps = []
            for _ in range(ntok - 1):
                seps.append(rng.randint(1, 25))
            line = parts[0]
            for j in range(ntok - 1):
                line += " " * seps[j] + parts[j + 1]
            # Sometimes add leading spaces.
            if rng.random() < 0.5:
                line = " " * rng.randint(1, 30) + line
            lines.append(line)

    elif r == 4:
        # Stress the maxRun answer directly: a few lines whose longest run is
        # exactly a power of two or one-off, so brute must iterate many steps.
        for _ in range(6):
            run = rng.choice([1, 2, 3, 4, 7, 8, 9, 15, 16, 17, 31, 32, 33, 50])
            tok = "".join(rng.choice(nonspace) for _ in range(rng.randint(1, 3)))
            tail = "".join(rng.choice(nonspace) for _ in range(rng.randint(1, 3)))
            line = " " * run + tok + " " * rng.randint(0, run) + tail
            lines.append(line)

    elif r == 5:
        # Dense small random lines, broad coverage.
        for _ in range(12):
            length = rng.randint(1, 40)
            chars = []
            for _ in range(length):
                if rng.random() < 0.5:
                    chars.append(rng.choice(nonspace))
                else:
                    chars.append(" ")
            line = "".join(chars)
            # Strip trailing spaces (problem guarantees no trailing spaces).
            line = line.rstrip(" ")
            if line == "":
                line = "".join(rng.choice(nonspace) for _ in range(rng.randint(1, 3)))
            lines.append(line)

    else:
        # General: moderate random lines with a bias toward spaces.
        for _ in range(10):
            length = rng.randint(1, 60)
            chars = []
            for _ in range(length):
                if rng.random() < 0.55:
                    chars.append(" ")
                else:
                    chars.append(rng.choice(nonspace))
            line = "".join(chars).rstrip(" ")
            if line == "":
                line = "".join(rng.choice(nonspace) for _ in range(rng.randint(1, 3)))
            lines.append(line)

    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
