#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<int> v;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            // v is kept non-increasing. Find first element strictly less than x.
            auto it = upper_bound(v.begin(), v.end(), x, greater<int>());
            if (it == v.end()) v.push_back(x);
            else *it = x;
        }
        cout << v.size() << '\n';
    }
    return 0;
}
