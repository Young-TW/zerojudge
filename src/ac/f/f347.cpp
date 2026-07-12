#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Turtle {
    int w;
    int s;
};

bool cmp(const Turtle& a, const Turtle& b) {
    if (a.s != b.s) return a.s < b.s;
    return a.w < b.w;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<Turtle> turtles;
    int w, s;
    while (cin >> w >> s) {
        turtles.push_back({w, s});
    }
    
    sort(turtles.begin(), turtles.end(), cmp);
    
    int n = turtles.size();
    vector<long long> dp(n + 1, INF);
    dp[0] = 0;
    
    for (int i = 0; i < n; ++i) {
        long long cw = turtles[i].w;
        long long cs = turtles[i].s;
        for (int j = i; j >= 0; --j) {
            if (dp[j] + cw <= cs) {
                if (dp[j + 1] > dp[j] + cw) {
                    dp[j + 1] = dp[j] + cw;
                }
            }
        }
    }
    
    int ans = 0;
    for (int i = n; i >= 0; --i) {
        if (dp[i] != INF) {
            ans = i;
            break;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
