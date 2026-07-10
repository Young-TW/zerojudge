import sys
import random


def main():
    seed = int(sys.argv[1])
    rng = random.Random(seed)

    # 全部可能的種類編號 0..100
    all_types = list(range(0, 101))

    def gen_section():
        # 隨機挑少數種類，規模刻意取小，但涵蓋邊界 (0 與 100 可能出現)
        rng.shuffle(all_types)
        k = rng.randint(0, 8)
        types = sorted(all_types[:k])
        lines = []
        for t in types:
            # 數目刻意取小，並偶爾為 0 (涵蓋邊界)
            n = rng.randint(0, 20)
            lines.append(f"{t} {n}")
        return lines

    init = gen_section()
    growth = gen_section()

    out = []
    out.extend(init)
    out.append("-1")
    out.extend(growth)
    out.append("-1")
    sys.stdout.write("\n".join(out) + "\n")


main()
