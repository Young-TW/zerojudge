#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        priority_queue<long long> pq;
        for (int i = 1; i <= N; i++) {
            long long a;
            cin >> a;
            long long b = a - (i - 1);
            if (b > 0) pq.push(b);
        }

        long long ans = 0;
        for (int d = 0; d < M && !pq.empty(); d++) {
            long long v = pq.top();
            if (v <= 0) break;
            pq.pop();
            ans += v;
            if (v - 1 > 0) pq.push(v - 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
