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
        
        int max_val = v[0], min_val = v[0];
        int max_pos = 1, min_pos = 1;
        
        for (int i = 1; i < n; ++i) {
            if (v[i] > max_val) {
                max_val = v[i];
                max_pos = i + 1;
            }
            if (v[i] < min_val) {
                min_val = v[i];
                min_pos = i + 1;
            }
        }
        
        cout << max_val << " " << max_pos << "\n";
        cout << min_val << " " << min_pos << "\n";
    }
    
    return 0;
}
