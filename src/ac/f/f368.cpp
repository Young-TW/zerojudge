#include <iostream>
#include <string>
#include <vector>

using namespace std;

string power_of_two(int count) {
    if (count == 0) return "1";
    if (count <= 62) {
        return to_string(1ULL << count);
    }
    vector<int> res;
    res.push_back(1);
    for (int i = 0; i < count; ++i) {
        int carry = 0;
        for (size_t j = 0; j < res.size(); ++j) {
            int val = res[j] * 2 + carry;
            res[j] = val % 10;
            carry = val / 10;
        }
        while (carry) {
            res.push_back(carry % 10);
            carry /= 10;
        }
    }
    string ans = "";
    for (int i = res.size() - 1; i >= 0; --i) {
        ans += (char)('0' + res[i]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    while (cin >> s) {
        int count = 0;
        for (size_t i = 0; i < s.length(); ) {
            if (s.compare(i, 3, "RED") == 0) {
                count++;
                i += 3;
            } else if (s.compare(i, 5, "GREEN") == 0) {
                count++;
                i += 5;
            } else {
                i++;
            }
        }
        cout << "1/" << power_of_two(count) << "\n";
    }
    return 0;
}
