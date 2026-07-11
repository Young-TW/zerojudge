#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

bool isPalindrome(int h, int m) {
    string s = "";
    if (h == 0) {
        s = to_string(m);
    } else {
        s = to_string(h);
        if (m < 10) {
            s += "0";
        }
        s += to_string(m);
    }
    string rev = s;
    reverse(rev.begin(), rev.end());
    return s == rev;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> palindromes;
    for (int h = 0; h < 24; ++h) {
        for (int m = 0; m < 60; ++m) {
            if (isPalindrome(h, m)) {
                palindromes.push_back(h * 60 + m);
            }
        }
    }

    int n;
    while (cin >> n) {
        while (n--) {
            string timeStr;
            cin >> timeStr;
            int h = (timeStr[0] - '0') * 10 + (timeStr[1] - '0');
            int m = (timeStr[3] - '0') * 10 + (timeStr[4] - '0');
            int curr = h * 60 + m;

            auto it = upper_bound(palindromes.begin(), palindromes.end(), curr);
            int nextTime;
            if (it != palindromes.end()) {
                nextTime = *it;
            } else {
                nextTime = palindromes[0];
            }

            int nextH = nextTime / 60;
            int nextM = nextTime % 60;
            cout << setw(2) << setfill('0') << nextH << ":"
                 << setw(2) << setfill('0') << nextM << "\n";
        }
    }

    return 0;
}
