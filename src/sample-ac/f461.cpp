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
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += (long long)a[i] * (2LL * i - n + 1);
        }
        cout << sum << "\n";
    }
    
    return 0;
}
