#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MOD = 998244353;
    const int MAX_N = 10000;
    
    int pow3[MAX_N + 5];
    pow3[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        pow3[i] = (long long)pow3[i - 1] * 3 % MOD;
    }
    
    int T;
    if (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            if (N == 1) {
                cout << 1 << "\n";
            } else if (N == 2) {
                cout << 2 << "\n";
            } else if (N == 3) {
                cout << 3 << "\n";
            } else {
                int r = N % 3;
                if (r == 0) {
                    cout << pow3[N / 3] << "\n";
                } else if (r == 1) {
                    cout << (long long)pow3[(N - 4) / 3] * 4 % MOD << "\n";
                } else {
                    cout << (long long)pow3[(N - 2) / 3] * 2 % MOD << "\n";
                }
            }
        }
    }
    
    return 0;
}
