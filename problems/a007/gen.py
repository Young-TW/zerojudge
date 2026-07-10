import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    n = rng.randint(1, 8)
    lines = []
    for _ in range(n):
        t = rng.randint(0, 6)
        if t == 0:
            # 下界：2
            lines.append("2")
        elif t == 1:
            # 最小奇質數：3
            lines.append("3")
        elif t == 2:
            # 上界附近（含 2147483647 本身）
            base = 2147483647
            off = rng.randint(-20, 0)
            x = base + off
            if x < 2:
                x = 2
            lines.append(str(x))
        elif t == 3:
            # 小質數
            lines.append(str(rng.choice([2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31])))
        elif t == 4:
            # 小合數
            lines.append(str(rng.choice([4, 6, 8, 9, 10, 12, 14, 15, 21, 25, 27, 49, 121])))
        elif t == 5:
            # 小範圍隨機（暴力秒解）
            lines.append(str(rng.randint(2, 100000)))
        else:
            # 中範圍隨機（仍保證暴力在 1 秒內）
            lines.append(str(rng.randint(2, 10000000)))

    sys.stdout.write("\n".join(lines))
    sys.stdout.write("\n")


main()
