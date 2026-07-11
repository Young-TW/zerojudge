#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    while (cin >> s) {
        long long sum = 0;
        int len = s.length();
        for (int i = 0; i < len; i += 3) {
            int num = 0;
            for (int j = 0; j < 3; ++j) {
                num *= 10;
                if (i + j < len) {
                    num += (s[i + j] - '0');
                }
            }
            sum += num;
        }
        cout << sum % 997 << "\n";
    }
    return 0;
}
