#include <iostream>
#include <cstring>

using namespace std;

int H, K;
int best_ans;
int best_stamps[10];
int cur[10];

const int MAXV = 9999;
int dp[MAXV + 1];

// 用目前前 cnt 個面額（cur[0..cnt-1]），計算 n(H, cnt)：
// 從 1 開始最多用 H 張郵票能連續表示到的最大值。
int computeN(int cnt) {
    int maxDenom = cur[cnt - 1];
    int maxVal = H * maxDenom;
    if (maxVal > MAXV) maxVal = MAXV;

    dp[0] = 0;
    for (int v = 1; v <= maxVal; ++v) dp[v] = -1;
    // 完全背包：dp[v] = 湊出 v 所需最少郵票數
    for (int v = 1; v <= maxVal; ++v) {
        for (int i = 0; i < cnt; ++i) {
            if (cur[i] <= v && dp[v - cur[i]] >= 0) {
                int c = dp[v - cur[i]] + 1;
                if (dp[v] < 0 || c < dp[v]) dp[v] = c;
            }
        }
    }

    int n = 0;
    for (int v = 1; v <= maxVal; ++v) {
        if (dp[v] >= 0 && dp[v] <= H) n = v;
        else break;
    }
    return n;
}

void dfs(int idx) {
    if (idx == K) {
        int n = computeN(K);
        if (n > best_ans) {
            best_ans = n;
            memcpy(best_stamps, cur, sizeof(int) * K);
        }
        return;
    }
    // 目前前 idx 個面額能連續表示到 m，下一個面額最多取到 m+1
    // （超過 m+1 會在 m+1 留下無法表示的缺口）。
    int m = computeN(idx);
    int upper = m + 1;
    for (int d = cur[idx - 1] + 1; d <= upper; ++d) {
        cur[idx] = d;
        dfs(idx + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> H >> K && (H || K)) {
        best_ans = 0;
        memset(best_stamps, 0, sizeof(best_stamps));
        cur[0] = 1;              // 第一個面額必為 1
        dfs(1);

        for (int i = 0; i < K; ++i) {
            cout << best_stamps[i] << " ";
        }
        cout << "-> " << best_ans << "\n";
    }

    return 0;
}
