#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        long long cost = 0;
        priority_queue<long long> pq;
        const long long L = -1;
        for (int i = 1; i <= n; ++i) {
            long long a;
            cin >> a;
            long long d = a - i;
            long long x;
            if (d < L) {
                cost += L - d;
                x = L;
            } else {
                x = d;
            }
            pq.push(x);
            if (pq.top() > x) {
                cost += pq.top() - x;
                pq.pop();
                pq.push(x);
            }
        }
        cout << cost << '\n';
    }
    return 0;
}
