import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Small scale so brute force finishes in <1s, but cover edge cases.
    # Number of distinct printed strings: keep modest.
    # Strategy: build an input string using letters, B, P.
    # Ensure every P prints a non-empty string (slot non-empty before P).
    # Ensure B never pops an empty slot.

    alpha = "abcdefghijklmnopqrstuvwxyz"

    # Decide how many P operations (printed strings).
    num_prints = rng.randint(1, 8)

    # Build the input operation string.
    ops = []
    slot_len = 0
    prints_done = 0
    max_steps = 200  # cap total operations

    steps = 0
    while prints_done < num_prints and steps < max_steps:
        steps += 1
        # Choose op: letter, B, or P
        # If slot empty, can't B or P -> must add letter.
        choices = []
        if slot_len == 0:
            choices = ["letter"]
        else:
            choices = ["letter", "B"]
            # P only if we still need prints; bias to ensure we finish prints
            if prints_done < num_prints:
                choices.extend(["P"])

        op = rng.choice(choices)
        if op == "letter":
            ops.append(rng.choice(alpha))
            slot_len += 1
        elif op == "B":
            ops.pop()
            slot_len -= 1
        else:  # P
            ops.append("P")
            prints_done += 1

    # Guarantee at least one print produced (boundary: at least 1 string).
    if prints_done == 0:
        ops.append(rng.choice(alpha))
        ops.append("P")
        prints_done = 1

    input_str = "".join(ops)

    # Number of printed strings equals prints_done.
    n = prints_done

    # Queries: x,y in [1,n]. Keep small.
    m = rng.randint(1, 10)

    out = []
    out.append(input_str)
    out.append(str(m))
    for _ in range(m):
        x = rng.randint(1, n)
        y = rng.randint(1, n)
        out.append(f"{x} {y}")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
