#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1050;
int vis[MAXN][MAXN];
int q_x[1200000];
int q_y[1200000];
int case_id = 0;

int get_gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int bfs(int x, int y, int z) {
    if (z == 0) return 0;
    if (z > x && z > y) return -1;
    if (z % get_gcd(x, y) != 0) return -1;
    
    ++case_id;
    int head = 0, tail = 0;
    q_x[tail] = 0; q_y[tail] = 0; tail++;
    vis[0][0] = case_id;
    int step = 0;
    
    while (head < tail) {
        int sz = tail - head;
        for (int i = 0; i < sz; ++i) {
            int a = q_x[head];
            int b = q_y[head];
            head++;
            
            if (a == z || b == z) {
                return step;
            }
            
            int na, nb;
            
            // 1. fill x
            na = x; nb = b;
            if (vis[na][nb] != case_id) { vis[na][nb] = case_id; q_x[tail] = na; q_y[tail] = nb; tail++; }
            
            // 2. fill y
            na = a; nb = y;
            if (vis[na][nb] != case_id) { vis[na][nb] = case_id; q_x[tail] = na; q_y[tail] = nb; tail++; }
            
            // 3. empty x
            na = 0; nb = b;
            if (vis[na][nb] != case_id) { vis[na][nb] = case_id; q_x[tail] = na; q_y[tail] = nb; tail++; }
            
            // 4. empty y
            na = a; nb = 0;
            if (vis[na][nb] != case_id) { vis[na][nb] = case_id; q_x[tail] = na; q_y[tail] = nb; tail++; }
            
            // 5. pour x to y
            int pour = min(a, y - b);
            na = a - pour; nb = b + pour;
            if (vis[na][nb] != case_id) { vis[na][nb] = case_id; q_x[tail] = na; q_y[tail] = nb; tail++; }
            
            // 6. pour y to x
            pour = min(b, x - a);
            na = a + pour; nb = b - pour;
            if (vis[na][nb] != case_id) { vis[na][nb] = case_id; q_x[tail] = na; q_y[tail] = nb; tail++; }
        }
        step++;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        while (n--) {
            int x, y, z;
            cin >> x >> y >> z;
            cout << bfs(x, y, z) << "\n";
        }
    }
    return 0;
}
