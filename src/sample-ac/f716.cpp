#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    long long min_val = LLONG_MAX;
    long long max_val = LLONG_MIN;

    while (cin >> x) {
        min_val = min(min_val, x);
        max_val = max(max_val, x);
    }

    if (min_val != LLONG_MAX) {
        cout << min_val << " " << (max_val - min_val) << "\n";
    }

    return 0;
}
