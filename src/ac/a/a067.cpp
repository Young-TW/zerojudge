#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>
using namespace std;

int N, M;
int best;
int minV[25], minA[25];

void dfs(int dep, int v, int maxR, int maxH, int s) {
    if (dep > M) {
        if (v == 0) best = min(best, s);
        return;
    }
    int k = M - dep + 1;
    if (v < minV[k]) return;
    if (s + minA[k] >= best) return;
    if (maxR < k) return;
    if (s + 2 * v / maxR >= best) return;

    int rmax = min(maxR, (int)sqrt((double)v));
    int minVR = (k > 1) ? minV[k - 1] : 0;
    for (int R = rmax; R >= k; R--) {
        int R2 = R * R;
        int hmax = min(maxH, v / R2);
        hmax = min(hmax, (v - minVR) / R2);
        for (int H = hmax; H >= k; H--) {
            int vol = R2 * H;
            int ns;
            if (dep == 1) ns = s + R2 + 2 * R * H;
            else ns = s + 2 * R * H;
            if (ns >= best) continue;
            dfs(dep + 1, v - vol, R - 1, H - 1, ns);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    minV[0] = 0; minA[0] = 0;
    for (int i = 1; i <= 20; i++) {
        minV[i] = minV[i-1] + i * i * i;
        minA[i] = minA[i-1] + 2 * i * i;
    }
    while (cin >> N >> M) {
        best = INT_MAX;
        int maxR = (int)sqrt((double)N) + 1;
        int maxH = N;
        dfs(1, N, maxR, maxH, 0);
        cout << (best == INT_MAX ? 0 : best) << "\n";
    }
    return 0;
}
