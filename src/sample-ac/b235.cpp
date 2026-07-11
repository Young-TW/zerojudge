#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int MAXN = 20000;
    vector<bool> is_prime(MAXN + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAXN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= MAXN; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    vector<int> ans;
    for (int A : primes) {
        if (A == 2 || A == 3) continue;
        bool found = false;
        for (int B : primes) {
            if (B >= A) break;
            int C = 2 * A - B;
            if (C <= MAXN && is_prime[C]) {
                found = true;
                break;
            }
        }
        if (found) {
            ans.push_back(A);
        }
    }

    int k;
    while (cin >> k) {
        while (k--) {
            int n;
            cin >> n;
            cout << ans[n - 1] << "\n";
        }
    }

    return 0;
}
