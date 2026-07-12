#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<long long> money(N);
        long long total_money = 0;
        long long max_money = 0;
        for (int i = 0; i < N; ++i) {
            cin >> money[i];
            total_money += money[i];
            if (money[i] > max_money) {
                max_money = money[i];
            }
        }
        
        vector<long long> dishes(M);
        long long total_dishes = 0;
        for (int i = 0; i < M; ++i) {
            cin >> dishes[i];
            total_dishes += dishes[i];
        }
        
        if (total_money < total_dishes) {
            cout << "Oh My God\n";
            continue;
        }
        
        priority_queue<long long> pq;
        for (int i = 0; i < N; ++i) {
            pq.push(money[i]);
        }
        
        for (int i = 0; i < M; ++i) {
            long long cost = dishes[i];
            while (cost > 0) {
                long long top = pq.top();
                pq.pop();
                if (top >= cost) {
                    top -= cost;
                    cost = 0;
                    pq.push(top);
                } else {
                    cost -= top;
                }
            }
        }
        
        cout << max_money << " " << pq.top() << "\n";
    }
    
    return 0;
}
