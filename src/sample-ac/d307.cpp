#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 33000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool is_prime[MAXN];
    for (int i = 2; i < MAXN; ++i) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAXN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 3; i < MAXN; i += 2) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    int ans[MAXN] = {0};
    for (int i = 6; i < MAXN; i += 2) {
        int count = 0;
        for (size_t j = 0; j < primes.size() && primes[j] <= i / 2; ++j) {
            if (is_prime[i - primes[j]]) {
                count++;
            }
        }
        ans[i] = count;
    }

    int n;
    while (cin >> n && n) {
        cout << ans[n] << "\n";
    }

    return 0;
}
