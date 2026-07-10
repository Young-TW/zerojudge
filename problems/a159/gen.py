import sys
import random


def luhn_sum(digits):
    """digits: list of ints, leftmost first."""
    total = 0
    L = len(digits)
    for i, v in enumerate(digits):
        pos_from_right = L - i  # 1-indexed from right
        if pos_from_right % 2 == 0:
            dv = v * 2
            total += (dv // 10) + (dv % 10)
        else:
            total += v
    return total


def random_digits(rng):
    """16 random digits, leftmost allowed to be 0 (problem only says digits)."""
    return [rng.randint(0, 9) for _ in range(16)]


def make_valid(rng):
    """Random 16 digits, force Luhn sum to end in 0."""
    digs = random_digits(rng)
    s = luhn_sum(digs)
    # adjust the rightmost (check) digit to make total a multiple of 10
    cur = digs[15]
    need = (-(s - cur)) % 10
    # choose among all check digits in [0,9] congruent to need mod 10
    candidates = [d for d in range(0, 10) if (d % 10) == need]
    digs[15] = rng.choice(candidates)
    return digs


def make_invalid(rng):
    """Random 16 digits whose Luhn sum does NOT end in 0."""
    digs = random_digits(rng)
    s = luhn_sum(digs)
    if s % 10 == 0:
        # bump rightmost digit by 1 (mod 10) to break validity
        digs[15] = (digs[15] + 1) % 10
    # verify
    assert luhn_sum(digs) % 10 != 0
    return digs


def fmt(digs):
    return f"{''.join(map(str, digs[0:4]))} {''.join(map(str, digs[4:8]))} {''.join(map(str, digs[8:12]))} {''.join(map(str, digs[12:16]))}"


def main():
    rng = random.Random(int(sys.argv[1]))

    # Small scale so brute runs well under 1s; cover boundaries:
    #   - N=1 (minimum), N small, and a slightly larger N
    #   - mix of valid / invalid / boundary all-zero card
    N = rng.randint(1, 12)
    print(N)

    # Guarantee at least one fully-zero card (sum 0 -> Valid) as a boundary.
    printed_zero = False
    # Guarantee at least one valid and one invalid when N >= 2.
    forced_valid = False
    forced_invalid = False

    for _ in range(N):
        r = rng.randint(0, 5)
        if r == 0 and not printed_zero:
            digs = [0] * 16
            printed_zero = True
        elif r == 1 or (not forced_valid and N >= 2):
            digs = make_valid(rng)
            forced_valid = True
        elif r == 2 or (not forced_invalid and N >= 2):
            digs = make_invalid(rng)
            forced_invalid = True
        else:
            digs = random_digits(rng)
        print(fmt(digs))


if __name__ == "__main__":
    main()
