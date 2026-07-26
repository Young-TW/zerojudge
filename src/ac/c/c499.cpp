#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string M, B;
    int T;
    while (cin >> M >> B >> T) {
        int n = static_cast<int>(M.size());
        int m = static_cast<int>(B.size());
        vector<int> prev(m + 1, 0), cur(m + 1, 0);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (M[i - 1] == B[j - 1])
                    cur[j] = prev[j - 1] + 1;
                else
                    cur[j] = max(prev[j], cur[j - 1]);
            }
            swap(prev, cur);
        }
        int L = prev[m];
        if (L >= T)
            cout << "kwa nini unaendesha\n";
        else
            cout << "sitini na tisa\n";
    }
    return 0;
}
