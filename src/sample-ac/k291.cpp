#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<int> tails;
        tails.reserve(n);
        for (int i = 0; i < n; i++) {
            int x = a[i];
            vector<int>::iterator it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end()) tails.push_back(x);
            else *it = x;
        }
        cout << tails.size() << "\n";
    }
    return 0;
}
