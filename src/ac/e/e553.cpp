#include <iostream>
#include <string>

using namespace std;

int ans[101];

void precompute() {
    int sum = 0;
    for (int i = 1; i <= 100; ++i) {
        int base = i % 10;
        int exp = (i - 1) % 4 + 1;
        int pow_val = 1;
        for (int j = 0; j < exp; ++j) {
            pow_val = (pow_val * base) % 10;
        }
        sum = (sum + pow_val) % 10;
        ans[i] = sum;
    }
    ans[0] = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precompute();
    string s;
    while (cin >> s && s != "0") {
        int n;
        if (s.length() == 1) {
            n = s[0] - '0';
        } else {
            n = (s[s.length() - 2] - '0') * 10 + (s[s.length() - 1] - '0');
        }
        cout << ans[n] << "\n";
    }
    return 0;
}
