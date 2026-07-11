#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline long long my_abs(long long x) {
    return x < 0 ? -x : x;
}

long long gcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int N;
        cin >> N;
        vector<long long> x(N), y(N);
        for (int i = 0; i < N; i++) {
            cin >> x[i] >> y[i];
        }
        
        int ans = 0;
        if (N > 0) ans = 1;
        
        for (int i = 0; i < N; i++) {
            int same = 1;
            vector<pair<long long, long long>> slopes;
            slopes.reserve(N);
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                if (x[i] == x[j] && y[i] == y[j]) {
                    same++;
                    continue;
                }
                long long dx = x[j] - x[i];
                long long dy = y[j] - y[i];
                long long g = gcd(my_abs(dx), my_abs(dy));
                dx /= g;
                dy /= g;
                if (dx < 0) {
                    dx = -dx;
                    dy = -dy;
                } else if (dx == 0) {
                    if (dy < 0) {
                        dy = -dy;
                    }
                }
                slopes.push_back({dx, dy});
            }
            
            sort(slopes.begin(), slopes.end());
            int max_cnt = 0;
            if (!slopes.empty()) {
                int cnt = 1;
                for (size_t k = 1; k < slopes.size(); k++) {
                    if (slopes[k] == slopes[k - 1]) {
                        cnt++;
                    } else {
                        if (cnt > max_cnt) max_cnt = cnt;
                        cnt = 1;
                    }
                }
                if (cnt > max_cnt) max_cnt = cnt;
            }
            
            if (max_cnt + same > ans) {
                ans = max_cnt + same;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
