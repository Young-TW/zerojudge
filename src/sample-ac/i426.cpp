#include <iostream>

using namespace std;

const int MAXN = 100005;
int L[MAXN], R[MAXN];

void move_to_left(int x, int y) {
    R[L[x]] = R[x];
    L[R[x]] = L[x];
    L[x] = L[y];
    R[L[y]] = x;
    R[x] = y;
    L[y] = x;
}

void move_to_right(int x, int y) {
    R[L[x]] = R[x];
    L[R[x]] = L[x];
    R[x] = R[y];
    L[R[y]] = x;
    L[x] = y;
    R[y] = x;
}

void swap_nodes(int x, int y) {
    if (R[x] == y) {
        int lx = L[x];
        int ry = R[y];
        R[lx] = y;
        L[y] = lx;
        R[y] = x;
        L[x] = y;
        R[x] = ry;
        L[ry] = x;
    } else if (R[y] == x) {
        int ly = L[y];
        int rx = R[x];
        R[ly] = x;
        L[x] = ly;
        R[x] = y;
        L[y] = x;
        R[y] = rx;
        L[rx] = y;
    } else {
        int lx = L[x], rx = R[x];
        int ly = L[y], ry = R[y];
        R[lx] = y; L[y] = lx; R[y] = rx; L[rx] = y;
        R[ly] = x; L[x] = ly; R[x] = ry; L[ry] = x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    int case_num = 1;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            L[i] = i - 1;
            R[i] = i + 1;
        }
        L[1] = 0;
        R[n] = 0;
        L[0] = n;
        R[0] = 1;
        
        bool reversed = false;
        
        for (int i = 0; i < m; ++i) {
            int cmd;
            cin >> cmd;
            if (cmd == 4) {
                reversed = !reversed;
            } else {
                int x, y;
                cin >> x >> y;
                if (cmd == 1) {
                    if (reversed) {
                        move_to_right(x, y);
                    } else {
                        move_to_left(x, y);
                    }
                } else if (cmd == 2) {
                    if (reversed) {
                        move_to_left(x, y);
                    } else {
                        move_to_right(x, y);
                    }
                } else if (cmd == 3) {
                    swap_nodes(x, y);
                }
            }
        }
        
        long long ans = 0;
        if (!reversed) {
            int cur = R[0];
            int pos = 1;
            while (cur != 0) {
                if (pos % 2 == 1) ans += cur;
                cur = R[cur];
                pos++;
            }
        } else {
            int cur = L[0];
            int pos = 1;
            while (cur != 0) {
                if (pos % 2 == 1) ans += cur;
                cur = L[cur];
                pos++;
            }
        }
        
        cout << "Case " << case_num << ": " << ans << "\n";
        case_num++;
    }
    
    return 0;
}
