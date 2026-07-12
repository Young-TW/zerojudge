#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXP = 50000;
int sigma[MAXP + 1];
int cnt[MAXP + 1];
int dp[10005];

void init_sigma() {
    for (int i = 1; i <= MAXP; ++i) {
        for (int j = i; j <= MAXP; j += i) {
            sigma[j] += i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init_sigma();
    int N, M;
    while (cin >> N >> M) {
        memset(cnt, 0, sizeof(cnt));
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < N; ++i) {
            int p;
            cin >> p;
            cnt[p]++;
        }
        for (int p = 1; p <= MAXP; ++p) {
            if (cnt[p] == 0) continue;
            int w = sigma[p];
            int v = p;
            if (w > M) continue;
            int k = 1;
            while (cnt[p] > 0) {
                int take = min(k, cnt[p]);
                cnt[p] -= take;
                if (w <= M / take) {
                    int ww = w * take;
                    int vv = v * take;
                    for (int j = M; j >= ww; --j) {
                        if (dp[j - ww] + vv > dp[j]) {
                            dp[j] = dp[j - ww] + vv;
                        }
                    }
                }
                k *= 2;
            }
        }
        cout << dp[M] << "\n";
    }
    return 0;
}
