#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    bool first_case = true;
    while (cin >> n) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        
        while (true) {
            for (size_t i = 0; i < v.size(); ++i) {
                cout << v[i];
                if (i < v.size() - 1) {
                    cout << " ";
                }
            }
            cout << "\n";
            
            if (v.size() == 1) {
                break;
            }
            
            v.erase(v.begin());
            reverse(v.begin(), v.end());
        }
    }
    
    return 0;
}
