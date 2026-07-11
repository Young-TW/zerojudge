#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int MAXN = 10000000;
bool is_composite[MAXN + 1];
vector<int> primes;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 2; i <= MAXN; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            if ((long long)i * i <= MAXN) {
                for (long long j = (long long)i * i; j <= MAXN; j += i) {
                    is_composite[j] = true;
                }
            }
        }
    }

    int T;
    while (cin >> T) {
        while (T--) {
            long long a, b;
            if (!(cin >> a >> b)) break;
            if (a > b) {
                swap(a, b);
            }
            auto it_l = lower_bound(primes.begin(), primes.end(), a);
            auto it_r = upper_bound(primes.begin(), primes.end(), b);
            cout << (it_r - it_l) << "\n";
        }
    }

    return 0;
}
