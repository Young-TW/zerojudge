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
        cin.ignore();
        
        cout << "Case " << t << ":\n";
        
        for (int i = 0; i < N; ++i) {
            string s;
            getline(cin, s);
            
            string ans;
            bool prev_space = false;
            
            for (char c : s) {
                if (c == ' ') {
                    if (!prev_space) {
                        ans += c;
                    }
                    prev_space = true;
                } else {
                    ans += c;
                    prev_space = false;
                }
            }
            
            cout << ans << "\n";
        }
    }
    
    return 0;
}
