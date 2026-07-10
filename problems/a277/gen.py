import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # 測資筆數: 取小, 讓暴力 O(n^2 log n) 跑得完
    num_cases = rng.randint(1, 6)
    lines = []

    for _ in range(num_cases):
        # N: 題目要求 2<=n<=100000, 但這裡刻意取小以利暴力
        # 邊界涵蓋: 最小 n=2, 偶爾測稍大但仍受控
        r = rng.random()
        if r < 0.20:
            N = rng.choice([2, 3, 4])             # 最小邊界
        elif r < 0.35:
            N = rng.randint(2, 30)                # 小型一般
        else:
            N = rng.randint(2, 120)               # 一般規模, n^2 約 14400 對, OK

        # Ai: 0<Ai<=1000000000
        r = rng.random()
        if r < 0.15:
            # 全相同: 所有差都是 0, 中位數必為 0
            v = rng.randint(1, 1000000000)
            A = [v] * N
        elif r < 0.30:
            # 小範圍值: 容易湊出重複差值
            A = [rng.randint(1, 10) for _ in range(N)]
        elif r < 0.45:
            # 二值: 測試大量 0 與單一非零差值
            x = rng.randint(1, 1000000000)
            y = rng.randint(1, 1000000000)
            while y == x:
                y = rng.randint(1, 1000000000)
            A = [rng.choice([x, y]) for _ in range(N)]
        elif r < 0.60:
            # 極值邊界: 包含 1 與 1000000000
            A = [rng.choice([1, 1000000000]) for _ in range(N)]
        elif r < 0.80:
            # 等差數列 (排序後差值規律)
            start = rng.randint(1, 1000)
            step = rng.randint(1, 1000)
            A = [start + i * step for _ in range(N)]
            A = [min(v, 1000000000) for v in A]
        else:
            # 完全隨機大範圍
            A = [rng.randint(1, 1000000000) for _ in range(N)]

        # 打亂順序 (題目未說明已排序, 順序應任意)
        rng.shuffle(A)

        lines.append(str(N))
        lines.append(" ".join(map(str, A)))

    sys.stdout.write("\n".join(lines) + "\n")


main()
