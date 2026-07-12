import sys
import random


def scompat(a, b):
    # Is set `a` (placed above `b`) compatible with `b`?  Uses the sorted
    # column condition only to *validate* that a generated case satisfies the
    # problem's guarantee ("at least two of the m sets are compatible").  This
    # is not the brute force; it just keeps the generator's output legal.
    sa = sorted(a)
    sb = sorted(b)
    return all(x < y for x, y in zip(sa, sb))


def has_pair(sets):
    mm = len(sets)
    for i in range(mm):
        for j in range(mm):
            if i != j and scompat(sets[i], sets[j]):
                return True
    return False


def repair(sets, rng):
    # Force at least one compatible pair if the random sets happen to have
    # none, while keeping every value within [1, 50000].
    if has_pair(sets):
        return sets
    base = sets[0]
    mx = max(base)
    if mx + 5 <= 50000:
        d = rng.randint(1, 5)
        sets[1] = [x + d for x in base]
    else:
        mn = min(base)
        d = rng.randint(1, min(5, mn - 1))
        if d < 1:
            d = 1
        sets[1] = [x - d for x in base]
    return sets


def rand_case(rng, n, m, lo, hi):
    sets = [[rng.randint(lo, hi) for _ in range(n)] for _ in range(m)]
    sets = repair(sets, rng)
    return (n, sets)


def cap_m(n):
    # Keep the brute force's (n!)^k * orderings well under 1 second.
    if n == 1:
        return 8
    if n == 2:
        return 8
    if n == 3:
        return 6
    return 4  # n == 4


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    cases = []  # each item: (n, list_of_sets)

    # --- Fixed edge / boundary cases ---

    # 1. Sample case 1.
    cases.append((3, [[6, 3, 5], [1, 4, 2]]))
    # 2. Sample case 2.
    cases.append((2, [[3, 1], [2, 4], [6, 5]]))
    # 3. Minimal: m=2, n=1, compatible singletons.
    cases.append((1, [[5], [9]]))
    # 4. m=2, n=1, equal values (not compatible) -> repaired to legal.
    cases.append((1, repair([[7], [7]], rng)))
    # 5. n=1 partial order with duplicates; chain 3,5,8,10 (kmax=4).
    cases.append((1, [[5], [5], [8], [3], [10], [8]]))
    # 6. n=1 eight singletons; longest increasing subsequence exercised.
    cases.append((1, [[i] for i in [2, 5, 3, 9, 1, 7, 4, 6]]))
    # 7. Forced full chain m=5, n=4 (kmax=5).
    cases.append((4, [[1 + t + c for c in range(4)] for t in range(0, 20, 4)]))
    # 8. Duplicate sets alongside a chain (kmax=3).
    cases.append((3, [[1, 2, 3], [1, 2, 3], [2, 3, 4], [3, 4, 5]]))
    # 9. Large values near the 50000 ceiling, n=3, m=4.
    cases.append((3, repair(
        [[rng.randint(40000, 50000) for _ in range(3)] for _ in range(4)], rng)))
    # 10. n=4, m=2 identical -> repaired.
    cases.append((4, repair(
        [[rng.randint(1, 20) for _ in range(4)] for _ in range(2)], rng)))

    # --- Small random cases covering each n with its safe m cap ---

    fixed_specs = [
        (2, rng.randint(2, cap_m(2)), 1, 50),
        (3, rng.randint(2, cap_m(3)), 1, 30),
        (4, rng.randint(2, cap_m(4)), 1, 20),
        (2, rng.randint(2, cap_m(2)), 1, 6),     # tight range -> many ties
        (1, rng.randint(2, cap_m(1)), 1, 100),
        (3, rng.randint(2, cap_m(3)), 40000, 50000),
        (2, cap_m(2), 1, 4),                     # max m for n=2, tiny range
        (4, cap_m(4), 1, 50),                    # max m for n=4
        (3, cap_m(3), 1, 10),                    # max m for n=3
        (1, cap_m(1), 1, 8),                     # max m for n=1
    ]
    for n_, m_, lo, hi in fixed_specs:
        cases.append(rand_case(rng, n_, m_, lo, hi))

    # --- Extra random cases with mixed n, m, value ranges ---

    range_opts = [(1, 10), (1, 50), (1, 500), (40000, 50000)]
    for _ in range(6):
        n_ = rng.randint(1, 4)
        m_ = rng.randint(2, cap_m(n_))
        lo, hi = rng.choice(range_opts)
        cases.append(rand_case(rng, n_, m_, lo, hi))

    # --- Emit in the problem's input format ---
    out = [str(len(cases))]
    for n_, sets in cases:
        out.append("%d %d" % (len(sets), n_))
        for s in sets:
            out.append(" ".join(str(x) for x in s))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
