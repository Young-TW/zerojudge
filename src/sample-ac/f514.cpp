#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string S, T;
    while (cin >> S >> T) {
        int N = S.length();
        set<int> pos[26];
        
        for (int i = 0; i < N; ++i) {
            pos[S[i] - 'a'].insert(i + 1);
        }
        
        int curr = 1;
        bool first = true;
        
        for (char c : T) {
            if (!first) {
                cout << " ";
            }
            first = false;
            
            int idx = c - 'a';
            if (idx < 0 || idx >= 26) {
                cout << 'X';
                continue;
            }
            
            auto it = pos[idx].lower_bound(curr);
            if (it == pos[idx].end()) {
                it = pos[idx].begin();
            }
            
            if (it == pos[idx].end()) {
                cout << 'X';
            } else {
                int p = *it;
                cout << p;
                pos[idx].erase(it);
                curr = p % N + 1;
            }
        }
        cout << "\n";
    }
    
    return 0;
}
