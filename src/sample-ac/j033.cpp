#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int n, P, Q;
            cin >> n >> P >> Q;
            vector<int> w(n);
            for (int i = 0; i < n; ++i) {
                cin >> w[i];
            }
            sort(w.begin(), w.end());
            int count = 0;
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                if (count < P && sum + w[i] <= Q) {
                    count++;
                    sum += w[i];
                } else {
                    break;
                }
            }
            cout << "Case " << t << ": " << count << "\n";
        }
    }
    return 0;
}
