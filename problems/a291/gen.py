import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    out = []

    T = rng.randint(1, 5)
    for _ in range(T):
        # 正確密碼：4 個 0-9 的數字，偶爾全同
        if rng.random() < 0.2:
            d = rng.randint(0, 9)
            ans = [d, d, d, d]
        else:
            ans = [rng.randint(0, 9) for _ in range(4)]
        out.append(" ".join(map(str, ans)))

        n = rng.randint(1, 20)
        out.append(str(n))

        for _ in range(n):
            r = rng.random()
            if r < 0.15:
                # 跟答案一模一樣 (4A0B)
                g = ans[:]
            elif r < 0.30:
                # 全同數字，測重複數字的 A/B 計算
                d = rng.randint(0, 9)
                g = [d, d, d, d]
            else:
                g = [rng.randint(0, 9) for _ in range(4)]
            out.append(" ".join(map(str, g)))

    sys.stdout.write("\n".join(out) + "\n")


main()
