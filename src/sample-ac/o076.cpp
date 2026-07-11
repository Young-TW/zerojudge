#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        
        int max_len = 1;
        int current_len = 1;
        
        for (int i = 1; i < n; ++i) {
            if (h[i] < h[i - 1]) {
                current_len++;
            } else {
                current_len = 1;
            }
            max_len = max(max_len, current_len);
        }
        
        cout << max_len << "\n";
    }
    
    return 0;
}
