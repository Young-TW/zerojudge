import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # 小規模：n <= 15, m <= 8, w <= 8, v <= 10 —— 暴力解瞬間跑完。
    # 用數種模式刻意涵蓋邊界。
    mode = rng.randint(0, 8)

    if mode == 0:
        # 邊界：n = 1, m = 1（最小規模）
        n = 1
        m = 1
        S = rng.randint(1, 50)
        wmax = 6
        vmax = 10
    elif mode == 1:
        # 邊界：所有重量相同（W 的選擇退化為全選或全不選）
        n = rng.randint(2, 8)
        m = rng.randint(1, 5)
        S = rng.randint(1, 50)
        wmax = 6
        vmax = 10
    elif mode == 2:
        # 邊界：S = 1（Y 幾乎必 > S）
        n = rng.randint(1, 8)
        m = rng.randint(1, 5)
        S = 1
        wmax = 6
        vmax = 10
    elif mode == 3:
        # 邊界：S 極大（Y 必 < S，答案 = S - Y_max）
        n = rng.randint(1, 8)
        m = rng.randint(1, 5)
        S = rng.randint(500, 1000)
        wmax = 6
        vmax = 10
    elif mode == 4:
        # 邊界：區間全為單點 [i, i]
        n = rng.randint(2, 8)
        m = rng.randint(1, 5)
        S = rng.randint(1, 50)
        wmax = 6
        vmax = 10
    elif mode == 5:
        # 邊界：單一全區間 [1, n]
        n = rng.randint(2, 8)
        m = 1
        S = rng.randint(1, 50)
        wmax = 6
        vmax = 10
    elif mode == 6:
        # 邊界：重量全為 1（W=0 全選，W>=1 全不選）
        n = rng.randint(1, 8)
        m = rng.randint(1, 5)
        S = rng.randint(1, 50)
        wmax = 1
        vmax = 10
    elif mode == 7:
        # 邊界：價值可為 0
        n = rng.randint(1, 8)
        m = rng.randint(1, 5)
        S = rng.randint(1, 30)
        wmax = 6
        vmax = 5  # 含 0
    else:
        # 一般隨機
        n = rng.randint(1, 15)
        m = rng.randint(1, 8)
        S = rng.randint(1, 100)
        wmax = 8
        vmax = 10

    lines = [f"{n} {m} {S}"]

    if mode == 1:
        # 所有重量相同
        wv = rng.randint(1, wmax)
        for _ in range(n):
            lines.append(f"{wv} {rng.randint(1, vmax)}")
    elif mode == 6:
        # 重量全為 1
        for _ in range(n):
            lines.append(f"1 {rng.randint(1, vmax)}")
    elif mode == 7:
        # 價值含 0
        for _ in range(n):
            lines.append(f"{rng.randint(1, wmax)} {rng.randint(0, vmax)}")
    else:
        for _ in range(n):
            lines.append(f"{rng.randint(1, wmax)} {rng.randint(1, vmax)}")

    if mode == 4:
        # 單點區間
        for _ in range(m):
            i = rng.randint(1, n)
            lines.append(f"{i} {i}")
    elif mode == 5:
        # 全區間
        lines.append(f"1 {n}")
    else:
        for _ in range(m):
            a = rng.randint(1, n)
            b = rng.randint(a, n)
            lines.append(f"{a} {b}")

    sys.stdout.write("\n".join(lines) + "\n")


main()
