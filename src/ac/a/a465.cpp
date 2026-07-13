#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;
        string S;
        cin >> S;
        
        int ans = 0;
        for (int i = 0; i < N; ) {
            if (S[i] == '.') {
                ans++;
                i += 3;
            } else {
                i++;
            }
        }
        
        cout << "Case " << t << ": " << ans << "\n";
    }
    
    return 0;
}
