#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        while (n--) {
            int k, w;
            cin >> k >> w;
            string prev, curr;
            cin >> prev;
            int ans = k;
            for (int i = 1; i < w; ++i) {
                cin >> curr;
                int maxL = 0;
                for (int l = k; l >= 1; --l) {
                    if (prev.compare(k - l, l, curr, 0, l) == 0) {
                        maxL = l;
                        break;
                    }
                }
                ans += k - maxL;
                prev = curr;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
