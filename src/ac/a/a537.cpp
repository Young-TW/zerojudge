#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2005;
bool isPrime[MAXN];

void sieve() {
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAXN; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string s;
        cin >> s;
        int cnt[256];
        memset(cnt, 0, sizeof(cnt));
        for (char c : s) {
            cnt[(unsigned char)c]++;
        }
        cout << "Case " << t << ": ";
        string result;
        for (int c = 0; c < 256; c++) {
            if (cnt[c] > 0 && isPrime[cnt[c]]) {
                result += (char)c;
            }
        }
        if (result.empty()) {
            cout << "empty\n";
        } else {
            cout << result << "\n";
        }
    }
    return 0;
}
