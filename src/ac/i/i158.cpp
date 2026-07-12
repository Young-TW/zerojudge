#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        string output;
        output.reserve(n * (n + 1LL) / 2 + n);
        for (int i = 1; i <= n; ++i) {
            int mask = i - 1;
            for (int k = 0; k < i; ++k) {
                if ((mask & k) == k) {
                    output += '*';
                } else {
                    output += ' ';
                }
            }
            output += '\n';
        }
        cout << output;
    }
    return 0;
}
