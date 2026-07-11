#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            int a[10][10];
            memset(a, 0, sizeof(a));
            
            for (int i = 1; i <= 9; i += 2) {
                for (int j = 1; j <= (i + 1) / 2; j++) {
                    cin >> a[i][2 * j - 1];
                }
            }
            
            for (int j = 1; j <= 4; j++) {
                a[9][2 * j] = (a[7][2 * j - 1] - a[9][2 * j - 1] - a[9][2 * j + 1]) / 2;
            }
            
            for (int i = 8; i >= 1; i--) {
                for (int j = 1; j <= i; j++) {
                    a[i][j] = a[i + 1][j] + a[i + 1][j + 1];
                }
            }
            
            for (int i = 1; i <= 9; i++) {
                for (int j = 1; j <= i; j++) {
                    cout << a[i][j];
                    if (j < i) cout << " ";
                }
                cout << "\n";
            }
        }
    }
    
    return 0;
}
