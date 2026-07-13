#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    if (!(cin >> N)) return 0;
    
    for (int case_num = 1; case_num <= N; ++case_num) {
        int m, k;
        if (!(cin >> m >> k)) break;
        
        vector<bitset<305>> out(m);
        for (int i = 0; i < k; ++i) {
            int x, y;
            cin >> x >> y;
            if (x >= 0 && x < m && y >= 0 && y < m) {
                out[x][y] = 1;
            }
        }
        
        bool valid = true;
        for (int i = 0; i < m && valid; ++i) {
            for (int j = i + 1; j < m && valid; ++j) {
                if ((out[i] & out[j]).any()) {
                    if (out[i] != out[j]) {
                        valid = false;
                    }
                }
            }
        }
        
        cout << "Case #" << case_num << ": " << (valid ? "Yes" : "No") << "\n";
    }
    
    return 0;
}
