import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    out = []
    T = rng.randint(1, 6)
    for _ in range(T):
        # 小規模：n 在 [1,8]，座標在 [0,8]，長度在 [1,8]，暴力解瞬間跑完
        n = rng.randint(1, 8)
        out.append(str(n))
        carpets = []
        maxc = 0
        for _ in range(n):
            a = rng.randint(0, 8)
            b = rng.randint(0, 8)
            g = rng.randint(1, 8)
            k = rng.randint(1, 8)
            carpets.append((a, b, g, k))
            out.append(f"{a} {b} {g} {k}")
            maxc = max(maxc, a + g, b + k)

        r = rng.random()
        if r < 0.45 and carpets:
            # 涵蓋邊界：挑某張地毯的四個頂點或四條邊上的點
            a, b, g, k = rng.choice(carpets)
            x, y = rng.choice([
                (a, b), (a + g, b), (a, b + k), (a + g, b + k),   # 四個頂點
                (a, rng.randint(b, b + k)),                       # 左邊
                (a + g, rng.randint(b, b + k)),                   # 右邊
                (rng.randint(a, a + g), b),                       # 下邊
                (rng.randint(a, a + g), b + k),                   # 上邊
            ])
        elif r < 0.65 and carpets:
            # 地毯內部某點
            a, b, g, k = rng.choice(carpets)
            x = rng.randint(a, a + g)
            y = rng.randint(b, b + k)
        else:
            # 任意點（可能沒被覆蓋 -> -1）
            x = rng.randint(0, maxc + 4)
            y = rng.randint(0, maxc + 4)
        out.append(f"{x} {y}")

    sys.stdout.write("\n".join(out) + "\n")


main()
