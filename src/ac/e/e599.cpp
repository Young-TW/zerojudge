#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        for (int g = 0; g < n; g++) {
            int card[5][5];
            bool marked[5][5];
            memset(marked, false, sizeof(marked));
            int posR[76], posC[76];
            memset(posR, -1, sizeof(posR));
            memset(posC, -1, sizeof(posC));
            
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (i == 2 && j == 2) {
                        card[i][j] = 0;
                        marked[i][j] = true;
                    } else {
                        int x; 
                        if (cin >> x) {
                            card[i][j] = x;
                            posR[x] = i;
                            posC[x] = j;
                        }
                    }
                }
            }
            
            int ans = 75;
            for (int k = 1; k <= 75; k++) {
                int num; 
                cin >> num;
                if (ans == 75) {
                    if (posR[num] != -1) {
                        marked[posR[num]][posC[num]] = true;
                    }
                    bool bingo = false;
                    for (int i = 0; i < 5 && !bingo; i++) {
                        bool ok = true;
                        for (int j = 0; j < 5; j++) if (!marked[i][j]) ok = false;
                        if (ok) bingo = true;
                    }
                    for (int j = 0; j < 5 && !bingo; j++) {
                        bool ok = true;
                        for (int i = 0; i < 5; i++) if (!marked[i][j]) ok = false;
                        if (ok) bingo = true;
                    }
                    bool d1 = true, d2 = true;
                    for (int i = 0; i < 5; i++) {
                        if (!marked[i][i]) d1 = false;
                        if (!marked[i][4-i]) d2 = false;
                    }
                    if (d1 || d2) bingo = true;
                    
                    if (bingo) ans = k;
                }
            }
            cout << "BINGO after " << ans << " numbers announced\n";
        }
    }
    return 0;
}
