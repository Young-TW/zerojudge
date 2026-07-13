#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// 斜率公式：(y(j) - y(k)) / (x(j) - x(k))
// 為了避免浮點數誤差，我們使用交叉相乘來比較斜率
// 判斷 j 是否比 k 更優（假設 j > k）
// 我们需要维护一个下凸包（因为 a < 0，我们要最大化 dp，转换后是求最小截距或者类似形式，具体看推导）
// DP 方程: dp[i] = max(dp[j] + a*(S[i]-S[j])^2 + b*(S[i]-S[j]) + c)
// 展开: dp[i] = max(dp[j] + a*S[i]^2 - 2*a*S[i]*S[j] + a*S[j]^2 + b*S[i] - b*S[j] + c)
// 移项提取与 j 相关的部分:
// dp[i] = a*S[i]^2 + b*S[i] + c + max(dp[j] + a*S[j]^2 - b*S[j] - 2*a*S[i]*S[j])
// 令 Y(j) = dp[j] + a*S[j]^2 - b*S[j]
// 令 X(j) = S[j]
// 则我们要最大化: Y(j) - 2*a*S[i]*X(j)
// 这相当于直线方程 y = kx + m 中的 m = y - kx，其中 k = 2*a*S[i], x = X(j), y = Y(j)
// 因为 a < 0，所以斜率 k = 2*a*S[i] 是单调递减的（假设 S[i] 单调递增，题目中战斗力通常为正，若为负需离散化或平衡树，但此类题通常前缀和单调）。
// 即使 S[i] 不单调，由于 k 是变化的，我们需要用凸包优化。
// 这里 k 是单调递减的（若 S[i] 递增），我们需要维护一个上凸包（Upper Convex Hull）。
// 对于上凸包，当斜率 k 递减时，最优决策点也是向左移动的（或者在队首弹出）。
// 实际上，我们要找的是 max(Y(j) - K * X(j))。
// 比较两个点 j 和 k (j > k)，如果 j 比 k 优，则：
// Y(j) - K * X(j) > Y(k) - K * X(k)
// Y(j) - Y(k) > K * (X(j) - X(k))
// (Y(j) - Y(k)) / (X(j) - X(k)) < K  (注意除以负数要变号？这里 X(j)-X(k) > 0)
// 等等，K = 2*a*S[i]。因为 a < 0, S[i] 递增，所以 K 是负数且绝对值越来越大（越来越小）。
// 让我们重新整理斜率不等式。
// 我们要维护上凸包。对于队列中的三个点 k, j, i (k < j < i)，如果 slope(k, j) <= slope(j, i)，则 j 点无用，移除。
// slope(j, k) = (Y(j) - Y(k)) / (X(j) - X(k))
// 当查询斜率 K 递减时，我们在队首检查：如果 slope(q[head+1], q[head]) >= K，则 head++ (因为后面的点更优)。
// 注意：这里的 K 是 2*a*S[i]。
// 让我们确认符号。
// 目标：Maximize Y(j) - K * X(j).
// 假设 j > k. j is better than k if:
// Y(j) - K * X(j) > Y(k) - K * X(k)
// Y(j) - Y(k) > K * (X(j) - X(k))
// 因为 X(j) > X(k) (前缀和递增), 除以 (X(j) - X(k)):
// (Y(j) - Y(k)) / (X(j) - X(k)) > K
// 令 slope(j, k) = (Y(j) - Y(k)) / (X(j) - X(k)).
// 如果 slope(j, k) > K, 则 j 比 k 好。
// 由于 K 是单调递减的 (a<0, S[i] 增加 => 2aS[i] 变得更负)，之前满足 slope > K 的点，随着 K 变小，可能依然满足，或者我们需要找 slope 更小的点？
// 不对。如果 K 变小（更负），那么条件 slope > K 更容易满足。这意味着原本不够优的点（slope 较小）现在可能变得比 K 大？
// 让我们换个角度。我们要找最大的截距。直线斜率为 K。
// 在上凸包上，随着斜率 K 减小，切点会向右移动还是向左？
// 上凸包的斜率是单调递减的。
// 如果 K 减小，为了最大化截距，切点应该往斜率更小（更右边）的地方移动？
// 举例：凸包斜率从 10 降到 -10。K 从 -5 降到 -20。
// 当 K=-5，切点斜率接近 -5。当 K=-20，切点斜率接近 -20（更靠右）。
// 所以决策点是单调向右移动的？
// 让我们再检查一遍 K 的变化。
// a < 0. S[i] 随 i 增加而增加（假设 x_i >= 0）。
// K = 2 * a * S[i].
// 如果 S[i] 增加，a 是负数，那么 K 会变得更小（例如 -10 -> -20）。
// 是的，K 单调递减。
// 上凸包的斜率也是单调递减的。
// 我们需要找点 j 使得 slope(j, j-1) >= K 且 slope(j+1, j) < K ?
// 或者是：只要 slope(q[head+1], q[head]) > K，说明 q[head+1] 比 q[head] 更优（因为斜率还很大，大于当前的 K，根据上面的推导 slope > K 则新点更优）。
// 既然 K 在减小，那么原本 slope > K 的关系可能保持，或者我们需要更大的 slope 才能大于 K？不对，K 变小了，slope > K 更容易成立。
// 这意味着如果 q[head+1] 比 q[head] 优（slope > K_old），那么当 K_new < K_old 时，slope > K_new 更是成立。
// 这说明最优点会随着 K 的减小而向“斜率更小”的方向移动？
// 等等，逻辑反了。
// 如果 slope(j, k) > K，则 j 优于 k。
// 我们有一个队列，斜率单调递减。
// q[0], q[1], ...
// slope(q[1], q[0]) > slope(q[2], q[1]) > ...
// 当前 K。我们想找第一个 j 使得 slope(q[j+1], q[j]) <= K。此时 q[j] 是最优的。
// 因为如果 slope(q[1], q[0]) > K，则 1 比 0 优，弹出 0。
// 随着 K 减小，更多的 slope 会变得 > K 吗？
// 如果 K 从 -5 变成 -20。
// 假设 slope 是 -10。
// -10 > -5 (False). 此时 0 比 1 优（假设前面没了）。
// -10 > -20 (True). 此时 1 比 0 优。
// 所以当 K 减小时，我们会弹出更多的队首元素，决策点向右移动。
// 结论：使用单调队列，队首维护最优解。当 slope(q[head+1], q[head]) > K 时，head++。
// 队尾维护凸包：加入新点 i 时，若 slope(i, tail) >= slope(tail, tail-1)，则移除 tail（因为要维持上凸包，斜率必须严格递减，如果出现折线向内凹或者直线，中间点无用）。
// 注意：这里是 >= 还是 > 取决于是否保留共线点，通常 >= 移除。

