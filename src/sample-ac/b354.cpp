#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int INF = 1e9;

int solve_knapsack(int target, int max_cost, const vector<pair<int, int>>& items) {
    if (target <= 0) return 0;
    if (max_cost <= 0) return INF;
    
    int m = items.size();
    int limit = min(target, max_cost);
    
    if (limit <= 2000000) {
        if (target <= max_cost) {
            vector<int> dp(target + 1, INF);
            dp[0] = 0;
            for (int i = 0; i < m; ++i) {
                int c = items[i].first, h = items[i].second;
                for (int j = target; j >= 0; --j) {
                    if (dp[j] == INF) continue;
                    int next = min(target, j + h);
                    if (dp[j] + c <= max_cost) {
                        if (dp[j] + c < dp[next]) {
                            dp[next] = dp[j] + c;
                        }
                    }
                }
            }
            return dp[target];
        } else {
            vector<int> dp(max_cost + 1, -1);
            dp[0] = 0;
            for (int i = 0; i < m; ++i) {
                int c = items[i].first, h = items[i].second;
                for (int j = max_cost; j >= c; --j) {
                    if (dp[j - c] != -1) {
                        if (dp[j - c] + h > dp[j]) {
                            dp[j] = dp[j - c] + h;
                        }
                    }
                }
            }
            for (int i = 0; i <= max_cost; ++i) {
                if (dp[i] >= target) return i;
            }
            return INF;
        }
    } else {
        int ans = INF;
        map<int, int> dp; // cost -> max_val
        dp[0] = 0;
        for (int i = 0; i < m; ++i) {
            int c = items[i].first, h = items[i].second;
            vector<pair<int, int>> updates;
            for (auto& st : dp) {
                int cost = st.first;
                int val = st.second;
                int new_cost = cost + c;
                if (new_cost > max_cost) continue;
                if (val + h >= target) {
                    if (new_cost < ans) {
                        ans = new_cost;
                    }
                } else {
                    updates.push_back({new_cost, val + h});
                }
            }
            for (auto& up : updates) {
                auto it = dp.find(up.first);
                if (it == dp.end() || it->second < up.second) {
                    dp[up.first] = up.second;
                }
            }
            vector<pair<int, int>> valid;
            int max_val = -1;
            for (auto& st : dp) {
                if (st.second > max_val) {
                    valid.push_back(st);
                    max_val = st.second;
                }
            }
            dp.clear();
            for (auto& v : valid) dp[v.first] = v.second;
        }
        return ans;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m1, m2;
    while (cin >> n >> m1 >> m2) {
        vector<pair<int, int>> red_potions;
        int red_bonus = 0;
        for (int i = 0; i < m1; ++i) {
            int c, h;
            cin >> c >> h;
            if (c > 0 && h > 0) {
                red_potions.push_back({c, h});
            } else if (c == 0 && h > 0) {
                red_bonus += h;
            }
        }
        
        vector<pair<int, int>> blue_potions;
        int blue_bonus = 0;
        for (int i = 0; i < m2; ++i) {
            int c, m_val;
            cin >> c >> m_val;
            if (c > 0 && m_val > 0) {
                blue_potions.push_back({c, m_val});
            } else if (c == 0 && m_val > 0) {
                blue_bonus += m_val;
            }
        }
        
        int a, b;
        cin >> a >> b;
        a = max(0, a - red_bonus);
        b = max(0, b - blue_bonus);
        
        int cost_red = solve_knapsack(a, n, red_potions);
        int cost_blue = solve_knapsack(b, n, blue_potions);
        
        if (cost_red == INF || cost_blue == INF || cost_red > n - cost_blue) {
            cout << "GG" << endl;
        } else {
            cout << cost_red + cost_blue << endl;
        }
    }
    
    return 0;
}
