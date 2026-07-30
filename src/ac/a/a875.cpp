#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    map<string, double> price;
    price["Cu"]  = 1.730;
    price["Zn"]  = 1.130;
    price["H2O"] = 3.720;
    price["Fe"]  = 0.410;
    price["Si"]  = 0.320;
    price["Mg"]  = 3.460;
    price["C"]   = 2.750;
    price["Pt"]  = 25000.000;
    price["Au"]  = 12260.000;
    price["Ag"]  = 190.629;

    long long F, R, C;
    while (cin >> F >> R >> C) {
        vector<long long> f, w;
        vector<string> nm;
        long long tf, tw;
        string tn;
        while (cin >> tf >> tn >> tw) {
            if (tf == 0 && tw == 0) break;
            f.push_back(tf);
            nm.push_back(tn);
            w.push_back(tw);
        }

        // Robot mines in list order (a prefix) until fuel is insufficient,
        // always keeping R fuel for the return trip.
        long long budget = F - R;
        long long used = 0;
        vector<int> weights;
        vector<double> values;
        for (size_t i = 0; i < f.size(); i++) {
            if (used + f[i] <= budget) {
                used += f[i];
                weights.push_back((int)w[i]);
                values.push_back(price[nm[i]] * (double)w[i]);
            } else {
                break;
            }
        }

        // 0/1 knapsack: choose which mined ores to load (exact weight DP).
        int cap = (int)C;
        const double NEG = -1e100;
        vector<double> dp(cap + 1, NEG);
        dp[0] = 0.0;
        for (size_t i = 0; i < weights.size(); i++) {
            int wt = weights[i];
            double v = values[i];
            for (int c = cap; c >= wt; c--) {
                if (dp[c - wt] + v > dp[c]) dp[c] = dp[c - wt] + v;
            }
        }

        double best = 0.0;
        int bestW = 0;
        for (int c = 0; c <= cap; c++) {
            if (dp[c] > best + 1e-9) {
                best = dp[c];
                bestW = c;
            }
        }
        printf("kg=%d value=%.1f\n", bestW, best + 1e-9);
    }
    return 0;
}