ll n, a, b, c;
vector<ll> S;
vector<ll> dp;

ll get_Y(int j) {
    return dp[j] + a * S[j] * S[j] - b * S[j];
}

ll get_X(int j) {
    return S[j];
}

// 计算斜率的分子分母，避免除法
// 判断 slope(j, k) > K  => (Y(j)-Y(k))/(X(j)-X(k)) > K
// 由于 X(j) > X(k)，分母为正。
// Y(j) - Y(k) > K * (X(j) - X(k))
// 但是 K = 2*a*S[i]，可能是负数。乘法没问题。
// 为了防止溢出，__int128 或者仔细检查范围。
// n=10^6, x=10^6 -> S=10^12. S^2 = 10^24. 必须用 __int128 或者题目数据范围较小？
// 题目没说 x 的范围，但通常这类题 x 较小或者 n 较小。如果是 10^5 * 10^6 = 10^11, 平方 10^22 超过 long long.
// 然而 ZeroJudge a200 原题数据范围：n <= 10^6, |xi| <= 100? 或者 xi 比较小？
// 查阅 APIO2010 原题，n=10^6, xi <= 100? 不，有些版本 xi 较大。
// 如果 S[i] 达到 10^12，a*S[i]^2 肯定爆 long long。
// 但通常这种题的结果在 long long 范围内，意味着中间过程可能也需要 __int128 或者题目保证了数据范围使得 long long 足够。
// 考虑到 C++14 和一般 OJ 环境，__int128 在 GCC 是可用的。
// 我们用 __int128 来处理斜率比较的乘法部分。

bool is_better(int j, int k, ll i) {
    // 判断 j 是否比 k 优 (j > k)
    // slope(j, k) > K
    // (Y(j) - Y(k)) > 2 * a * S[i] * (X(j) - X(k))
    ll Yj = get_Y(j);
    ll Yk = get_Y(k);
    ll Xj = get_X(j);
    ll Xk = get_X(k);
    
    __int128 lhs = (__int128)(Yj - Yk);
    __int128 rhs = (__int128)(2) * a * S[i] * (Xj - Xk);
    
    return lhs > rhs;
}

// 检查凸包性质：slope(i, tail) >= slope(tail, tail-1) 则移除 tail
// (Y(i)-Y(t))/(X(i)-X(t)) >= (Y(t)-Y(t-1))/(X(t)-X(t-1))
// 交叉相乘，注意分母都是正的 (X 递增)
bool check_convex(int i, int t, int t_prev) {
    ll Yi = get_Y(i);
    ll Yt = get_Y(t);
    ll Ytp = get_Y(t_prev);
    
    ll Xi = get_X(i);
    ll Xt = get_X(t);
    ll Xtp = get_X(t_prev);
    
    __int128 num1 = (__int128)(Yi - Yt) * (Xt - Xtp);
    __int128 num2 = (__int128)(Yt - Ytp) * (Xi - Xt);
    
    return num1 >= num2;
}

int main() {
    // 优化 IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    cin >> a >> b >> c;
    
    S.assign(n + 1, 0);
    dp.assign(n + 1, 0);
    
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        S[i] = S[i - 1] + x;
    }
    
    // 单调队列存储下标
    vector<int> q(n + 5);
    int head = 0, tail = 0;
    
    // 初始状态，dp[0] = 0
    q[tail++] = 0;
    
    for (int i = 1; i <= n; ++i) {
        // 队首优化：移除不如下一个点优的点
        while (head + 1 < tail && is_better(q[head + 1], q[head], i)) {
            head++;
        }
        
        int j = q[head];
        ll diff = S[i] - S[j];
        dp[i] = dp[j] + a * diff * diff + b * diff + c;
        
        // 队尾维护凸包
        while (head + 1 < tail && check_convex(i, q[tail - 1], q[tail - 2])) {
            tail--;
        }
        q[tail++] = i;
    }
    
    cout << dp[n] << endl;
    
    return 0;
}
