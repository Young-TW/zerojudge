#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const int LIMIT = 40000;
    vector<bool> isPrime(LIMIT + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; (long long)i * i <= LIMIT; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= LIMIT; j += i) {
                isPrime[j] = false;
            }
        }
    }
    int primes[3501];
    int cnt = 0;
    for (int i = 2; i <= LIMIT && cnt < 3501; i++) {
        if (isPrime[i]) primes[cnt++] = i;
    }
    
    int ans[3502];
    ans[1] = 1;
    for (int n = 2; n <= 3501; n++) {
        int a = 0;
        for (int k = n - 1; k >= 1; k--) {
            int i = n - k + 1;
            a = (a + primes[k - 1]) % i;
        }
        ans[n] = a + 1;
    }
    
    int n;
    while (cin >> n && n) {
        cout << ans[n] << "\n";
    }
    return 0;
}
