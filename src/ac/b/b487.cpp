#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100005;

int ch[MAXN][2];
int fa[MAXN];
int sz[MAXN];

bool isRoot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}

void pushup(int x) {
    sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
}

void rotate(int x) {
    int y = fa[x], z = fa[y];
    int dir = (ch[y][1] == x);
    int w = ch[x][dir ^ 1];
    if (!isRoot(y)) ch[z][ch[z][1] == y] = x;
    fa[x] = z;
    ch[x][dir ^ 1] = y;
    fa[y] = x;
    ch[y][dir] = w;
    if (w) fa[w] = y;
    pushup(y);
    pushup(x);
}

void splay(int x) {
    while (!isRoot(x)) {
        int y = fa[x], z = fa[y];
        if (!isRoot(y)) {
            if ((ch[y][0] == x) ^ (ch[z][0] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}

void access(int x) {
    int last = 0;
    for (int u = x; u; u = fa[u]) {
        splay(u);
        ch[u][1] = last;
        pushup(u);
        last = u;
    }
    splay(x);
}

int findRoot(int x) {
    access(x);
    while (ch[x][0]) x = ch[x][0];
    splay(x);
    return x;
}

void link(int x, int y) {
    access(x);
    fa[x] = y;
}

void cut(int x) {
    access(x);
    if (ch[x][0]) {
        fa[ch[x][0]] = 0;
        ch[x][0] = 0;
        pushup(x);
    }
}

int lca(int x, int y) {
    if (x == y) return x;
    access(x);
    int last = 0;
    for (int u = y; u; u = fa[u]) {
        splay(u);
        if (!fa[u]) return u;
        last = u;
    }
    return last;
}

int getDepth(int x) {
    access(x);
    return sz[ch[x][0]];
}

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M) {
        for (int i = 1; i <= N; i++) {
            ch[i][0] = ch[i][1] = fa[i] = 0;
            sz[i] = 1;
        }
        
        string op;
        int x, y;
        for (int i = 0; i < M; i++) {
            cin >> op >> x >> y;
            if (op == "news") {
                cut(x);
                link(x, y);
            } else if (op == "sim") {
                if (findRoot(x) != findRoot(y)) {
                    cout << -1 << '\n';
                } else {
                    int l = lca(x, y);
                    int depth_l = getDepth(l);
                    int depth_x = getDepth(x);
                    int depth_y = getDepth(y);
                    int num = 2 * (depth_l + 1);
                    int den = depth_x + depth_y + 2;
                    int g = gcd(num, den);
                    num /= g;
                    den /= g;
                    cout << num << '/' << den << '\n';
                }
            }
        }
    }
    return 0;
}
