#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        while (n--) {
            vector<long long> a(m), b(m);
            for (int i = 0; i < m; ++i) {
                cin >> a[i];
            }
            for (int i = 0; i < m; ++i) {
                cin >> b[i];
            }
            
            int i = 0, j = 0, cnt = 0;
            while (i < m && j < m) {
                if (a[i] == b[j]) {
                    cnt++;
                    i++;
                    j++;
                } else if (a[i] < b[j]) {
                    i++;
                } else {
                    j++;
                }
            }
            cout << cnt << "\n";
        }
    }
    
    return 0;
}
