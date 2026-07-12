#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int case_num = 1;
    while (cin >> n && n) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        sort(arr.begin(), arr.end());
        
        int m;
        cin >> m;
        cout << "Case " << case_num++ << ":\n";
        while (m--) {
            int query;
            cin >> query;
            
            int closest_sum = arr[0] + arr[1];
            int L = 0, R = n - 1;
            while (L < R) {
                int sum = arr[L] + arr[R];
                int diff1 = sum - query;
                if (diff1 < 0) diff1 = -diff1;
                int diff2 = closest_sum - query;
                if (diff2 < 0) diff2 = -diff2;
                
                if (diff1 < diff2) {
                    closest_sum = sum;
                }
                
                if (sum < query) {
                    L++;
                } else if (sum > query) {
                    R--;
                } else {
                    break;
                }
            }
            cout << "Closest sum to " << query << " is " << closest_sum << ".\n";
        }
    }
    return 0;
}
