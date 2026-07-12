#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            string s;
            cin >> s;
            unsigned long long ans = 0;
            for (size_t j = 0; j < s.length(); ++j) {
                ans *= 4;
                char c = s[j];
                if (c == 'A') {
                    ans += 0;
                } else if (c == 'C') {
                    ans += 1;
                } else if (c == 'G') {
                    ans += 2;
                } else if (c == 'T') {
                    ans += 3;
                }
            }
            cout << "Case " << i << ": (" << s.length() << ":" << ans << ")\n";
        }
    }
    
    return 0;
}
