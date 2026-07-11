#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            vector<int> nums(N);
            for (int i = 0; i < N; ++i) {
                cin >> nums[i];
            }

            sort(nums.begin(), nums.end());

            int min_dist_sq = INT_MAX;
            int sum = 0;
            for (int i = 0; i < N; ++i) {
                sum += nums[i];
            }

            for (int k = 0; k <= N; ++k) {
                int east = 0;
                for (int i = 0; i < k; ++i) {
                    east += nums[i];
                }
                int north = sum - east;
                int dist_sq = east * east + north * north;
                if (dist_sq < min_dist_sq) {
                    min_dist_sq = dist_sq;
                }
            }

            cout << min_dist_sq << '\n';
        }
    }

    return 0;
}
