#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    if (cin >> N) {
        while (N--) {
            int m;
            cin >> m;
            vector<long long> a(m);
            for (int i = 0; i < m; ++i) {
                cin >> a[i];
            }
            sort(a.begin(), a.end());
            long long median = a[m / 2];
            long long sum = 0;
            for (int i = 0; i < m; ++i) {
                long long diff = a[i] - median;
                if (diff < 0) diff = -diff;
                sum += diff;
            }
            cout << sum << '\n';
        }
    }
    
    return 0;
}
