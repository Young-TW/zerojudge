#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            long long N;
            cin >> N;
            
            if (N == 0) {
                cout << 10 << "\n";
            } else if (N == 1) {
                cout << 1 << "\n";
            } else {
                string ans = "";
                for (int i = 9; i >= 2; --i) {
                    while (N % i == 0) {
                        ans = char('0' + i) + ans;
                        N /= i;
                    }
                }
                
                if (N != 1) {
                    cout << -1 << "\n";
                } else {
                    cout << ans << "\n";
                }
            }
        }
    }
    
    return 0;
}
