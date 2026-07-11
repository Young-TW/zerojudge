#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        
        cout << v.size() << "\n";
        for (size_t i = 0; i < v.size(); ++i) {
            cout << v[i];
            if (i + 1 < v.size()) {
                cout << " ";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
