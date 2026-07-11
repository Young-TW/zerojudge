#include <bits/stdc++.h>
using namespace std;

static int parentv[200005];
static int dsu[200005];
static int sz[200005];

int find(int x) {
    while (dsu[x] != x) {
        dsu[x] = dsu[dsu[x]];
        x = dsu[x];
    }
    return x;
}

void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
    dsu[b] = a;
    sz[a] += sz[b];
}

int main() {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;
    for (int i = 2; i <= N; i++) {
        scanf("%d", &parentv[i]);
    }
    int total = (N - 1) + Q;
    vector<array<int,3>> ops;
    ops.reserve(total);
    for (int i = 0; i < total; i++) {
        int x;
        scanf("%d", &x);
        if (x == 0) {
            int b;
            scanf("%d", &b);
            ops.push_back({0, b, 0});
        } else {
            int c, d;
            scanf("%d %d", &c, &d);
            ops.push_back({1, c, d});
        }
    }
    for (int i = 1; i <= N; i++) { dsu[i] = i; sz[i] = 1; }
    
    vector<const char*> answers;
    answers.reserve(Q);
    for (int i = total - 1; i >= 0; i--) {
        if (ops[i][0] == 0) {
            int b = ops[i][1];
            unite(b, parentv[b]);
        } else {
            int c = ops[i][1], d = ops[i][2];
            answers.push_back(find(c) == find(d) ? "YES" : "NO");
        }
    }
    reverse(answers.begin(), answers.end());
    for (auto s : answers) printf("%s\n", s);
    return 0;
}
