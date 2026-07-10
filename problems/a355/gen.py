import sys
import random


def main():
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    ncases = rnd.randint(1, 2)
    blocks = []
    for _ in range(ncases):
        n = rnd.randint(2, 8)
        t = rnd.randint(1, 4)
        lines = ["%d %d" % (n, t)]
        for _ in range(t):
            m = rnd.randint(1, 7)
            choice = rnd.randint(0, 2)
            if choice == 0:
                pat = [rnd.randint(1, n) for _ in range(m)]
            elif choice == 1:
                v = rnd.randint(1, n)
                pat = [v] * m
            else:
                if m <= n:
                    perm = list(range(1, n + 1))
                    rnd.shuffle(perm)
                    pat = perm[:m]
                else:
                    pat = [rnd.randint(1, n) for _ in range(m)]
            lines.append(str(m) + " " + " ".join(map(str, pat)))
        blocks.append("\n".join(lines))

    sys.stdout.write("\n\n".join(blocks) + "\n")


if __name__ == "__main__":
    main()
