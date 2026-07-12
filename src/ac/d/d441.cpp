#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int get_count(int n, int p) {
    int count = 0;
    long long power = p;
    while (power <= n) {
        count += n / power;
        power *= p;
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (!(cin >> t)) return 0;
    for (int i = 1; i <= t; ++i) {
        int m, n;
        if (!(cin >> m >> n)) break;
        vector<pair<int, int>> factors;
        int temp = m;
        for (int j = 2; j * j <= temp; ++j) {
            if (temp % j == 0) {
                int cnt = 0;
                while (temp % j == 0) {
                    temp /= j;
                    cnt++;
                }
                factors.push_back(make_pair(j, cnt));
            }
        }
        if (temp > 1) {
            factors.push_back(make_pair(temp, 1));
        }
        
        int ans = INT_MAX;
        for (size_t j = 0; j < factors.size(); ++j) {
            int p = factors[j].first;
            int e = factors[j].second;
            int cnt = get_count(n, p);
            if (cnt / e < ans) {
                ans = cnt / e;
            }
        }
        
        cout << "Case " << i << ":\n";
        if (ans == 0) {
            cout << "Impossible to divide\n";
        } else {
            cout << ans << "\n";
        }
    }
    return 0;
}
