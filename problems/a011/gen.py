import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    letters = [chr(c) for c in range(ord('A'), ord('Z') + 1)] + \
              [chr(c) for c in range(ord('a'), ord('z') + 1)]
    nonletters = list("0123456789 .,!?;:'\"-()[]{}@#$%^&*\t")

    nlines = rng.randint(1, 8)
    lines = []
    for _ in range(nlines):
        t = rng.randint(0, 5)
        if t == 0:
            # 空行
            lines.append("")
        elif t == 1:
            # 只有非字母（含全數字、全標點）→ 0 字
            L = rng.randint(0, 6)
            lines.append("".join(rng.choice(nonletters) for _ in range(L)))
        elif t == 2:
            # 單一字母 → 1 字
            lines.append(rng.choice(letters))
        elif t == 3:
            # 一個連續字母組成的字（無分隔）→ 1 字
            L = rng.randint(1, 10)
            lines.append("".join(rng.choice(letters) for _ in range(L)))
        elif t == 4:
            # 多個字，用各種非字母分隔
            nwords = rng.randint(1, 6)
            parts = []
            for w in range(nwords):
                if w > 0:
                    parts.append("".join(rng.choice(nonletters)
                                         for _ in range(rng.randint(1, 3))))
                parts.append("".join(rng.choice(letters)
                                     for _ in range(rng.randint(1, 8))))
            # 前後也可能有非字母
            if rng.random() < 0.5:
                parts.insert(0, "".join(rng.choice(nonletters)
                                        for _ in range(rng.randint(1, 3))))
            if rng.random() < 0.5:
                parts.append("".join(rng.choice(nonletters)
                                     for _ in range(rng.randint(1, 3))))
            lines.append("".join(parts))
        else:
            # 完全隨機混合
            L = rng.randint(0, 20)
            buf = []
            for _ in range(L):
                if rng.random() < 0.6:
                    buf.append(rng.choice(letters))
                else:
                    buf.append(rng.choice(nonletters))
            lines.append("".join(buf))

    out = "\n".join(lines)
    sys.stdout.write(out)
    sys.stdout.write("\n")


main()
