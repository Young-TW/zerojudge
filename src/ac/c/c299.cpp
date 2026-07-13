#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            cin >> nums[i];
        }

        int min_val = *min_element(nums.begin(), nums.end());
        int max_val = *max_element(nums.begin(), nums.end());

        bool is_consecutive = true;
        if (max_val - min_val + 1 != n) {
            is_consecutive = false;
        } else {
            vector<bool> present(n, false);
            for (int num : nums) {
                int idx = num - min_val;
                if (idx < 0 || idx >= n || present[idx]) {
                    is_consecutive = false;
                    break;
                }
                present[idx] = true;
            }
        }

        cout << min_val << " " << max_val << " " << (is_consecutive ? "yes" : "no") << endl;
    }
    return 0;
}
