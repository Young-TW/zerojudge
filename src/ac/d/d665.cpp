#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        vector<int> L(n, -1);
        vector<int> R(n, -1);
        
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && a[s.top()] < a[i]) {
                s.pop();
            }
            if (!s.empty()) {
                L[i] = s.top();
            }
            s.push(i);
        }
        
        while (!s.empty()) {
            s.pop();
        }
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && a[s.top()] <= a[i]) {
                s.pop();
            }
            if (!s.empty()) {
                R[i] = s.top();
            }
            s.push(i);
        }
        
        long long total_cost = 0;
        for (int i = 0; i < n; ++i) {
            long long cost = 0;
            bool hasL = (L[i] != -1);
            bool hasR = (R[i] != -1);
            if (hasL && hasR) {
                cost = min(a[L[i]], a[R[i]]);
            } else if (hasL) {
                cost = a[L[i]];
            } else if (hasR) {
                cost = a[R[i]];
            }
            total_cost += cost;
        }
        
        cout << total_cost << "\n";
    }
    
    return 0;
}
