#include <bits/stdc++.h>
using namespace std;

const long long INF = (long long)4e18;   // larger than any possible answer

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while ( (cin >> n) ) {
        vector<int> L(n + 1), R(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> L[i] >> R[i];
        }

        // ---------- first pass : depths ----------
        vector<int> depthRod(n + 1, -1);
        depthRod[1] = 0;
        int minDepth = INT_MAX, maxDepth = -1;

        for (int i = 1; i <= n; ++i) {
            int d = depthRod[i];
            // left child
            if (L[i] != -1) {
                depthRod[L[i]] = d + 1;
            } else {
                int leafDepth = d + 1;
                minDepth = min(minDepth, leafDepth);
                maxDepth = max(maxDepth, leafDepth);
            }
            // right child
            if (R[i] != -1) {
                depthRod[R[i]] = d + 1;
            } else {
                int leafDepth = d + 1;
                minDepth = min(minDepth, leafDepth);
                maxDepth = max(maxDepth, leafDepth);
            }
        }

        if (maxDepth - minDepth > 1) {
            cout << -1 << "\n";
            continue;
        }
        if (maxDepth == minDepth) {
            cout << 0 << "\n";
            continue;
        }

        int deeper = maxDepth;   // depth that corresponds to label 1

        // ---------- DP bottom‑up ----------
        vector<long long> ones(n + 1, 0), zeros(n + 1, 0), cost(n + 1, INF);

        for (int i = n; i >= 1; --i) {
            // left side
            long long onesL, zerosL, costL;
            if (L[i] == -1) {
                int leafDepth = depthRod[i] + 1;
                long long one = (leafDepth == deeper) ? 1LL : 0LL;
                onesL = one;
                zerosL = 1 - one;
                costL = 0;
            } else {
                onesL = ones[L[i]];
                zerosL = zeros[L[i]];
                costL = cost[L[i]];
            }

            // right side
            long long onesR, zerosR, costR;
            if (R[i] == -1) {
                int leafDepth = depthRod[i] + 1;
                long long one = (leafDepth == deeper) ? 1LL : 0LL;
                onesR = one;
                zerosR = 1 - one;
                costR = 0;
            } else {
                onesR = ones[R[i]];
                zerosR = zeros[R[i]];
                costR = cost[R[i]];
            }

            // if any child impossible, this node impossible
            if (costL == INF || costR == INF) {
                cost[i] = INF;
                ones[i] = onesL + onesR;
                zeros[i] = zerosL + zerosR;
                continue;
            }

            long long best = INF;
            // keep order
            if (zerosL == 0 || onesR == 0) {
                best = min(best, costL + costR);
            }
            // swap order
            if (zerosR == 0 || onesL == 0) {
                best = min(best, costL + costR + 1);
            }

            cost[i] = best;
            ones[i] = onesL + onesR;
            zeros[i] = zerosL + zerosR;
        }

        if (cost[1] >= INF/2) cout << -1 << "\n";
        else                 cout << cost[1] << "\n";
    }
    return 0;
}
