#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAXN = 123456;
    vector<bool> is_prime(MAXN + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAXN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    vector<int> cnt(MAXN + 1, 0);
    for (int i = 3; i <= MAXN; ++i) {
        cnt[i] = cnt[i - 1];
        if (i + 2 <= MAXN && is_prime[i] && is_prime[i + 2]) {
            cnt[i]++;
        }
    }
    
    int n;
    while (cin >> n) {
        if (n < 5) {
            cout << 0 << "\n";
        } else {
            cout << cnt[n - 2] << "\n";
        }
    }
    
    return 0;
}
