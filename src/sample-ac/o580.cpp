#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    while (cin >> a >> b) {
        int len = (int)(b - a + 1);
        vector<int> cnt(len, 1);
        vector<long long> rem(len);
        for (int i = 0; i < len; i++) {
            rem[i] = a + i;
        }
        
        long long sqb = (long long)sqrt((double)b);
        while ((sqb + 1) * (sqb + 1) <= b) sqb++;
        while (sqb > 0 && sqb * sqb > b) sqb--;
        
        vector<bool> isPrime(sqb + 1, true);
        if (sqb >= 0) isPrime[0] = false;
        if (sqb >= 1) isPrime[1] = false;
        
        for (long long i = 2; i <= sqb; i++) {
            if (isPrime[i]) {
                for (long long j = i * i; j <= sqb; j += i) {
                    isPrime[j] = false;
                }
                long long start = ((a + i - 1) / i) * i;
                for (long long m = start; m <= b; m += i) {
                    int idx = (int)(m - a);
                    long long e = 0;
                    while (rem[idx] % i == 0) {
                        rem[idx] /= i;
                        e++;
                    }
                    cnt[idx] *= (int)(e + 1);
                }
            }
        }
        
        long long bestNum = a;
        int bestCnt = 0;
        for (int i = 0; i < len; i++) {
            if (rem[i] > 1) {
                cnt[i] *= 2;
            }
            if (cnt[i] > bestCnt) {
                bestCnt = cnt[i];
                bestNum = a + i;
            }
        }
        
        cout << bestNum << " " << bestCnt << "\n";
    }
    
    return 0;
}
