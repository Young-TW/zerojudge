#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>

using namespace std;

const int MAX_N = 10000000;

int digit_sum(int x) {
    int sum = 0;
    while (x) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int fun1(int n) {
    int start = max(1, n - 100);
    for (int x = start; x < n; ++x) {
        if (x + digit_sum(x) == n) {
            return x;
        }
    }
    return -1;
}

int fun2(int a, int b, const vector<int>& self_prefix) {
    if (a > b) swap(a, b);
    return self_prefix[b] - self_prefix[a - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<char> generated(MAX_N + 1, 0);
    for (int x = 1; x <= MAX_N; ++x) {
        int y = x;
        int tmp = x;
        while (tmp) {
            y += tmp % 10;
            tmp /= 10;
        }
        if (y <= MAX_N) {
            generated[y] = 1;
        }
    }

    vector<int> self_prefix(MAX_N + 1, 0);
    for (int i = 1; i <= MAX_N; ++i) {
        self_prefix[i] = self_prefix[i - 1] + (generated[i] ? 0 : 1);
    }

    int T;
    if (!(cin >> T)) return 0;
    string line;
    getline(cin, line);

    for (int tc = 1; tc <= T; ++tc) {
        getline(cin, line);
        stringstream ss(line);
        vector<int> nums;
        int x;
        while (ss >> x) {
            nums.push_back(x);
        }

        int result = 0;
        if (nums.size() == 1) {
            result = fun1(nums[0]);
        } else if (nums.size() == 2) {
            result = fun2(nums[0], nums[1], self_prefix);
        }

        cout << "Case " << tc << ": " << result << '\n';
    }

    return 0;
}
