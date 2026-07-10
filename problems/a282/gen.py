import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    num_cases = rng.randint(1, 6)
    lines = []

    for _ in range(num_cases):
        r = rng.random()

        if r < 0.15:
            # 邊界：n=0，一本都沒讀過，答案必為 1
            lines.append("0")

        elif r < 0.30:
            # 邊界：連續從第 1 頁讀到第 k 頁，答案=k+1
            k = rng.randint(1, 30)
            lines.append(f"{k}")
            lines.append(" ".join(str(i) for i in range(1, k + 1)))

        elif r < 0.45:
            # 邊界：第 1 頁沒讀到，答案=1
            n = rng.randint(1, 30)
            pages = [rng.randint(2, 2000) for _ in range(n)]
            lines.append(f"{n}")
            lines.append(" ".join(str(p) for p in pages))

        elif r < 0.58:
            # 邊界：大量重複（含全部相同頁碼）
            n = rng.randint(1, 30)
            base = rng.randint(1, 2000)
            pages = [base if rng.random() < 0.7 else rng.randint(1, 2000) for _ in range(n)]
            lines.append(f"{n}")
            lines.append(" ".join(str(p) for p in pages))

        elif r < 0.70:
            # 邊界：涵蓋最小(1)與最大(2000)頁碼
            n = rng.randint(2, 30)
            pages = [1, 2000]
            pages += [rng.randint(1, 2000) for _ in range(n - 2)]
            rng.shuffle(pages)
            lines.append(f"{n}")
            lines.append(" ".join(str(p) for p in pages))

        else:
            # 一般隨機；偶爾放大 n 但仍保證暴力秒殺
            if rng.random() < 0.2:
                n = rng.randint(100, 300)
            else:
                n = rng.randint(1, 40)
            pages = [rng.randint(1, 2000) for _ in range(n)]
            lines.append(f"{n}")
            lines.append(" ".join(str(p) for p in pages))

    sys.stdout.write("\n".join(lines) + "\n")


main()
