import sys
import random

ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def i2g(n):
    # natural G-code representation; "A" for 0
    if n == 0:
        return "A"
    r = []
    while n > 0:
        r.append(ALPHA[n % 26])
        n //= 26
    return "".join(reversed(r))


def rand_code(rnd, L):
    # Exactly L chars; mix in boundary values to cover edges.
    r = rnd.random()
    if r < 0.15:
        return "A" * L            # value 0 (all leading zeros)
    if r < 0.30:
        return "Z" * L            # max value -> forces carry/overflow
    if r < 0.45:
        # leading A's then random (fewer significant digits)
        k = rnd.randint(1, L)
        head = "A" * (L - k)
        tail = "".join(rnd.choice(ALPHA) for _ in range(k))
        return head + tail
    return "".join(rnd.choice(ALPHA) for _ in range(L))


def main():
    rnd = random.Random(int(sys.argv[1]))
    out = []
    num_cases = rnd.randint(1, 5)
    for _ in range(num_cases):
        # L in 1..28: keeps brute trivial (<1s) but sometimes yields a
        # 2-char G-code length spec (e.g. L=26 -> "BA") covering the
        # "three-or-fewer-digit" length field.
        L = rnd.randint(1, 28)
        out.append(i2g(L))
        out.append(rand_code(rnd, L))
        out.append(rand_code(rnd, L))
    out.append("A")               # terminator
    sys.stdout.write("\n".join(out) + "\n")


main()
