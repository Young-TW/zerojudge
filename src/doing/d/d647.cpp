#include <iostream>
#include <string>

using namespace std;

string solve(long long n) {
    string res = "";
    bool first = true;
    for (int i = 31; i >= 0; --i) {
        if ((n >> i) & 1) {
            if (!first) {
                res += "+";
            }
            first = false;
            if (i == 0) {
                res += "2(0)";
            } else if (i == 1) {
                res += "2";
            } else {
                res += "2(" + solve(i) + ")";
            }
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n;
    while (cin >> n) {
        cout << solve(n) << "\n";
    }
    return 0;
}
