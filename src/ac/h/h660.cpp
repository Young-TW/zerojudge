#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long X, R, V;
    while (cin >> X >> R >> V) {
        int N;
        if (!(cin >> N)) break;
        for (int i = 0; i < N; ++i) {
            long long P, S;
            cin >> P >> S;
            long long left  = X - R;
            long long right = X + R;
            if (P < left || P > right) continue;          // not reachable
            if (S <= V) {
                X = P;                                     // catch
            } else {
                if (P >= X) X -= 15;                       // dodge left
                else        X += 15;                       // dodge right
            }
        }
        cout << X << '\n';
    }
    return 0;
}
