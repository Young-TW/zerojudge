#include <bits/stdc++.h>
using namespace std;

struct Animal {
    long long L; // limit
    long long H; // height
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        vector<Animal> a(N);
        for (int i = 0; i < N; ++i) {
            long long H, L;
            cin >> H >> L;
            a[i] = {L, H};
        }
        sort(a.begin(), a.end(), [](const Animal& x, const Animal& y) {
            return x.L < y.L;
        });
        
        priority_queue<long long> pq; // max‑heap of H
        long long sum = 0;            // total height of selected animals
        
        for (const auto& cur : a) {
            if (sum <= cur.L) {
                // we can keep it
                pq.push(cur.H);
                sum += cur.H;
            } else if (!pq.empty() && pq.top() > cur.H) {
                // replace the largest H by a smaller one
                sum -= pq.top();
                pq.pop();
                pq.push(cur.H);
                sum += cur.H;
            }
            // otherwise skip this animal
        }
        cout << pq.size() << '\n';
    }
    return 0;
}
