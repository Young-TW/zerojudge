import sys, random

def main():
    if len(sys.argv) != 2:
        return
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # seed 0: empty program
    if seed == 0:
        return

    # seed 1: minimal program (single END)
    if seed == 1:
        print("10 END")
        return

    # seed 2: maximal size, simple linear program without jumps
    if seed == 2:
        n = 100
        lines = [i * 10 for i in range(1, n + 1)]
        for ln in lines[:-1]:
            var = chr(rng.randint(0, 25) + ord('A'))
            val = rng.randint(0, 9999)
            print(f"{ln} {var}+{val}")
        print(f"{lines[-1]} END")
        return

    # general case
    n = rng.randint(1, 100)
    # unique line numbers within 1..3000
    line_nums = sorted(rng.sample(range(1, 3001), n))
    # ensure the last (largest) line is END
    statements = {}

    # helper to pick a later line number
    def later_idx(idx):
        if idx + 1 < len(line_nums):
            return rng.choice(line_nums[idx + 1 :])
        return None

    for idx, ln in enumerate(line_nums):
        if idx == len(line_nums) - 1:
            stmt = "END"
        else:
            typ = rng.random()
            var = chr(rng.randint(0, 25) + ord('A'))
            if typ < 0.4:  # add
                val = rng.randint(0, 9999)
                stmt = f"{var}+{val}"
            elif typ < 0.6:  # output
                stmt = f"{var} ?"
            elif typ < 0.8:  # go
                tgt = later_idx(idx)
                if tgt is None:
                    val = rng.randint(0, 9999)
                    stmt = f"{var}+{val}"
                else:
                    stmt = f"GO {tgt}"
            else:  # if
                tgt = later_idx(idx)
                if tgt is None:
                    val = rng.randint(0, 9999)
                    stmt = f"{var}+{val}"
                else:
                    val = rng.randint(0, 9999)
                    stmt = f"IF {var}={val} GO {tgt}"
        statements[ln] = stmt

    # output in random order (as input may be unsorted)
    ordered = list(statements.items())
    rng.shuffle(ordered)
    for ln, stmt in ordered:
        print(f"{ln} {stmt}")

if __name__ == "__main__":
    main()
