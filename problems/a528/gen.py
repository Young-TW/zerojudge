import sys
import random


def rand_bigint_str(rng, max_digits=100):
    length = rng.randint(1, max_digits)
    digits = [str(rng.randint(0, 9)) for _ in range(length)]
    if digits[0] == '0':
        digits[0] = str(rng.randint(1, 9))
    return ''.join(digits)


def rand_number(rng):
    r = rng.random()
    if r < 0.10:
        return "0"
    if r < 0.20:
        s = str(rng.randint(1, 999))
        return "-" + s if rng.random() < 0.5 else s
    if r < 0.30:
        return rand_bigint_str(rng, 100)
    if r < 0.40:
        return "-" + rand_bigint_str(rng, 100)
    if r < 0.55:
        return rand_bigint_str(rng, 18)
    if r < 0.70:
        return "-" + rand_bigint_str(rng, 18)
    s = rand_bigint_str(rng, 100)
    return "-" + s if rng.random() < 0.5 else s


def gen_case(rng, out):
    r = rng.random()
    if r < 0.30:
        n = rng.randint(1, 3)
    elif r < 0.70:
        n = rng.randint(1, 20)
    else:
        n = rng.randint(1, 50)
    out.append(str(n))
    nums = []
    for _ in range(n):
        if nums and rng.random() < 0.15:
            nums.append(rng.choice(nums))
        else:
            nums.append(rand_number(rng))
    out.extend(nums)


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)
    cases = rng.randint(1, 2)
    out = []
    for _ in range(cases):
        gen_case(rng, out)
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
