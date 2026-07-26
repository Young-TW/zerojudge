#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    while (cin >> N) {
        multiset<long long> S;
        for (long long i = 0; i < N; ++i) {
            int op;
            cin >> op;
            if (op == 1) {                 // insert
                long long x;
                cin >> x;
                S.insert(x);
            } else {                       // delete interval
                long long l, r;
                cin >> l >> r;
                auto itL = S.lower_bound(l);
                auto itR = S.upper_bound(r);
                S.erase(itL, itR);
            }

            if (S.empty()) {
                cout << "0\n";
            } else {
                long long mn = *S.begin();
                long long mx = *S.rbegin();
                if (mn == mx) {
                    cout << "1 " << mn << "\n";
                } else {
                    cout << "2 " << mn << " " << mx << "\n";
                }
            }
        }
    }
    return 0;
}
