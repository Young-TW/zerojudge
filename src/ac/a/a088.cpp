#include <iostream>
using namespace std;

int main() {
    int L1, L2, L3, D;
    while (cin >> L1 >> L2 >> L3 >> D) {
        const int MOD = 11380;
        int dp1[31][11] = {};
        int dp2[31][11][11] = {};
        int dp3[31][11][11][11] = {};

        dp1[0][0] = 1;
        dp2[0][0][0] = 1;
        dp3[0][0][0][0] = 1;

        for (int d = 1; d <= D; ++d) {
            // dp1[d]
            dp1[d][0] = 1;
            for (int c = 1; c <= L3; ++c) {
                long long sum = 0;
                for (int i = 1; i <= c; ++i) {
                    int g = dp1[d-1][i-1];
                    if (g) sum += (long long)dp1[d][c-i] * g;
                }
                dp1[d][c] = sum % MOD;
            }

            // dp2[d]
            int G2[11][11] = {};
            for (int b = 0; b <= L2; ++b) {
                for (int c = 0; c <= L3; ++c) {
                    long long val = 0;
                    if (b >= 1) val += dp2[d-1][b-1][c];
                    if (b == 0 && c >= 1) val += dp1[d-1][c-1];
                    G2[b][c] = val % MOD;
                }
            }
            dp2[d][0][0] = 1;
            for (int b = 0; b <= L2; ++b) {
                for (int c = 0; c <= L3; ++c) {
                    if (b == 0 && c == 0) continue;
                    long long sum = 0;
                    for (int i = 0; i <= b; ++i) {
                        for (int j = 0; j <= c; ++j) {
                            if (i == 0 && j == 0) continue;
                            int g = G2[i][j];
                            if (g) sum += (long long)dp2[d][b-i][c-j] * g;
                        }
                    }
                    dp2[d][b][c] = sum % MOD;
                }
            }

            // dp3[d]
            int G3[11][11][11] = {};
            for (int a = 0; a <= L1; ++a) {
                for (int b = 0; b <= L2; ++b) {
                    for (int c = 0; c <= L3; ++c) {
                        long long val = 0;
                        if (a >= 1) val += dp3[d-1][a-1][b][c];
                        if (a == 0 && b >= 1) val += dp2[d-1][b-1][c];
                        if (a == 0 && b == 0 && c >= 1) val += dp1[d-1][c-1];
                        G3[a][b][c] = val % MOD;
                    }
                }
            }
            dp3[d][0][0][0] = 1;
            for (int a = 0; a <= L1; ++a) {
                for (int b = 0; b <= L2; ++b) {
                    for (int c = 0; c <= L3; ++c) {
                        if (a == 0 && b == 0 && c == 0) continue;
                        long long sum = 0;
                        for (int i = 0; i <= a; ++i) {
                            for (int j = 0; j <= b; ++j) {
                                for (int k = 0; k <= c; ++k) {
                                    if (i == 0 && j == 0 && k == 0) continue;
                                    int g = G3[i][j][k];
                                    if (g) sum += (long long)dp3[d][a-i][b-j][c-k] * g;
                                }
                            }
                        }
                        dp3[d][a][b][c] = sum % MOD;
                    }
                }
            }
        }

        int ans;
        if (D == 0) {
            ans = dp3[0][L1][L2][L3];
        } else {
            ans = (dp3[D][L1][L2][L3] - dp3[D-1][L1][L2][L3]) % MOD;
            if (ans < 0) ans += MOD;
        }
        cout << ans << endl;
    }
    return 0;
}
