#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long p;
    int n;
    while (cin >> p) {
        if (!(cin >> n)) break;
        vector<int> c(n + 2);
        vector<long long> d(n + 2), pref(n + 2);
        for (int i = 1; i <= n; ++i) {
            cin >> c[i] >> d[i];
            pref[i] = pref[i - 1] + d[i];
        }
        long long total = pref[n];

        // next cheaper station
        vector<int> nxt(n + 2, n + 1);
        vector<int> st;
        st.reserve(n);
        for (int i = n; i >= 1; --i) {
            while (!st.empty() && c[st.back()] >= c[i]) st.pop_back();
            nxt[i] = st.empty() ? n + 1 : st.back();
            st.push_back(i);
        }

        long long fuel = 0, cost = 0;
        for (int i = 1; i <= n; ++i) {
            long long distCheaper = (nxt[i] == n + 1)
                ? total - pref[i - 1]
                : pref[nxt[i] - 1] - pref[i - 1];
            long long need = (distCheaper <= p)
                ? distCheaper
                : min(p, total - pref[i - 1]);
            if (need > fuel) {
                long long buy = need - fuel;
                cost += buy * c[i];
                fuel = need;
            }
            fuel -= d[i];
        }
        cout << cost << '\n';
    }
    return 0;
}
