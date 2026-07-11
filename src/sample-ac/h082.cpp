#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    while (cin >> n >> m) {
        vector<long long> S(n+1), T(n+1);
        for (int i = 1; i <= n; i++) cin >> S[i];
        for (int i = 1; i <= n; i++) cin >> T[i];
        vector<int> order(n);
        for (int i = 0; i < n; i++) cin >> order[i];
        
        vector<int> loss(n+1, 0);
        
        while ((int)order.size() > 1) {
            vector<int> winners, losers;
            int sz = (int)order.size();
            for (int i = 0; i + 1 < sz; i += 2) {
                int p1 = order[i], p2 = order[i+1];
                long long a = S[p1], b = T[p1], c = S[p2], d = T[p2];
                long long ab = a * b, cd = c * d;
                if (ab >= cd) {
                    S[p1] = a + cd / (2 * b);
                    T[p1] = b + cd / (2 * a);
                    S[p2] = c + c / 2;
                    T[p2] = d + d / 2;
                    winners.push_back(p1);
                    loss[p2]++;
                    losers.push_back(p2);
                } else {
                    S[p2] = c + ab / (2 * d);
                    T[p2] = d + ab / (2 * c);
                    S[p1] = a + a / 2;
                    T[p1] = b + b / 2;
                    winners.push_back(p2);
                    loss[p1]++;
                    losers.push_back(p1);
                }
            }
            if (sz % 2 == 1) {
                winners.push_back(order[sz - 1]);
            }
            vector<int> newOrder;
            newOrder.reserve(winners.size() + losers.size());
            for (int p : winners) newOrder.push_back(p);
            for (int p : losers) {
                if (loss[p] < m) newOrder.push_back(p);
            }
            order.swap(newOrder);
        }
        
        cout << order[0] << "\n";
    }
    return 0;
}
