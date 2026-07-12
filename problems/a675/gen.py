import sys
from random import Random

VAL = [1, 2, 4, 10, 20, 40]  # 5c, 10c, 20c, 50c, $1, $2 in 5c units


def gen_one(rng):
    mode = rng.randint(0, 5)
    if mode == 0:
        # very small counts, tiny target
        cnt = [rng.randint(0, 2) for _ in range(6)]
    elif mode == 1:
        # some denominations zeroed out
        cnt = [rng.randint(0, 4) for _ in range(6)]
        for _ in range(rng.randint(1, 3)):
            cnt[rng.randint(0, 5)] = 0
    elif mode == 2:
        # moderate counts
        cnt = [rng.randint(0, 5) for _ in range(6)]
    elif mode == 3:
        # larger counts (stress brute a bit)
        cnt = [rng.randint(1, 6) for _ in range(6)]
    elif mode == 4:
        # single denomination only
        cnt = [0] * 6
        cnt[rng.randint(0, 5)] = rng.randint(1, 8)
    else:
        # two denominations only
        cnt = [0] * 6
        i = rng.randint(0, 5)
        j = rng.randint(0, 5)
        while j == i:
            j = rng.randint(0, 5)
        cnt[i] = rng.randint(1, 6)
        cnt[j] = rng.randint(1, 6)

    total = sum(c * v for c, v in zip(cnt, VAL))
    while total == 0:
        cnt[rng.randint(0, 5)] = rng.randint(1, 3)
        total = sum(c * v for c, v in zip(cnt, VAL))

    maxu = min(total, 99)  # amount < $5.00 = 100 units, multiple of 5c
    r = rng.random()
    if r < 0.1:
        target = 1  # 0.05 minimum
    elif r < 0.2:
        target = maxu  # maximum affordable (or boundary)
    else:
        target = rng.randint(1, maxu)
    d = target / 20.0
    return cnt, d


def main():
    seed = int(sys.argv[1])
    rng = Random(seed)
    T = rng.randint(5, 15)
    lines = []
    for _ in range(T):
        cnt, d = gen_one(rng)
        lines.append(f"{' '.join(map(str, cnt))}  {d:.2f}")
    lines.append("0 0 0 0 0 0")
    sys.stdout.write('\n'.join(lines) + '\n')


if __name__ == '__main__':
    main()
