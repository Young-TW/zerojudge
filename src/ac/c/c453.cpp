#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<unsigned long long> cat(n + 1, 0);
        cat[0] = 1;
        for (int i = 1; i <= n; ++i) {
            unsigned __int128 sum = 0;
            for (int j = 0; j < i; ++j) {
                sum += (unsigned __int128)cat[j] * cat[i - 1 - j];
            }
            cat[i] = (unsigned long long)sum;
        }
        cout << cat[n] << '\n';
    }
    return 0;
}
