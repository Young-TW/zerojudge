import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # Build a list of test cases. Each case is (initial_list, ops) where ops is
    # a list of either ("add", value) or ("max",). Scale kept small so the
    # brute force (linear-scan per op) runs well under 1 second, but boundary
    # conditions are covered.

    cases = []

    # --- Edge cases (fixed, exhaustive of small boundaries) ---

    # 1) Empty start, no ops: only final "It's empty!" printed.
    cases.append(([], []))

    # 2) Empty start, single add, single max.
    cases.append(([], [("add", 5), ("max",)]))

    # 3) Empty start, max on empty (prints It's empty!), then add.
    cases.append(([], [("max",), ("add", 7), ("max",)]))

    # 4) Single element start, drain it then keep asking.
    cases.append(([42], [("max",), ("max",), ("max",)]))

    # 5) Drain everything, then refill.
    cases.append(([3, 2, 1],
                  [("max",), ("max",), ("max",),      # drain 3,2,1
                   ("max",),                          # empty
                   ("add", 8), ("max",),              # add 8, take 8
                   ("max",),                          # empty
                   ("add", 20), ("max",),             # add 20, take 20
                   ("max",)]))                        # empty -> mirrors sample case 2 tail

    # 6) Duplicate max values: removing one max at a time.
    cases.append(([5, 5, 5, 5], [("max",), ("max",), ("max",), ("max",)]))

    # 7) Negative numbers (problem says positive ints, but we keep a mild
    #    negative test to be safe about comparisons; brute handles them).
    # Actually the problem states positive integers, so skip negatives to stay
    # strictly legal. Replace with zeros/ones boundary instead.
    cases.append(([0, 0, 0], [("max",), ("max",), ("max",), ("max",)]))

    # 8) All adds, no max; final sorted descending output only.
    cases.append(([], [("add", 3), ("add", 1), ("add", 4), ("add", 1), ("add", 5)]))

    # 9) Interleaved adds and maxes with ties at the boundary value.
    cases.append(([1, 2, 3],
                  [("add", 3), ("max",),    # 3 (one of two 3s)
                   ("add", 3), ("max",),    # 3
                   ("max",),                # 3
                   ("max",), ("max",)]))    # 2, 1 -> final empty

    # --- Small random cases ---

    def rand_case(max_init, max_ops, val_lo, val_hi):
        n_init = rng.randint(0, max_init)
        init = [rng.randint(val_lo, val_hi) for _ in range(n_init)]
        n_ops = rng.randint(0, max_ops)
        ops = []
        for _ in range(n_ops):
            if rng.random() < 0.5:
                ops.append(("add", rng.randint(val_lo, val_hi)))
            else:
                ops.append(("max",))
        return (init, ops)

    # Small, mostly small values.
    for _ in range(6):
        cases.append(rand_case(8, 12, 1, 10))

    # Slightly larger initial + many ops, small value range (more ties).
    for _ in range(4):
        cases.append(rand_case(20, 30, 1, 6))

    # Larger value range, few ops.
    for _ in range(3):
        cases.append(rand_case(6, 8, 1, 100000))

    # Push the brute a little: moderate n and m, many maxes draining.
    # n<=30000, m<=10000 per problem, but we cap small for brute timing.
    cases.append(rand_case(40, 60, 1, 100))

    # Near-worst for brute: lots of adds then a drain (linear scan each time).
    big_init = [rng.randint(1, 100) for _ in range(60)]
    big_ops = [("add", rng.randint(1, 100)) for _ in range(60)] + \
              [("max",)] * 120
    rng.shuffle(big_ops)
    cases.append((big_init, big_ops))

    # --- Emit in the problem's input format ---
    out_lines = []
    out_lines.append(str(len(cases)))
    for init, ops in cases:
        n = len(init)
        m = len(ops)
        out_lines.append("%d %d" % (n, m))
        if init:
            out_lines.append(" ".join(str(x) for x in init))
        else:
            # n == 0: still emit a (possibly empty) line for the initial
            # numbers. Emitting an empty line is the natural reading; many
            # judges accept whitespace-flexible reading. To be safe and
            # unambiguous we instead just emit nothing extra here, since
            # scanf/iostream skip whitespace and n=0 means no tokens to read.
            pass
        for op in ops:
            if op[0] == "add":
                out_lines.append("1 %d" % op[1])
            else:
                out_lines.append("2")

    sys.stdout.write("\n".join(out_lines) + "\n")


if __name__ == "__main__":
    main()
