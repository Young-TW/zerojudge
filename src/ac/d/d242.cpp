#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums;
    int num;
    while (cin >> num) {
        nums.push_back(num);
    }

    int n = nums.size();
    vector<int> dp(n, 1);
    vector<int> prev(n, -1);
    vector<int> tail;

    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(tail.begin(), tail.end(), nums[i]);
        if (it == tail.end()) {
            tail.push_back(nums[i]);
            if (tail.size() > 1) {
                prev[i] = dp[tail.size() - 2] - 1;
            }
            dp[tail.size() - 1] = i + 1;
        } else {
            int pos = it - tail.begin();
            *it = nums[i];
            if (pos > 0) {
                prev[i] = dp[pos - 1] - 1;
            }
            dp[pos] = i + 1;
        }
    }

    int len = tail.size();
    cout << len << "\n-\n";

    vector<int> result;
    int idx = dp[len - 1] - 1;
    while (idx != -1) {
        result.push_back(nums[idx]);
        idx = prev[idx];
    }

    reverse(result.begin(), result.end());
    for (int x : result) {
        cout << x << "\n";
    }

    return 0;
}
