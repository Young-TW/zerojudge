#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cstdlib>
using namespace std;

int main() {
    int n;
    bool first = true;
    while (cin >> n) {
        if (!first) cout << endl;
        first = false;
        vector<tuple<int, int, int>> statues(n);
        for (int i = 0; i < n; i++) {
            int h, w;
            cin >> h >> w;
            statues[i] = make_tuple(h, w, i);
        }
        sort(statues.begin(), statues.end());
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int original = get<2>(statues[i]);
            ans += abs(i - original);
        }
        cout << ans << endl;
    }
    return 0;
}
