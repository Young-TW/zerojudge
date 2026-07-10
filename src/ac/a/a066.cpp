#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        set<int> s;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if (i == 0) {
                sum += a;
            } else {
                auto it = s.lower_bound(a);
                int best = INT_MAX;
                if (it != s.end()) best = min(best, abs(*it - a));
                if (it != s.begin()) {
                    auto pit = prev(it);
                    best = min(best, abs(*pit - a));
                }
                sum += best;
            }
            s.insert(a);
        }
        cout << sum << "\n";
    }
    return 0;
}
