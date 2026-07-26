#include <bits/stdc++.h>
using namespace std;

struct StateInfo {
    int prev;      // index of predecessor state, -1 for start
    unsigned char used; // factor that was added to reach this state
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unsigned long long P;
    while (cin >> P) {
        // factorise P into primes 2,3,5,7
        int need[4] = {0, 0, 0, 0}; // exponents of 2,3,5,7
        unsigned long long tmp = P;
        const int primes[4] = {2, 3, 5, 7};
        for (int i = 0; i < 4; ++i) {
            while (tmp % primes[i] == 0) {
                tmp /= primes[i];
                ++need[i];
            }
        }
        if (tmp != 1) {               // contains other prime factor
            cout << -1 << '\n';
            continue;
        }

        // dimensions for encoding
        int dim2 = need[0] + 1;
        int dim3 = need[1] + 1;
        int dim5 = need[2] + 1;
        int dim7 = need[3] + 1;
        int totalStates = dim2 * dim3 * dim5 * dim7;

        auto encode = [&](int e2, int e3, int e5, int e7) -> int {
            return ((e2 * dim3 + e3) * dim5 + e5) * dim7 + e7;
        };
        auto decode = [&](int idx, int &e2, int &e3, int &e5, int &e7) {
            e7 = idx % dim7; idx /= dim7;
            e5 = idx % dim5; idx /= dim5;
            e3 = idx % dim3; idx /= dim3;
            e2 = idx;
        };

        // factor data
        const int factorVal[8] = {2,3,4,5,6,7,8,9};
        const int factorExp[8][4] = {
            {1,0,0,0}, //2
            {0,1,0,0}, //3
            {2,0,0,0}, //4
            {0,0,1,0}, //5
            {1,1,0,0}, //6
            {0,0,0,1}, //7
            {3,0,0,0}, //8
            {0,2,0,0}  //9
        };

        vector<char> visited(totalStates, 0);
        vector<StateInfo> info(totalStates);
        queue<int> q;

        int start = encode(0,0,0,0);
        visited[start] = 1;
        info[start] = {-1, 0};
        q.push(start);

        int target = encode(need[0], need[1], need[2], need[3]);

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            if (cur == target) break; // already optimal, can stop early
            int e2, e3, e5, e7;
            decode(cur, e2, e3, e5, e7);
            for (int i = 0; i < 8; ++i) {          // factors 2..9
                int ne2 = e2 + factorExp[i][0];
                int ne3 = e3 + factorExp[i][1];
                int ne5 = e5 + factorExp[i][2];
                int ne7 = e7 + factorExp[i][3];
                if (ne2 > need[0] || ne3 > need[1] ||
                    ne5 > need[2] || ne7 > need[3]) continue;
                int nxt = encode(ne2, ne3, ne5, ne7);
                if (!visited[nxt]) {
                    visited[nxt] = 1;
                    info[nxt] = {cur, (unsigned char)factorVal[i]};
                    q.push(nxt);
                }
            }
        }

        if (!visited[target]) {
            cout << -1 << '\n';
            continue;
        }

        // reconstruct
        vector<int> ans;
        int cur = target;
        while (cur != start) {
            ans.push_back(info[cur].used);
            cur = info[cur].prev;
        }
        sort(ans.begin(), ans.end());
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
