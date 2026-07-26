#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const string fail = "wryyyyyyyyyyyyy";

    int W, E, N;
    while (cin >> W >> E >> N) {
        vector<pair<int,int>> skills;
        skills.reserve(N);
        for (int i = 0; i < N; ++i) {
            int D, A;
            cin >> D >> A;
            if (D < W)               // using it would not kill us immediately
                skills.emplace_back(D, A);
        }

        // dp[j] = max damage with exact cost j, -1 = unreachable
        vector<int> dp(W, -1);
        dp[0] = 0;

        for (auto &sk : skills) {
            int d = sk.first;
            int a = sk.second;
            for (int j = W - 1; j >= d; --j) {
                if (dp[j - d] != -1) {
                    int cand = dp[j - d] + a;
                    if (cand > dp[j]) dp[j] = cand;
                }
            }
        }

        int answer = -1;
        for (int j = 1; j < W; ++j) {
            if (dp[j] >= E) {
                answer = W - j;          // remaining hit points
                break;                   // smallest j gives maximal remaining HP
            }
        }

        if (answer == -1) cout << fail << '\n';
        else               cout << answer << '\n';
    }
    return 0;
}
