#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <bitset>
#include <utility>

using namespace std;

const int MAX_TARGET = 10000000;
std::bitset<MAX_TARGET + 5> dp;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, N;
    while (cin >> M >> N) {
        while (M--) {
            vector<long long> arr(N);
            long long sum = 0;
            for (int i = 0; i < N; ++i) {
                cin >> arr[i];
                sum += arr[i];
            }
            if (sum % 2 != 0) {
                cout << "No\n";
                continue;
            }
            long long target = sum / 2;
            
            long long g = 0;
            for (long long x : arr) {
                long long a = g, b = x;
                while (b) {
                    a %= b;
                    swap(a, b);
                }
                g = a;
            }
            if (g == 0) {
                cout << (target == 0 ? "Yes" : "No") << "\n";
                continue;
            }
            if (target % g != 0) {
                cout << "No\n";
                continue;
            }
            target /= g;
            for (long long& x : arr) x /= g;

            vector<long long> filtered_arr;
            long long current_sum = 0;
            for (long long x : arr) {
                if (x <= target) {
                    filtered_arr.push_back(x);
                    current_sum += x;
                }
            }
            if (current_sum < target) {
                cout << "No\n";
                continue;
            }
            if (target == 0) {
                cout << "Yes\n";
                continue;
            }

            sort(filtered_arr.rbegin(), filtered_arr.rend());

            bool found = false;
            if (target <= MAX_TARGET) {
                dp.reset();
                dp[0] = 1;
                for (long long x : filtered_arr) {
                    dp |= (dp << x);
                    if (dp[target]) {
                        found = true;
                        break;
                    }
                }
            } else {
                std::unordered_set<long long> us_dp;
                us_dp.insert(0);
                for (long long x : filtered_arr) {
                    vector<long long> to_add;
                    for (long long y : us_dp) {
                        if (y + x <= target) {
                            to_add.push_back(y + x);
                        }
                    }
                    for (long long y : to_add) {
                        us_dp.insert(y);
                    }
                    if (us_dp.count(target)) {
                        found = true;
                        break;
                    }
                }
            }
            cout << (found ? "Yes" : "No") << "\n";
        }
    }
    return 0;
}
