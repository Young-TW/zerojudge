#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long N;
    while (cin >> N) {
        if (N == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        int len = 0;
        int c1 = 0;
        long long temp = N;
        
        while (temp > 0) {
            if (temp & 1) {
                c1++;
            }
            len++;
            temp >>= 1;
        }
        
        cout << (1LL << (len - c1)) << "\n";
    }
    
    return 0;
}
