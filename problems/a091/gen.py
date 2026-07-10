import sys
import random


def main():
    seed = int(sys.argv[1])
    rnd = random.Random(seed)

    out = []
    size = 0
    num_ops = rnd.randint(1, 3000)

    for _ in range(num_ops):
        r = rnd.random()
        if size == 0:
            op = 1
        else:
            if r < 0.5:
                op = 1
            elif r < 0.75:
                op = 2
            else:
                op = 3

        if op == 1:
            b = rnd.random()
            if b < 0.1:
                n = 0
            elif b < 0.2:
                n = 2147483647
            elif b < 0.3:
                n = rnd.randint(0, 10)
            else:
                n = rnd.randint(0, 2147483647)
            out.append(f"1 {n}")
            size += 1
        elif op == 2:
            out.append("2")
            size -= 1
        else:
            out.append("3")
            size -= 1

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
