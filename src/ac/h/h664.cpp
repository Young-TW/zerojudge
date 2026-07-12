#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        long long N, S;
        cin >> N >> S;
        long long ans = N;
        
        while (true) {
            long long mid = 1LL << (ans - 1);
            if (S == mid) {
                break;
            } else if (S < mid) {
                ans--;
            } else {
                S -= mid;
                ans--;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
