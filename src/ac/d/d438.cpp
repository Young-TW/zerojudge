#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000000;
bool is_prime[MAXN + 1];
int prefix[MAXN + 1];

void sieve() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAXN; ++i) {
        if (is_prime[i]) {
            int sum = 0;
            int temp = i;
            while (temp > 0) {
                sum += temp % 10;
                temp /= 10;
            }
            if (is_prime[sum]) {
                prefix[i] = prefix[i - 1] + 1;
            } else {
                prefix[i] = prefix[i - 1];
            }
            for (long long j = 1LL * i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        } else {
            prefix[i] = prefix[i - 1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    int N;
    while (cin >> N) {
        while (N--) {
            int t1, t2;
            cin >> t1 >> t2;
            cout << prefix[t2] - prefix[t1 - 1] << "\n";
        }
    }
    return 0;
}
