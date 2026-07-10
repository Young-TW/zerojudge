import sys
import random


def main():
    rng = random.Random(int(sys.argv[1]))

    # 小規模：N 在 [1, 8]（2~16 名選手），R 在 [1, 8]，Q 在 [1, 2N]。
    # 暴力模擬每輪排序 O(N log N) 瞬間跑完，刻意涵蓋邊界。
    mode = rng.randint(0, 5)

    if mode == 0:
        # 邊界：N = 1（最少選手數 2 名）
        N = 1
        R = rng.randint(1, 6)
    elif mode == 1:
        # 邊界：R = 1（最少輪數）
        N = rng.randint(1, 6)
        R = 1
    elif mode == 2:
        # 邊界：Q = 1（冠軍）或 Q = 2N（墊底）
        N = rng.randint(1, 6)
        R = rng.randint(1, 6)
        # Q 在下面隨機選，這裡只決定 N, R
    elif mode == 3:
        # 邊界：初始分數全相同 -> 排名完全由編號決定（首輪前）
        N = rng.randint(2, 6)
        R = rng.randint(1, 6)
    elif mode == 4:
        # 邊界：初始分數全為 0
        N = rng.randint(1, 6)
        R = rng.randint(1, 6)
    else:
        # 一般隨機
        N = rng.randint(1, 8)
        R = rng.randint(1, 8)

    n2 = 2 * N

    # 初始分數：mode 3 全相同、mode 4 全為 0、否則隨機小範圍
    if mode == 3:
        base = rng.randint(0, 20)
        scores = [base] * n2
    elif mode == 4:
        scores = [0] * n2
    else:
        scores = [rng.randint(0, 15) for _ in range(n2)]

    # 實力值：兩兩不同（題目保證），正整數
    strengths = rng.sample(range(1, 5 * n2 + 1), n2)

    # Q：mode 2 偏向邊界值
    if mode == 2:
        Q = rng.choice([1, 2, n2 - 1, n2])
    else:
        Q = rng.randint(1, n2)

    out = []
    out.append(f"{N} {R} {Q}")
    out.append(" ".join(map(str, scores)))
    out.append(" ".join(map(str, strengths)))
    sys.stdout.write("\n".join(out) + "\n")


main()
