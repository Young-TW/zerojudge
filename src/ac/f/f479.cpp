#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAX_PRIME = 150000;
    vector<bool> is_prime(MAX_PRIME + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= MAX_PRIME; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= MAX_PRIME; i += p) {
                is_prime[i] = false;
            }
        }
    }
    
    vector<long long> P(10001);
    P[1] = 1;
    int idx = 2;
    for (int i = 2; i <= MAX_PRIME && idx <= 10000; ++i) {
        if (is_prime[i]) {
            P[idx++] = i;
        }
    }
    
    vector<long long> S(10001, 0);
    for (int i = 1; i <= 10000; ++i) {
        S[i] = S[i - 1] + P[i];
    }
    
    int N;
    long long K;
    while (cin >> N >> K) {
        if (K > S[N]) {
            cout << "#\n";
        } else {
            int i = lower_bound(S.begin() + 1, S.begin() + N + 1, K) - S.begin();
            long long j = K - S[i - 1];
            char c = 'A' + (j - 1) % 3;
            cout << c << "\n";
        }
    }
    
    return 0;
}
