#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    const int MAXP = 40000;
    vector<int> primes;
    vector<bool> is_composite(MAXP + 1, false);
    
    for (int i = 2; i <= MAXP; ++i) {
        if (!is_composite[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= MAXP; j += i) {
                is_composite[j] = true;
            }
        }
    }
    
    long long M, N, L;
    while (cin >> M >> N >> L && (M || N || L)) {
        long long mn = M * N;
        long long nl = N * L;
        long long lm = L * M;
        
        long long V = mn * mn + nl * nl + lm * lm;
        
        long long a = 1;
        long long b = V;
        
        for (int p : primes) {
            long long p2 = (long long)p * p;
            if (p2 > b) break;
            while (b % p2 == 0) {
                b /= p2;
                a *= p;
            }
        }
        
        if (b == 1) {
            cout << a << "\n";
        } else if (a == 1) {
            cout << "_/" << b << "\n";
        } else {
            cout << a << "_/" << b << "\n";
        }
    }
    
    return 0;
}
