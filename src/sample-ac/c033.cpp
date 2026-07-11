#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAXN = 1000;
    bool is_prime[MAXN + 1];
    for (int i = 0; i <= MAXN; ++i) {
        is_prime[i] = true;
    }
    is_prime[0] = false;
    // is_prime[1] is true as per problem description
    
    for (int i = 2; i * i <= MAXN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    int N, C;
    while (cin >> N >> C) {
        vector<int> primes;
        for (int i = 1; i <= N; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
            }
        }
        
        int K = primes.size();
        int size = (K % 2 == 0) ? (2 * C) : (2 * C - 1);
        
        cout << N << " " << C << ":";
        if (size >= K) {
            for (int i = 0; i < K; ++i) {
                cout << " " << primes[i];
            }
        } else {
            int start = (K - size) / 2;
            for (int i = start; i < start + size; ++i) {
                cout << " " << primes[i];
            }
        }
        cout << "\n\n";
    }
    
    return 0;
}
