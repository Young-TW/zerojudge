#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int l, int r, bool is_max, const vector<int>& arr) {
    if (l == r) {
        return arr[l];
    }
    int mid = l + (r - l) / 2;
    int left_val = solve(l, mid, !is_max, arr);
    int right_val = solve(mid + 1, r, !is_max, arr);
    if (is_max) {
        return max(left_val, right_val);
    } else {
        return min(left_val, right_val);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        vector<int> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i];
        }
        cout << solve(0, N - 1, true, arr) << "\n";
    }
    return 0;
}
