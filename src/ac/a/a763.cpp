#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<long long> S(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        string s;
        cin >> s;
        long long val = 0;
        bool dot = false;
        for (char c : s) {
            if (c == '.') {
                dot = true;
            } else {
                val = val * 10 + (c - '0');
            }
        }
        if (!dot) val *= 10;
        S[i] = S[i - 1] + val;
    }

    vector<long long> dp_prev(N + 1, 0);
    vector<long long> dp_curr(N + 1, 0);

    const long long INF = 1e18;

    for (int i = 0; i <= N; ++i) {
        dp_prev[i] = INF;
    }
    dp_prev[0] = 0;

    vector<int> dq(N + 1);

    for (int j = 1; j <= M; ++j) {
        int head = 0, tail = 0;
        fill(dp_curr.begin(), dp_curr.end(), INF);

        for (int i = j; i <= N; ++i) {
            int k = i - 1;
            bool should_add = (dp_prev[k] != INF);
            if (should_add) {
                while (head < tail) {
                    int t = dq[tail - 1];
                    if (S[k] == S[t]) {
                        if (dp_prev[k] >= dp_prev[t]) {
                            should_add = false;
                            break;
                        } else {
                            tail--;
                        }
                    } else {
                        break;
                    }
                }
            }
            if (should_add) {
                while (tail - head >= 2) {
                    int k1 = dq[tail - 2];
                    int k2 = dq[tail - 1];
                    if ((dp_prev[k2] - dp_prev[k1]) * (S[k] - S[k2]) >= (dp_prev[k] - dp_prev[k2]) * (S[k2] - S[k1])) {
                        tail--;
                    } else {
                        break;
                    }
                }
                dq[tail++] = k;
            }

            if (head == tail) continue;

            while (tail - head >= 2) {
                int k1 = dq[head];
                int k2 = dq[head + 1];
                if ((long long)i * (S[k2] - S[k1]) >= dp_prev[k2] - dp_prev[k1]) {
                    head++;
                } else {
                    break;
                }
            }

            int best_k = dq[head];
            dp_curr[i] = dp_prev[best_k] + (long long)i * (S[i] - S[best_k]);
        }
        dp_prev.swap(dp_curr);
    }

    double ans = (double)dp_prev[N] / 10.0;
    cout << fixed << setprecision(1) << ans << "\n";

    return 0;
}
