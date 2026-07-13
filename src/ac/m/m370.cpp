#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, n;
    while (cin >> x >> n) {
        vector<int> left, right;
        for (int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            if (p < x) {
                left.push_back(p);
            } else if (p > x) {
                right.push_back(p);
            }
        }
        
        int left_count = left.size();
        int right_count = right.size();
        
        if (left_count > right_count) {
            int min_pos = *min_element(left.begin(), left.end());
            cout << left_count << " " << min_pos << "\n";
        } else {
            int max_pos = *max_element(right.begin(), right.end());
            cout << right_count << " " << max_pos << "\n";
        }
    }
    
    return 0;
}
