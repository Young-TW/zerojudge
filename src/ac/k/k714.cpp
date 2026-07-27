#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N;
    // ZeroJudge may contain several test cases until EOF
    while (cin >> N) {
        vector<pair<long long,long long>> a; // (deadline, processing)
        a.reserve(N);
        for (long long i = 0; i < N; ++i) {
            long long p, t;
            cin >> p >> t;
            a.emplace_back(t, p);
        }
        sort(a.begin(), a.end(),
             [](const pair<long long,long long>& x,
                const pair<long long,long long>& y) {
                 return x.first < y.first;          // by deadline
             });
        
        priority_queue<long long> pq; // max‑heap of processing times
        long long cur = 0;            // total time of chosen orders
        
        for (auto &e : a) {
            long long deadline = e.first;
            long long proc = e.second;
            cur += proc;
            pq.push(proc);
            if (cur > deadline) {
                cur -= pq.top();
                pq.pop();
            }
        }
        cout << pq.size() << '\n';
    }
    return 0;
}
