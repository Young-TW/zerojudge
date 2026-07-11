#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<int> P(N);
        vector<int> J(N);
        for (int i = 0; i < N; ++i) {
            cin >> P[i];
        }
        for (int i = 0; i < N; ++i) {
            cin >> J[i];
        }
        
        vector<int> f(N + 1);
        for (int i = 0; i < N; ++i) {
            f[P[i]] = i + 1;
        }
        
        vector<int> v;
        for (int i = 0; i < N; ++i) {
            int x = f[J[i]];
            auto it = lower_bound(v.begin(), v.end(), x, greater<int>());
            if (it == v.end()) {
                v.push_back(x);
            } else {
                *it = x;
            }
        }
        
        cout << v.size() << "\n";
    }
    
    return 0;
}
