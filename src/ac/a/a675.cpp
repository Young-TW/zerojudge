#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

static const int VAL[6] = {1, 2, 4, 10, 20, 40};
static const int INF = 1000000;

int main() {
    int cnt[6];
    while (cin >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3] >> cnt[4] >> cnt[5]) {
        bool allz = true;
        for (int i = 0; i < 6; i++) if (cnt[i] != 0) allz = false;
        if (allz) break;

        double d;
        cin >> d;
        int target = (int)llround(d * 20.0);

        int maxpay = 0;
        for (int i = 0; i < 6; i++) maxpay += cnt[i] * VAL[i];

        int cap = min(maxpay, target + 40);
        if (cap < target) cap = target;

        vector<int> dp(cap + 1, INF);
        dp[0] = 0;
        for (int i = 0; i < 6; i++) {
            int v = VAL[i];
            int use = min(cnt[i], cap / v);
            int k = 1;
            while (use > 0) {
                int take = min(k, use);
                int wval = take * v;
                int wcost = take;
                for (int j = cap; j >= wval; j--) {
                    if (dp[j - wval] + wcost < dp[j]) dp[j] = dp[j - wval] + wcost;
                }
                use -= take;
                k <<= 1;
            }
        }

        int maxch = cap - target;
        if (maxch < 0) maxch = 0;
        vector<int> ch(maxch + 1, INF);
        ch[0] = 0;
        for (int i = 0; i < 6; i++) {
            int v = VAL[i];
            for (int j = v; j <= maxch; j++) {
                if (ch[j - v] + 1 < ch[j]) ch[j] = ch[j - v] + 1;
            }
        }

        int best = INF;
        for (int P = target; P <= cap; P++) {
            if (dp[P] >= INF) continue;
            int c = ch[P - target];
            if (c >= INF) continue;
            if (dp[P] + c < best) best = dp[P] + c;
        }

        cout << setw(3) << best << "\n";
    }
    return 0;
}
