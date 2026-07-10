import sys
import random
import string


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Small scale so the O(n^2) brute force finishes well under 1s, but covers
    # the boundary cases: length-1 strings, all-same chars (max exponent),
    # periodic strings, and aperiodic strings (answer 1).
    num_lines = rng.randint(1, 20)
    lines = []

    for _ in range(num_lines):
        mode = rng.choice(["single", "repeat", "repeat_plus_tail", "random"])

        if mode == "single":
            # Length-1 string: answer is always 1.
            c = rng.choice(string.ascii_letters + string.digits)
            lines.append(c)

        elif mode == "repeat":
            # s = a^k for a random non-empty base a -> answer == k.
            base_len = rng.randint(1, 8)
            base = "".join(rng.choice(string.ascii_letters) for _ in range(base_len))
            k = rng.randint(1, 12)
            lines.append(base * k)

        elif mode == "repeat_plus_tail":
            # Build a^k then truncate to a non-multiple length so the answer
            # collapses to 1 (aperiodic w.r.t. any divisor), exercising the
            # "n % len != 0 / built != s" branches of the brute force.
            base_len = rng.randint(1, 8)
            base = "".join(rng.choice(string.ascii_letters) for _ in range(base_len))
            k = rng.randint(2, 12)
            s = base * k
            # Trim between 1 and base_len-1 chars (keep at least one full repeat
            # so the string is clearly not a clean power).
            trim = rng.randint(1, max(1, base_len - 1))
            s = s[:len(s) - trim]
            if len(s) == 0:
                s = base
            lines.append(s)

        else:  # random
            length = rng.randint(1, 40)
            s = "".join(rng.choice(string.ascii_letters) for _ in range(length))
            lines.append(s)

    lines.append(".")

    sys.stdout.write("\n".join(lines) + "\n")


main()
