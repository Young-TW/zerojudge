#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 10000005;
bool not_prime[MAX_N];
vector<int> primes;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 2; i < MAX_N; ++i) {
        if (!not_prime[i]) {
            primes.push_back(i);
            if ((long long)i * i < MAX_N) {
                for (int j = i * i; j < MAX_N; j += i) {
                    not_prime[j] = true;
                }
            }
        }
    }

    int N, m;
    while (cin >> N >> m) {
        while (m--) {
            int x;
            cin >> x;
            cout << (lower_bound(primes.begin(), primes.end(), x) - primes.begin() + 1) << '\n';
        }
    }

    return 0;
}
