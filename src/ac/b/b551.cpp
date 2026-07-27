#include <bits/stdc++.h>
using namespace std;

bool survivor_is_one(int n, long long k, int start_i) {
    vector<int> circle;
    circle.reserve(n);
    for (int i = 1; i <= n; ++i) circle.push_back(i);

    int s = start_i - 1;                     // current start index (0‑based)

    while (circle.size() > 1) {
        int m = (int)circle.size();
        int step = (int)((k - 1) % m);
        int kill = (s + step) % m;           // index of the killed person

        // remove killed
        circle.erase(circle.begin() + kill);
        if (circle.empty()) break;           // only possible when n==1

        int sz = (int)circle.size();         // size after removal
        int left = kill % sz;                // clockwise neighbour of killed

        int step2 = (int)((k - 1) % sz);
        int burier = (left + step2) % sz;    // index of the burier

        if (burier != left) {
            int val = circle[burier];
            circle.erase(circle.begin() + burier);
            if (burier < left) --left;       // indices shifted left
            circle.insert(circle.begin() + left, val);
        }
        // next start is the former left neighbour, now at left+1
        s = (left + 1) % (int)circle.size();
    }
    return !circle.empty() && circle[0] == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    while (cin >> n >> k) {
        int answer = 1;
        for (int i = 1; i <= n; ++i) {
            if (survivor_is_one(n, k, i)) {
                answer = i;
                break;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
