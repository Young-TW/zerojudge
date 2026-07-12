#include <iostream>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int n;
            cin >> n;
            map<int, int> cnt;
            int max_cnt = 0;
            for (int i = 0; i < n; ++i) {
                int x;
                cin >> x;
                cnt[x]++;
                if (cnt[x] > max_cnt) {
                    max_cnt = cnt[x];
                }
            }
            if (max_cnt <= n / 2) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    return 0;
}
