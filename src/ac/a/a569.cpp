#include <iostream>
#include <sstream>
#include <string>
#include <bitset>

using namespace std;

const int MAXV = 10000000;
bitset<MAXV + 1> is_prime;

void sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= MAXV; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAXV; j += i) {
                is_prime[j] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int x;
        long long current_sum = 0;
        long long ans = 0;
        int last_prime = -1;
        bool has_num = false;
        while (ss >> x) {
            has_num = true;
            if (x >= 0 && x <= MAXV && is_prime[x]) {
                if (x > last_prime) {
                    current_sum += x;
                } else {
                    current_sum = x;
                }
                last_prime = x;
                if (current_sum > ans) {
                    ans = current_sum;
                }
            } else {
                current_sum = 0;
                last_prime = -1;
            }
        }
        if (has_num) {
            cout << ans << "\n";
        }
    }
    return 0;
}
