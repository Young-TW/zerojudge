#include <iostream>
#include <vector>
#include <algorithm>

const long long NEG_INF = -4e18;

struct Node {
    std::vector<long long> dp;
    std::vector<long long> top;
};

Node combine(const Node& L, const Node& R) {
    int nL = (int)L.dp.size() - 1;
    int nR = (int)R.dp.size() - 1;
    int n = nL + nR;
    Node res;
    res.dp.resize(n + 1);
    res.top.resize(n + 1);
    res.dp[0] = 0;
    res.top[0] = 0;
    for (int i = 1; i <= n; ++i) {
        res.dp[i] = NEG_INF;
        res.top[i] = NEG_INF;
    }

    // Combine top: max-plus convolution of L.top and R.top
    int i = 0;
    for (int k = 1; k <= n; ++k) {
        int low = std::max(0, k - nR);
        int high = std::min(k, nL);
        if (i < low) i = low;
        while (i < high) {
            long long cur = L.top[i] + R.top[k - i];
            long long nxt = L.top[i + 1] + R.top[k - (i + 1)];
            if (nxt >= cur) ++i;
            else break;
        }
        res.top[k] = L.top[i] + R.top[k - i];
    }

    // Combine dp: max(L.dp[x], max_{k=0..x-1} L.top[k] + R.dp[x-k])
    int k_ptr = 0;
    for (int x = 1; x <= n; ++x) {
        long long val1 = (x <= nL) ? L.dp[x] : NEG_INF;
        int low = std::max(0, x - nR);
        int high = std::min(x - 1, nL);
        long long val2 = NEG_INF;
        if (low <= high) {
            if (k_ptr < low) k_ptr = low;
            while (k_ptr < high) {
                long long cur = L.top[k_ptr] + R.dp[x - k_ptr];
                long long nxt = L.top[k_ptr + 1] + R.dp[x - (k_ptr + 1)];
                if (nxt >= cur) ++k_ptr;
                else break;
            }
            val2 = L.top[k_ptr] + R.dp[x - k_ptr];
        }
        res.dp[x] = std::max(val1, val2);
    }
    return res;
}

Node solve(int l, int r, const std::vector<long long>& S, const std::vector<long long>& A) {
    if (l == r) {
        Node res;
        res.dp = {0, 2 * S[l] + A[l]};
        res.top = {0, A[l]};
        return res;
    }
    int mid = (l + r) / 2;
    Node left = solve(l, mid, S, A);
    Node right = solve(mid + 1, r, S, A);
    return combine(left, right);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N;
    bool first = true;
    while (std::cin >> N) {
        std::vector<long long> S(N), A(N);
        for (int i = 0; i < N; ++i) std::cin >> S[i];
        for (int i = 0; i < N; ++i) std::cin >> A[i];
        
        Node ans = solve(0, N - 1, S, A);
        
        if (!first) std::cout << '\n';
        first = false;
        for (int i = 1; i <= N; ++i) {
            std::cout << ans.dp[i] << '\n';
        }
    }
    return 0;
}
