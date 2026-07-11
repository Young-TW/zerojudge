#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, K;
    while (cin >> N >> K) {
        bool lucky = false;
        
        if (N % K == 0) {
            lucky = true;
        } else {
            long long temp = N;
            while (temp > 0) {
                if (temp % 10 == K) {
                    lucky = true;
                    break;
                }
                temp /= 10;
            }
        }
        
        if (lucky) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
