import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))
    out = []

    # 隨機產生 1~5 筆測資，刻意取小規模讓暴力解秒殺，但涵蓋邊界
    T = rng.randint(1, 5)
    for _ in range(T):
        # N 偏小，涵蓋 N=1 的邊界
        N = rng.randint(1, 25)
        maxM = min(N * N, 50)
        # M 可為 0，涵蓋無路可走的邊界
        M = rng.randint(0, maxM)
        out.append(f"{N} {M}")

        for _ in range(M):
            a = rng.randint(1, N)
            b = rng.randint(1, N)
            out.append(f"{a} {b}")  # 允許自環與重邊

        A = rng.randint(1, N)
        B = rng.randint(1, N)
        # 偶爾強制 A==B，測試自身可達性
        if rng.random() < 0.2:
            A = B
        out.append(f"{A} {B}")

    sys.stdout.write("\n".join(out) + "\n")


main()
