#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        string s;
        cin >> s;
        vector<int> pos;
        pos.reserve(n);
        for (int i = 0; i < (int)s.length(); ++i) {
            if (s[i] == 'p') {
                pos.push_back(i);
            }
        }
        int k = pos.size();
        vector<long long> suff(k + 2, 0);
        for (int i = k - 1; i >= 1; --i) {
            suff[i] = (pos[i] - pos[i - 1]) + suff[i + 2];
        }
        
        long long min_cost = -1;
        int ans = -1;
        long long pref = 0;
        for (int i = 1; i <= k; ++i) {
            long long cost;
            if (i % 2 == 1) {
                cost = pref + suff[i + 1];
            } else {
                cost = pref + (pos[i] - pos[i - 2]) + suff[i + 2];
                pref += (pos[i - 1] - pos[i - 2]);
            }
            if (min_cost == -1 || cost < min_cost) {
                min_cost = cost;
                ans = i;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
