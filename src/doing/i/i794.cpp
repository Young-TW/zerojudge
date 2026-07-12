#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int dp[10005];
vector<pair<int, int>> items;
vector<pair<int, int>> useful_items;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int W, E, N;
    while (cin >> W >> E >> N) {
        memset(dp, 0, sizeof(dp));
        items.clear();
        useful_items.clear();
        
        for (int i = 0; i < N; ++i) {
            int D, A;
            cin >> D >> A;
            if (D < W) {
                items.push_back({D, A});
            }
        }
        
        sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second;
        });
        
        int max_A = -1;
        for (const auto& p : items) {
            if (p.second > max_A) {
                useful_items.push_back(p);
                max_A = p.second;
            }
        }
        
        for (const auto& p : useful_items) {
            int D = p.first;
            int A = p.second;
            for (int j = W - 1; j >= D; --j) {
                if (dp[j - D] + A > dp[j]) {
                    dp[j] = dp[j - D] + A;
                }
            }
        }
        
        int min_cost = W + 1;
        for (int j = 1; j < W; ++j) {
            if (dp[j] >= E) {
                min_cost = j;
                break;
            }
        }
        
        if (min_cost <= W - 1) {
            cout << W - min_cost << "\n";
        } else {
            cout << "wryyyyyyyyyyyyy\n";
        }
    }
    return 0;
}
