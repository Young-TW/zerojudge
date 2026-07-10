#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int N;
    while (cin >> N) {
        int m = N * (N - 1) / 2;
        vector<long long> s(m);
        for (int i = 0; i < m; i++) cin >> s[i];
        sort(s.begin(), s.end());

        bool found = false;
        vector<long long> best;

        // s[0]=a0+a1, s[1]=a0+a2, try each candidate for a1+a2
        for (int i = 2; i < m; i++) {
            long long sum01 = s[0], sum02 = s[1], sum12 = s[i];
            long long num = sum01 + sum02 - sum12;
            if (num % 2 != 0) continue;
            long long a0 = num / 2;
            long long a1 = sum01 - a0;
            long long a2 = sum02 - a0;

            multiset<long long> rest;
            for (int j = 0; j < m; j++) if (j != i) rest.insert(s[j]);

            vector<long long> ans;
            ans.push_back(a0);
            ans.push_back(a1);
            ans.push_back(a2);
            // remove a0+a1, a0+a2
            rest.erase(rest.find(a0 + a1));
            rest.erase(rest.find(a0 + a2));

            bool ok = true;
            for (int k = 3; k < N && ok; k++) {
                // smallest remaining = a0 + a[k]
                long long val = *rest.begin() - a0;
                // verify val + ans[j] for all existing j
                for (int j = 0; j < (int)ans.size(); j++) {
                    auto it = rest.find(val + ans[j]);
                    if (it == rest.end()) { ok = false; break; }
                    rest.erase(it);
                }
                if (ok) ans.push_back(val);
            }
            if (!ok) continue;

            sort(ans.begin(), ans.end());
            if (!found || ans > best) { best = ans; found = true; }
        }

        if (!found) cout << "Impossible\n";
        else {
            for (int i = 0; i < N; i++) cout << best[i] << " \n"[i == N - 1];
        }
    }
    return 0;
}
