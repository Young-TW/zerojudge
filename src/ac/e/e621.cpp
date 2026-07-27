#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (!(cin >> N)) return 0;
    while (N--) {
        long long A, B, C;
        cin >> A >> B >> C;
        vector<long long> ans;
        for (long long x = A + 1; x < B; ++x) {
            if (x % C != 0) ans.push_back(x);
        }
        if (ans.empty()) {
            cout << "No free parking spaces.\n";
        } else {
            for (size_t i = 0; i < ans.size(); ++i) {
                if (i) cout << ' ';
                cout << ans[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
