#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        char s[16];
        s[n] = '\0';
        int limit = 1 << n;
        for (int i = 0; i < limit; ++i) {
            for (int j = 0; j < n; ++j) {
                s[n - 1 - j] = ((i >> j) & 1) + '0';
            }
            puts(s);
        }
    }
    return 0;
}
