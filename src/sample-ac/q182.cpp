#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S;
    while (cin >> S) {
        int k;
        cin >> k;
        while (k--) {
            int op;
            cin >> op;
            if (op == 0) {
                for (size_t i = 0; i + 1 < S.length(); i += 2) {
                    swap(S[i], S[i+1]);
                }
            } else if (op == 1) {
                for (size_t i = 0; i + 1 < S.length(); i += 2) {
                    if (S[i] > S[i+1]) {
                        swap(S[i], S[i+1]);
                    }
                }
            } else if (op == 2) {
                int n = S.length();
                int half = n / 2;
                string res(n, ' ');
                for (int i = 0; i < half; ++i) {
                    res[2 * i] = S[i];
                    res[2 * i + 1] = S[half + i];
                }
                S = res;
            }
        }
        cout << S << "\n";
    }
    
    return 0;
}
