#pragma GCC optimize("O3")
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    if (!(cin >> N >> M >> K)) return 0;

    int U[505], V[505];
    double W[505];
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        U[i] = u;
        V[i] = v;
        W[i] = w;
    }

    double inv[1005];
    for (int i = 1; i <= K; ++i) {
        inv[i] = 1.0 / i;
    }

    static double dp[505][1005];
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= K; ++j) {
            dp[i][j] = 1e18;
        }
    }
    dp[1][0] = 0.0;

    for (int k = 0; k < K; ++k) {
        int limit = K - k;
        for (int i = 0; i < M; ++i) {
            int u = U[i];
            int v = V[i];
            double w = W[i];
            
            double du = dp[u][k];
            double dv = dp[v][k];
            
            if (du < 1e17) {
                double* dpv = dp[v];
                for (int x = 1; x <= limit; ++x) {
                    double val = du + w * inv[x];
                    if (val < dpv[k + x]) {
                        dpv[k + x] = val;
                    }
                }
            }
            if (dv < 1e17) {
                double* dpu = dp[u];
                for (int x = 1; x <= limit; ++x) {
                    double val = dv + w * inv[x];
                    if (val < dpu[k + x]) {
                        dpu[k + x] = val;
                    }
                }
            }
        }
    }

    double ans = dp[N][K];
    if (fabs(ans - round(ans)) < 1e-6) {
        cout << (long long)round(ans) << "\n";
    } else {
        cout << fixed << setprecision(6) << ans << "\n";
    }

    return 0;
}
