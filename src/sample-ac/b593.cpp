#include <iostream>
#include <string>

using namespace std;

long long C[30][30];

void init() {
    for (int i = 0; i < 30; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    init();
    string w;
    
    while (cin >> w && w != "0") {
        int L = w.length();
        bool valid = true;
        
        for (int i = 0; i < L - 1; ++i) {
            if (w[i] >= w[i+1]) {
                valid = false;
                break;
            }
        }
        
        if (!valid) {
            cout << 0 << "\n";
            continue;
        }
        
        long long ans = 0;
        for (int i = 1; i < L; ++i) {
            ans += C[26][i];
        }
        
        for (int i = 0; i < L; ++i) {
            char start = (i == 0) ? 'a' : w[i-1] + 1;
            for (char c = start; c < w[i]; ++c) {
                ans += C[26 - (c - 'a' + 1)][L - i - 1];
            }
        }
        
        ans += 1;
        cout << ans << "\n";
    }
    
    return 0;
}
