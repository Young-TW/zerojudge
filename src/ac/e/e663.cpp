#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> answers;
    vector<int> s(10);
    while (cin >> s[0]) {
        for (int i = 1; i < 10; ++i) {
            if (!(cin >> s[i])) return 0;
        }
        sort(s.begin(), s.end());
        long long total = 0;
        for (int i = 0; i < 10; ++i) total += s[i];
        total /= 4; // sum of five weights

        long long ab = s[0];       // a + b
        long long de = s[9];       // d + e
        long long c = total - ab - de;
        long long e = s[8] - c;    // s[8] = c + e
        long long d = s[9] - e;
        long long a = s[1] - c;    // s[1] = a + c
        long long b = s[0] - a;

        vector<int> w;
        w.push_back((int)a);
        w.push_back((int)b);
        w.push_back((int)c);
        w.push_back((int)d);
        w.push_back((int)e);
        sort(w.begin(), w.end());
        answers.push_back(w);
    }

    for (size_t i = 0; i < answers.size(); ++i) {
        for (int j = 0; j < 5; ++j) {
            if (j) cout << ' ';
            cout << answers[i][j];
        }
        if (i + 1 < answers.size()) cout << "\n\n\n\n";
    }
    return 0;
}
