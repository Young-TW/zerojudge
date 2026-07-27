#include <bits/stdc++.h>
using namespace std;

struct Prog {
    long long t;   // arrival time
    int rem;       // remaining execution time
    int id;        // 1‑based identifier
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K, X;
    while (cin >> N >> K >> X) {
        vector<Prog> prog(N + 1);               // 1‑based
        for (int i = 1; i <= N; ++i) {
            long long ti; int ci;
            cin >> ti >> ci;
            prog[i] = {ti, ci, i};
        }

        // order of arrivals (stable)
        vector<int> order(N);
        for (int i = 0; i < N; ++i) order[i] = i + 1;
        stable_sort(order.begin(), order.end(),
                    [&](int a, int b){ return prog[a].t < prog[b].t; });

        queue<int> q;
        long long cur = 0;
        int idx = 0;                     // next not yet inserted program in 'order'

        long long answer = -1;

        while (true) {
            // no ready program -> jump to next arrival
            if (q.empty()) {
                if (idx >= N) break;    // should not happen before X finishes
                cur = max(cur, prog[order[idx]].t);
                while (idx < N && prog[order[idx]].t == cur) {
                    q.push(order[idx]);
                    ++idx;
                }
                continue;
            }

            int id = q.front(); q.pop();
            Prog &p = prog[id];

            int run = min(K, p.rem);
            long long finish = cur + run;

            // arrivals strictly before finish
            while (idx < N && prog[order[idx]].t < finish) {
                q.push(order[idx]);
                ++idx;
            }

            // execute the slice
            p.rem -= run;
            cur = finish;

            if (p.rem == 0) {                 // program finished
                if (id == X) {
                    answer = cur - prog[id].t;
                    break;
                }
                // arrivals exactly at this moment
                while (idx < N && prog[order[idx]].t == cur) {
                    q.push(order[idx]);
                    ++idx;
                }
            } else {                           // quantum expired, move to tail
                q.push(id);
                while (idx < N && prog[order[idx]].t == cur) {
                    q.push(order[idx]);
                    ++idx;
                }
            }
        }

        cout << answer << '\n';
    }
    return 0;
}
