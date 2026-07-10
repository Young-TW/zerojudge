#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int n, m;
        cin >> n >> m;

        priority_queue<int> pq;

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            pq.push(x);
        }

        cout << "Case " << t << ":\n";

        for (int i = 0; i < m; i++) {
            int op;
            cin >> op;
            if (op == 1) {
                int x;
                cin >> x;
                pq.push(x);
            } else {
                if (pq.empty()) {
                    cout << "It's empty!\n";
                } else {
                    cout << "Max: " << pq.top() << "\n";
                    pq.pop();
                }
            }
        }

        if (pq.empty()) {
            cout << "It's empty!\n";
        } else {
            while (!pq.empty()) {
                cout << pq.top() << " ";
                pq.pop();
            }
            cout << "\n";
        }
    }

    return 0;
}
