#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        vector<int> degree(n + 1, 0);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            degree[a]++;
            degree[b]++;
        }
        
        int odd_count = 0;
        for (int i = 1; i <= n; ++i) {
            if (degree[i] % 2 != 0) {
                odd_count++;
            }
        }
        
        if (odd_count == 0 || odd_count == 2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
