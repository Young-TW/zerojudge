import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    out = []

    # 邊界導向的小規模測資，讓暴力解秒殺
    r = rng.random()
    if r < 0.15:
        n = 1                       # n=1 邊界：無法選兩家，答案必為 0
    elif r < 0.30:
        n = 2                       # n=2 邊界
    else:
        n = rng.randint(1, 60)

    k = rng.randint(1, 6)

    # p 偶爾為 0（幾乎沒有咖啡店符合），偶爾很大（全部符合）
    rp = rng.random()
    if rp < 0.20:
        p = 0
    elif rp < 0.40:
        p = 100                     # 全部咖啡店都符合
    else:
        p = rng.randint(0, 6)

    out.append(f"{n} {k} {p}")

    max_cost = max(p, 6)
    for _ in range(n):
        color = rng.randint(0, k - 1)
        # 偶爾刻意製造 cost<=p 或 cost>p 的情況以涵蓋邊界
        rc = rng.random()
        if rc < 0.30:
            cost = rng.randint(0, p)            # 必定符合
        elif rc < 0.60:
            cost = rng.randint(p + 1, p + 6)    # 必定不符合
        else:
            cost = rng.randint(0, max_cost)     # 隨機
        out.append(f"{color} {cost}")

    sys.stdout.write("\n".join(out) + "\n")


main()
