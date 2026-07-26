#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> nums;
    string buf;
    char ch;

    while (cin.get(ch)) {
        if (ch >= '0' && ch <= '9') {
            buf.push_back(ch);
        } else {
            if (!buf.empty()) {
                if (nums.size() < 2) {
                    nums.push_back(stoll(buf));
                }
                buf.clear();
                if (nums.size() == 2) {
                    // we already have the two numbers; continue reading
                    // only to consume the input, but we ignore further numbers
                }
            }
        }
    }
    if (!buf.empty() && nums.size() < 2) {
        nums.push_back(stoll(buf));
    }

    if (nums.size() == 2) {
        long long a = nums[0];
        long long b = nums[1];
        cout << a << ' ' << b << ' ' << (a + b) << '\n';
    }
    return 0;
}
