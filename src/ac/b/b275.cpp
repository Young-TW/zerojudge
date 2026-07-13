#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int my_gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        if (!(cin >> x[i] >> y[i])) return 0;
    }
    
    long long collinear = 0;
    vector<long long> dirs;
    if (n > 0) dirs.reserve(n - 1);
    for (int i = 0; i < n; ++i) {
        dirs.clear();
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            int dx = x[j] - x[i];
            int dy = y[j] - y[i];
            int g = my_gcd(dx, dy);
            if (g != 0) {
                dx /= g;
                dy /= g;
            }
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx;
                dy = -dy;
            }
            long long key = ((long long)dx << 32) | (unsigned int)dy;
            dirs.push_back(key);
        }
        sort(dirs.begin(), dirs.end());
        int cnt = 1;
        for (size_t j = 1; j < dirs.size(); ++j) {
            if (dirs[j] == dirs[j-1]) {
                cnt++;
            } else {
                if (cnt >= 2) {
                    collinear += (long long)cnt * (cnt - 1) / 2;
                }
                cnt = 1;
            }
        }
        if (cnt >= 2) {
            collinear += (long long)cnt * (cnt - 1) / 2;
        }
    }
    collinear /= 3;
    
    long long total = (long long)n * (n - 1) * (n - 2) / 6;
    cout << total - collinear << "\n";
    
    return 0;
}
