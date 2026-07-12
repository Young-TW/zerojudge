#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long x;
    while (cin >> x) {
        if (x == 0) {
            cout << "0\n";
            continue;
        }
        
        bool neg = (x < 0);
        long long n = x < 0 ? -x : x;
        long long k = 1;
        long long m = n;
        
        while (m % 4 == 0) {
            k *= 2;
            m /= 4;
        }
        
        for (long long i = 3; i * i <= m; i += 2) {
            while (m % (i * i) == 0) {
                k *= i;
                m /= (i * i);
            }
        }
        
        if (m == 1) {
            // magnitude 為 1 且為負數時應輸出 "i" 而非 "1i"
            if (!(neg && k == 1)) {
                cout << k;
            }
        } else {
            if (k == 1) {
                cout << "_/" << m;
            } else {
                cout << k << "_/" << m;
            }
        }
        
        if (neg) {
            cout << "i";
        }
        cout << "\n";
    }
    
    return 0;
}
