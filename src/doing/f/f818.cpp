#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 0) continue;
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
        }
        
        long long min_sum = a[0] + b[0];
        int idx = 0;
        for (int i = 1; i < n; ++i) {
            long long sum = a[i] + b[i];
            if (sum < min_sum) {
                min_sum = sum;
                idx = i;
            }
        }
        cout << a[idx] << " " << b[idx] << "\n";
    }
    return 0;
}
