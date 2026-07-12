#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m, c;
    int seq = 0;
    while (cin >> n >> m >> c) {
        if (n == 0 && m == 0 && c == 0) break;
        seq++;
        vector<int> dev(n + 1, 0);
        vector<char> on(n + 1, 0);
        for (int i = 1; i <= n; i++) cin >> dev[i];
        long long total = 0;
        long long maxP = 0;
        bool blown = false;
        for (int i = 0; i < m; i++) {
            int k;
            cin >> k;
            if (on[k]) {
                total -= dev[k];
                on[k] = 0;
            } else {
                total += dev[k];
                on[k] = 1;
                if (total > maxP) maxP = total;
                if (total > c) blown = true;
            }
        }
        cout << "Sequence " << seq << "\n";
        if (blown) {
            cout << "Fuse was blown.\n";
        } else {
            cout << "Fuse was not blown.\n";
            cout << "Maximal power consumption was " << maxP << " amperes.\n";
        }
        cout << "\n";
    }
    return 0;
}
