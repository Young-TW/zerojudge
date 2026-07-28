#include <bits/stdc++.h>
using namespace std;

bool isNumber(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit((unsigned char)c)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string tok;
    while (cin >> tok) {
        if (isNumber(tok)) {
            int n = stoi(tok);
            for (int i = 0; i < n; i++) {
                long long X;
                int k;
                cin >> X >> k;
                int M = k + 1;
                int r = (int)(X % M);
                int best = INT_MAX;
                for (int t = 1; t < M; t += 2) {
                    int cand = ((t - r) % M + M) % M;
                    if (cand == 0) cand = M;
                    if (cand < best) best = cand;
                }
                if (best > 10000) best = 0;
                cout << best << "\n";
            }
        } else {
            cout << tok << "\n";
        }
    }
    return 0;
}
