#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int N, Q;
long long bit[260][260];
long long val[260][260];

void update(int x, int y, long long delta) {
    for (int i = x; i <= N; i += i & (-i))
        for (int j = y; j <= N; j += j & (-j))
            bit[i][j] += delta;
}

long long query(int x, int y) {
    long long res = 0;
    for (int i = x; i > 0; i -= i & (-i))
        for (int j = y; j > 0; j -= j & (-j))
            res += bit[i][j];
    return res;
}

long long query_range(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> N >> Q) {
        memset(bit, 0, sizeof(bit));
        memset(val, 0, sizeof(val));
        
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                long long m;
                cin >> m;
                val[i][j] = m;
                update(i, j, m);
            }
        }
        
        for (int k = 0; k < Q; ++k) {
            int op;
            cin >> op;
            if (op == 1) {
                int x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                int x_min = min(x1, x2), x_max = max(x1, x2);
                int y_min = min(y1, y2), y_max = max(y1, y2);
                cout << query_range(x_min, y_min, x_max, y_max) << "\n";
            } else if (op == 2) {
                int x1, y1;
                long long v;
                cin >> x1 >> y1 >> v;
                long long delta = v - val[x1][y1];
                val[x1][y1] = v;
                update(x1, y1, delta);
            }
        }
    }
    
    return 0;
}
