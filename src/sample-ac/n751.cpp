#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long fact[21] = {1};
    for (int i = 1; i <= 20; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    int T;
    while (cin >> T) {
        while (T--) {
            string S;
            unsigned long long N;
            if (!(cin >> S >> N)) break;
            
            sort(S.begin(), S.end());
            
            string ans;
            int len = S.length();
            for (int i = len - 1; i >= 0; --i) {
                unsigned long long idx = N / fact[i];
                N %= fact[i];
                ans += S[idx];
                S.erase(S.begin() + idx);
            }
            cout << ans << "\n";
        }
    }

    return 0;
}
