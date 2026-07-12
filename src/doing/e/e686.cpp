#include <iostream>
#include <algorithm>

using namespace std;

struct Order {
    int start, end, profit;
};

Order orders[30005];
long long dp[30005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int N;
            cin >> N;
            for (int i = 0; i < N; ++i) {
                int A, B, C;
                cin >> A >> B >> C;
                orders[i].start = A;
                orders[i].end = A + B - 1;
                orders[i].profit = C;
            }
            
            sort(orders, orders + N, [](const Order& a, const Order& b) {
                if (a.end != b.end) return a.end < b.end;
                return a.start < b.start;
            });
            
            dp[0] = 0;
            for (int i = 1; i <= N; ++i) {
                dp[i] = dp[i - 1];
                
                int L = 0, R = i - 1;
                int best = 0;
                while (L <= R) {
                    int mid = L + (R - L) / 2;
                    if (orders[mid].end < orders[i - 1].start) {
                        best = mid + 1;
                        L = mid + 1;
                    } else {
                        R = mid - 1;
                    }
                }
                
                dp[i] = max(dp[i], dp[best] + orders[i - 1].profit);
            }
            
            cout << "Case " << t << ": " << dp[N] << "\n";
        }
    }
    return 0;
}
