#include <iostream>

using namespace std;

const int MAXN = 500005;
int L[MAXN], R[MAXN];

void remove_node(int x) {
    L[R[x]] = L[x];
    R[L[x]] = R[x];
}

void insert_right(int x, int y) {
    R[x] = R[y];
    L[x] = y;
    L[R[y]] = x;
    R[y] = x;
}

void insert_left(int x, int y) {
    L[x] = L[y];
    R[x] = y;
    R[L[y]] = x;
    L[y] = x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, q;
    while (cin >> n >> m >> q) {
        for (int i = 0; i < n; ++i) {
            L[i] = (i - 1 + n) % n;
            R[i] = (i + 1) % n;
        }
        
        for (int i = 0; i < m; ++i) {
            char op;
            int a, b;
            cin >> op >> a >> b;
            if (a == b) continue;
            remove_node(a);
            if (op == 'F') {
                insert_right(a, b);
            } else {
                insert_left(a, b);
            }
        }
        
        for (int i = 0; i < q; ++i) {
            int c;
            cin >> c;
            if (i > 0) cout << " ";
            cout << L[c] << " " << R[c];
        }
        cout << "\n";
    }
    
    return 0;
}
