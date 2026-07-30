#include <bits/stdc++.h>
using namespace std;

struct Node {
    long long val;   // dp[p] - p
    int cnt;         // cnt[p]
    int idx;         // p
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXA = 100000;

    int n, k;
    while (cin >> n >> k) {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];

        /* ---------- 1. compute L[i] ---------- */
        static int last[MAXA + 1];
        fill(last, last + MAXA + 1, 0);
        vector<int> L(n + 1);
        int left = 1;
        for (int i = 1; i <= n; ++i) {
            if (last[a[i]] >= left) left = last[a[i]] + 1;
            last[a[i]] = i;
            L[i] = left;
        }

        /* ---------- DP evaluation for a given lambda ---------- */
        vector<long long> dp(n + 1);
        vector<int> cntArr(n + 1);

        auto evaluate = [&](int lambda, long long &best, int &cnt) {
            dp[0] = 0;
            cntArr[0] = 0;
            deque<Node> dq;
            dq.push_back({0LL, 0, 0});               // p = 0

            for (int i = 1; i <= n; ++i) {
                // insert candidate p = i-1
                Node nd{dp[i - 1] - (i - 1), cntArr[i - 1], i - 1};
                while (!dq.empty()) {
                    const Node &bk = dq.back();
                    if (bk.val < nd.val ||
                        (bk.val == nd.val && bk.cnt <= nd.cnt))
                        dq.pop_back();
                    else break;
                }
                dq.push_back(nd);

                // discard candidates that are too far left
                int limit = L[i] - 1;
                while (!dq.empty() && dq.front().idx < limit) dq.pop_front();

                // best take
                long long takeVal = dq.front().val + i - lambda;
                int takeCnt = dq.front().cnt + 1;

                // skip i
                long long skipVal = dp[i - 1];
                int skipCnt = cntArr[i - 1];

                if (takeVal > skipVal) {
                    dp[i] = takeVal;
                    cntArr[i] = takeCnt;
                } else if (takeVal < skipVal) {
                    dp[i] = skipVal;
                    cntArr[i] = skipCnt;
                } else { // equal value, keep larger cnt
                    dp[i] = takeVal;
                    cntArr[i] = (takeCnt > skipCnt ? takeCnt : skipCnt);
                }
            }
            best = dp[n];
            cnt = cntArr[n];
        };

        /* ---------- 2. binary search for smallest lambda with cnt <= k ---------- */
        int lo = 0, hi = n + 1;          // cnt(hi) = 0
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            long long dummy; int c;
            evaluate(mid, dummy, c);
            if (c > k) lo = mid + 1;    // need larger penalty
            else       hi = mid;
        }
        int lambda0 = lo;

        long long best0, ans;
        int cnt0;
        evaluate(lambda0, best0, cnt0);
        ans = best0 + 1LL * lambda0 * k;          // candidate

        if (lambda0 > 0) {
            long long best1; int cnt1;
            evaluate(lambda0 - 1, best1, cnt1);
            long long cand = best1 + 1LL * (lambda0 - 1) * k;
            if (cand < ans) ans = cand;
        }

        cout << ans << '\n';
    }
    return 0;
}
