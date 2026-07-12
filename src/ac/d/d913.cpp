#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int g[6][6];
    int m[6];
    
    while (cin >> g[0][0]) {
        for (int j = 1; j < 6; ++j) {
            cin >> g[0][j];
        }
        cin >> m[0];
        
        for (int i = 1; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                cin >> g[i][j];
            }
            cin >> m[i];
        }

        vector<int> p = {1, 2, 3, 4, 5, 6};
        do {
            bool ok = true;
            for (int i = 0; i < 6 && ok; ++i) {
                int cnt = 0;
                for (int j = 0; j < 6; ++j) {
                    if (p[j] == g[i][j]) {
                        cnt++;
                    }
                }
                if (cnt != m[i]) {
                    ok = false;
                }
            }
            if (ok) {
                for (int j = 0; j < 6; ++j) {
                    cout << p[j] << (j == 5 ? '\n' : ' ');
                }
                break;
            }
        } while (next_permutation(p.begin(), p.end()));
    }

    return 0;
}
