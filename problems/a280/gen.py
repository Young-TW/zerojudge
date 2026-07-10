import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    num_cases = rng.randint(1, 6)
    lines = []

    for _ in range(num_cases):
        # n: 目標階, 1..100, 偏邊界
        r = rng.random()
        if r < 0.25:
            n = rng.choice([1, 2, 99, 100])
        else:
            n = rng.randint(1, 100)

        # k: 傳送管道數, 取小讓暴力秒殺; 偶爾 0 (無法移動) 或邊界大值
        rk = rng.random()
        if rk < 0.15:
            k = 0                       # 完全沒有管道
        elif rk < 0.30:
            k = rng.choice([1, 2, 3])   # 極少
        elif rk < 0.45:
            k = rng.randint(0, 30)      # 中等
        else:
            k = rng.randint(0, 60)

        edges = []
        for _ in range(k):
            ra = rng.random()
            if ra < 0.35:
                a = 0                   # 從起點出發, 提高可達機率
            elif ra < 0.50:
                a = rng.choice([0, n])  # 起點或目標
            else:
                a = rng.randint(0, 100)

            rb = rng.random()
            if rb < 0.25:
                b = n                   # 直指目標
            elif rb < 0.45:
                b = rng.choice([0, n, 100])
            else:
                b = rng.randint(0, 100)

            edges.append((a, b))

        lines.append(f"{n} {k}")
        for a, b in edges:
            lines.append(f"{a} {b}")

    sys.stdout.write("\n".join(lines) + "\n")


main()
