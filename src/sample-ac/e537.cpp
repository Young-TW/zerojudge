#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    bool first_case = true;
    while (cin >> N) {
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            
            int L = s.length();
            int ans = L;
            for (int p = 1; p <= L; ++p) {
                if (L % p == 0) {
                    bool ok = true;
                    for (int j = p; j < L; ++j) {
                        if (s[j] != s[j - p]) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        ans = p;
                        break;
                    }
                }
            }
            
            if (!first_case) {
                cout << "\n";
            }
            cout << ans << "\n";
            first_case = false;
        }
    }
    return 0;
}
