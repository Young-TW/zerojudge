#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    bool firstCase = true;
    while (cin >> n) {
        if (n == 0) break;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            --a[i];                     // to 0‑based
        }

        // ----- find cycles -----
        vector<int> cycle_id(n, -1), pos_in_cycle(n, -1);
        vector<vector<int>> cycles;
        for (int i = 0; i < n; ++i) {
            if (cycle_id[i] != -1) continue;
            vector<int> cur;
            int v = i;
            do {
                cycle_id[v] = (int)cycles.size();
                pos_in_cycle[v] = (int)cur.size();
                cur.push_back(v);
                v = a[v];
            } while (v != i);
            cycles.push_back(move(cur));
        }

        // ----- answer queries -----
        int k;
        while (cin >> k) {
            if (k == 0) break;          // end of this test case
            string line;
            getline(cin, line);         // rest of the line (may be empty)

            // remove the single separating space after k, if present
            if (!line.empty() && line[0] == ' ')
                line.erase(line.begin());

            // remove possible carriage return (for Windows line endings)
            if (!line.empty() && line.back() == '\r')
                line.pop_back();

            // pad or truncate to length n
            if ((int)line.size() < n)
                line.append(n - line.size(), ' ');
            else if ((int)line.size() > n)
                line.resize(n);

            string cipher(n, ' ');
            for (int i = 0; i < n; ++i) {
                int cid = cycle_id[i];
                int L = (int)cycles[cid].size();
                int step = k % L;
                int dest = cycles[cid][ (pos_in_cycle[i] + step) % L ];
                cipher[dest] = line[i];
            }
            cout << cipher << "\n";
        }

        // blank line after each test case
        cout << "\n";
    }
    return 0;
}
