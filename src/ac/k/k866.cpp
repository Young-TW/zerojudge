#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N, M;
    while (cin >> N >> M) {
        priority_queue<long double> pq;
        for (long long i = 0; i < N; ++i) {
            long double w;
            cin >> w;
            pq.push(w);
        }
        for (long long i = 0; i < M; ++i) {
            long double w = pq.top(); pq.pop();
            long double half = w / 2.0L;
            pq.push(half);
            pq.push(half);
        }
        long double maxw = pq.top();
        const long double eps = 1e-12L;          // guard against 4.000000000001
        long long answer = (long long)ceil(maxw - eps);
        if (answer < 1) answer = 1;              // safety, though never needed
        cout << answer << '\n';
    }
    return 0;
}
