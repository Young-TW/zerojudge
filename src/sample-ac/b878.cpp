#include <iostream>
#include <vector>
#include <stack>
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
        
        vector<int> a(n + 2);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        
        vector<int> L(n + 2, 0);
        vector<int> R(n + 2, n + 1);
        
        stack<int> s;
        for (int i = 1; i <= n; ++i) {
            while (!s.empty() && a[s.top()] >= a[i]) {
                s.pop();
            }
            if (!s.empty()) {
                L[i] = s.top();
            } else {
                L[i] = 0;
            }
            s.push(i);
        }
        
        while (!s.empty()) {
            s.pop();
        }
        
        for (int i = n; i >= 1; --i) {
            while (!s.empty() && a[s.top()] >= a[i]) {
                s.pop();
            }
            if (!s.empty()) {
                R[i] = s.top();
            } else {
                R[i] = n + 1;
            }
            s.push(i);
        }
        
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            long long distL = i - L[i];
            long long distR = R[i] - i;
            ans += min(distL, distR);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
