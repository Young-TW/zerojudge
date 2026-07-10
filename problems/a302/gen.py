import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # 小規模：k 在 [0, 25]，a,b 在 [1, 15]，暴力模擬瞬間跑完。
    # 用數種模式刻意涵蓋邊界。
    mode = rng.randint(0, 6)

    if mode == 0:
        # 邊界：k = 0 -> n = m = 0，係數必為 1
        k = 0
        n = 0
        m = 0
        a = rng.randint(1, 15)
        b = rng.randint(1, 15)
    elif mode == 1:
        # 邊界：k = 1
        k = 1
        n = rng.randint(0, 1)
        m = k - n
        a = rng.randint(1, 15)
        b = rng.randint(1, 15)
    elif mode == 2:
        # 邊界：n = 0（純 b^k）或 m = 0（純 a^k）
        k = rng.randint(1, 25)
        if rng.random() < 0.5:
            n = 0
        else:
            n = k
        m = k - n
        a = rng.randint(1, 15)
        b = rng.randint(1, 15)
    elif mode == 3:
        # 邊界：a 或 b 是 10007 的倍數 -> mod 後為 0
        k = rng.randint(1, 25)
        n = rng.randint(0, k)
        m = k - n
        if rng.random() < 0.5:
            a = 10007
            b = rng.randint(1, 15)
        else:
            a = rng.randint(1, 15)
            b = 10007
    elif mode == 4:
        # 邊界：a = b = 1，係數退化為 C(k, n)
        k = rng.randint(1, 25)
        n = rng.randint(0, k)
        m = k - n
        a = 1
        b = 1
    elif mode == 5:
        # a, b 偏大但仍小規模（測 mod 行為）
        k = rng.randint(1, 20)
        n = rng.randint(0, k)
        m = k - n
        a = rng.randint(9000, 10010)
        b = rng.randint(9000, 10010)
    else:
        # 一般隨機
        k = rng.randint(0, 25)
        n = rng.randint(0, k)
        m = k - n
        a = rng.randint(1, 15)
        b = rng.randint(1, 15)

    sys.stdout.write(f"{a} {b} {k} {n} {m}\n")


main()
