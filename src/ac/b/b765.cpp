#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

bool isValid(const string& id) {
    if (id.length() != 10) return false;
    char c = id[0];
    if (c < 'A' || c > 'Z') return false;
    if (id[1] != '1' && id[1] != '2') return false;
    for (int i = 2; i < 10; ++i) {
        if (id[i] < '0' || id[i] > '9') return false;
    }
    int val[26] = {10, 11, 12, 13, 14, 15, 16, 17, 34, 18, 19, 20, 21, 22, 35, 23, 24, 25, 26, 27, 28, 29, 32, 30, 31, 33};
    int n1 = val[c - 'A'] / 10;
    int n2 = val[c - 'A'] % 10;
    int sum = n1 * 1 + n2 * 9;
    int weights[] = {8, 7, 6, 5, 4, 3, 2, 1, 1};
    for (int i = 0; i < 9; ++i) {
        sum += (id[i + 1] - '0') * weights[i];
    }
    return sum % 10 == 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            int seq;
            string id;
            cin >> seq >> id;
            vector<string> ans;
            int star_pos = id.find('*');
            if (star_pos == 0) {
                for (char c = 'A'; c <= 'Z'; ++c) {
                    string temp = id;
                    temp[0] = c;
                    if (isValid(temp)) {
                        ans.push_back(temp);
                    }
                }
            } else {
                for (char c = '0'; c <= '9'; ++c) {
                    string temp = id;
                    temp[star_pos] = c;
                    if (isValid(temp)) {
                        ans.push_back(temp);
                    }
                }
            }
            cout << setw(3) << setfill('0') << seq;
            for (size_t j = 0; j < ans.size(); ++j) {
                cout << " " << ans[j];
            }
            cout << "\n";
        }
    }
    return 0;
}
