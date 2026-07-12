#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    while (cin >> N) {
        long long orig = N;
        cout << orig << " = ";
        bool first = true;
        
        for (long long i = 2; i * i <= N; ++i) {
            if (N % i == 0) {
                int cnt = 0;
                while (N % i == 0) {
                    N /= i;
                    cnt++;
                }
                if (!first) {
                    cout << " * ";
                }
                first = false;
                cout << i;
                if (cnt > 1) {
                    cout << "^" << cnt;
                }
            }
        }
        
        if (N > 1) {
            if (!first) {
                cout << " * ";
            }
            cout << N;
        }
        
        cout << "\n";
    }
    
    return 0;
}
