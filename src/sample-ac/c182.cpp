#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<int> a(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            cin >> a[i];
        }
        
        int ans = 0;
        for (int i = 1; i <= N; ++i) {
            if (a[i] == 1) {
                ans++;
                for (int j = i; j <= N; j += i) {
                    a[j] ^= 1;
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
