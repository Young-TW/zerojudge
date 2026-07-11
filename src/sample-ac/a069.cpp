#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
using namespace std;

int a[8][8];
int sum[9][9];
long long dp[9][9][9][9][15];
bool done[9][9][9][9][15];

int rectSum(int r1, int r2, int c1, int c2) {
    return sum[r2][c2] - sum[r1][c2] - sum[r2][c1] + sum[r1][c1];
}

long long solve(int r1, int r2, int c1, int c2, int k) {
    if (done[r1][r2][c1][c2][k]) return dp[r1][r2][c1][c2][k];
    done[r1][r2][c1][c2][k] = true;
    long long &res = dp[r1][r2][c1][c2][k];
    int s = rectSum(r1, r2, c1, c2);
    if (k == 1) {
        res = (long long)s * s;
        return res;
    }
    const long long INF = (long long)4e18;
    res = INF;
    for (int r = r1 + 1; r < r2; r++) {
        for (int k1 = 1; k1 < k; k1++) {
            long long v = solve(r1, r, c1, c2, k1) + solve(r, r2, c1, c2, k - k1);
            if (v < res) res = v;
        }
    }
    for (int c = c1 + 1; c < c2; c++) {
        for (int k1 = 1; k1 < k; k1++) {
            long long v = solve(r1, r2, c1, c, k1) + solve(r1, r2, c, c2, k - k1);
            if (v < res) res = v;
        }
    }
    return res;
}

int main() {
    int n;
    while (cin >> n) {
        memset(done, 0, sizeof(done));
        long long total = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cin >> a[i][j];
                total += a[i][j];
            }
        }
        for (int i = 0; i <= 8; i++) {
            for (int j = 0; j <= 8; j++) {
                if (i == 0 || j == 0) sum[i][j] = 0;
                else sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i-1][j-1];
            }
        }
        long long sq = solve(0, 8, 0, 8, n);
        double mean = (double)total / n;
        double sigma2 = (double)sq / n - mean * mean;
        if (sigma2 < 0) sigma2 = 0;
        double sigma = sqrt(sigma2);
        cout << fixed << setprecision(3) << sigma << endl;
    }
    return 0;
}
