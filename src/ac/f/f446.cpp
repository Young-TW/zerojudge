#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    while (T--) {
        int D;
        cin >> D;
        vector<string> names(D);
        vector<int> L(D), H(D);
        for (int i = 0; i < D; ++i) {
            cin >> names[i] >> L[i] >> H[i];
        }
        
        int Q;
        cin >> Q;
        while (Q--) {
            int P;
            cin >> P;
            string ans = "UNDETERMINED";
            int match_count = 0;
            for (int i = 0; i < D; ++i) {
                if (L[i] <= P && P <= H[i]) {
                    match_count++;
                    if (match_count == 1) {
                        ans = names[i];
                    } else {
                        ans = "UNDETERMINED";
                        break;
                    }
                }
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}
