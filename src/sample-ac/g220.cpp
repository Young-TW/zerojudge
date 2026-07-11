#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

long long my_gcd(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
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
    
    int n;
    while (cin >> n) {
        vector<long long> x(n), y(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }
        
        long long ans = 0;
        vector<pair<long long, long long>> slopes;
        slopes.reserve(n);
        
        for (int i = 0; i < n; i++) {
            slopes.clear();
            for (int j = i + 1; j < n; j++) {
                long long dx = x[j] - x[i];
                long long dy = y[j] - y[i];
                if (dx == 0 && dy == 0) {
                    slopes.push_back({0, 0});
                } else {
                    long long g = my_gcd(dx, dy);
                    dx /= g;
                    dy /= g;
                    if (dx < 0 || (dx == 0 && dy < 0)) {
                        dx = -dx;
                        dy = -dy;
                    }
                    slopes.push_back({dx, dy});
                }
            }
            
            sort(slopes.begin(), slopes.end());
            
            int count = 1;
            for (size_t k = 1; k < slopes.size(); k++) {
                if (slopes[k] == slopes[k - 1]) {
                    count++;
                } else {
                    if (count >= 3) {
                        ans += (long long)count * (count - 1) * (count - 2) / 6;
                    }
                    count = 1;
                }
            }
            if (count >= 3) {
                ans += (long long)count * (count - 1) * (count - 2) / 6;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
