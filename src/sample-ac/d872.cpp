#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        sort(a.begin(), a.end());
        
        long long total_time = 0;
        int i = n - 1;
        
        while (i >= 3) {
            long long plan1 = 2LL * a[0] + a[i] + a[i - 1];
            long long plan2 = a[0] + 2LL * a[1] + a[i];
            total_time += min(plan1, plan2);
            i -= 2;
        }
        
        if (i == 2) {
            total_time += a[0] + a[1] + a[2];
        } else if (i == 1) {
            total_time += a[1];
        } else if (i == 0) {
            total_time += a[0];
        }
        
        cout << total_time << "\n";
    }
    
    return 0;
}
