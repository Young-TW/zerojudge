#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int MAX_PRE = 2500000; 
int mu[MAX_PRE + 5];
long long M_pre[MAX_PRE + 5];
vector<int> primes;
bool is_prime[MAX_PRE + 5];
unordered_map<long long, long long> memo;

void sieve() {
    fill(is_prime, is_prime + MAX_PRE + 5, true);
    is_prime[0] = is_prime[1] = false;
    mu[1] = 1;
    for (int i = 2; i <= MAX_PRE; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (size_t j = 0; j < primes.size(); ++j) {
            int p = primes[j];
            if (i * p > MAX_PRE) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }
    M_pre[0] = 0;
    for (int i = 1; i <= MAX_PRE; ++i) {
        M_pre[i] = M_pre[i - 1] + mu[i];
    }
}

long long calc_M(long long n) {
    if (n <= MAX_PRE) return M_pre[n];
    if (memo.find(n) != memo.end()) return memo[n];
    
    long long res = 1;
    for (long long l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res -= (r - l + 1) * calc_M(n / l);
    }
    return memo[n] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve();
    
    int T;
    if (cin >> T) {
        while (T--) {
            long long N;
            cin >> N;
            // 清空 memo 以防萬一，但其實不同測資間可以共用？
            // 題目是多筆測資，N 不同。共用 memo 可以加速。
            // 但若 N 差異極大，memo 可能會變得很大。
            // 考慮到 T<=10，且 N 最大 2e9，狀態數有限，共用是安全的且更有效率。
            cout << calc_M(N) << "\n";
        }
    }
    return 0;
}
