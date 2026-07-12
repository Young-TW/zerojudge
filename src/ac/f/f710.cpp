#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (!(cin >> T)) return 0;
    
    for (int t = 1; t <= T; ++t) {
        string N;
        if (!(cin >> N)) break;
        
        int c0 = 0, c1 = 0, c2 = 0;
        for (char ch : N) {
            int d = ch - '0';
            if (d % 3 == 0) c0++;
            else if (d % 3 == 1) c1++;
            else c2++;
        }
        
        int S_mod = (c1 + 2 * c2) % 3;
        bool s_wins = false;
        
        if (S_mod == 0) {
            if (c0 > 0 && c0 % 2 == 1) s_wins = true;
        } else if (S_mod == 1) {
            if (c1 > 0 && c0 % 2 == 0) s_wins = true;
        } else {
            if (c2 > 0 && c0 % 2 == 0) s_wins = true;
        }
        
        cout << "Case " << t << ": " << (s_wins ? "S" : "T") << "\n";
    }
    
    return 0;
}
