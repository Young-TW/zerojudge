#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1299710;
bool is_prime[MAXN];

void sieve() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAXN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve();
    
    int k;
    while (cin >> k && k != 0) {
        if (is_prime[k]) {
            cout << 0 << "\n";
        } else {
            int p1 = k - 1;
            while (!is_prime[p1]) {
                p1--;
            }
            int p2 = k + 1;
            while (!is_prime[p2]) {
                p2++;
            }
            cout << p2 - p1 << "\n";
        }
    }
    
    return 0;
}
