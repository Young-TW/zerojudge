#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string n;
        int h;
        char s;
        cin >> n >> h >> s;

        vector<int> digits;
        for (char c : n) {
            digits.push_back(c - '0');
        }

        if (s == 'b') {
            sort(digits.begin(), digits.end(), greater<int>());
        } else {
            sort(digits.begin(), digits.end());
        }

        if (s == 'b') {
            do {
                h--;
                if (h == 0) break;
            } while (prev_permutation(digits.begin(), digits.end()));
        } else {
            do {
                h--;
                if (h == 0) break;
            } while (next_permutation(digits.begin(), digits.end()));
        }

        for (int d : digits) {
            cout << d;
        }
        cout << endl;
    }
    return 0;
}
