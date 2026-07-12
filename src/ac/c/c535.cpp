#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

const int MAXQ = 200005;

struct Node {
    int x, y;
    Node *l, *r;
    int xmin, xmax, ymin, ymax;
    int size;
};

Node pool[MAXQ];
int pool_cnt = 0;

Node *newNode(int x, int y) {
    Node *p = &pool[pool_cnt++];
    p->x = x;
    p->y = y;
    p->l = p->r = nullptr;
    p->xmin = p->xmax = x;
    p->ymin = p->ymax = y;
    p->size = 1;
    return p;
}

int size(Node *u) {
    return u ? u->size : 0;
}

void pushup(Node *u) {
    u->size = 1;
    u->xmin = u->xmax = u->x;
    u->ymin = u->ymax = u->y;
    if (u->l) {
        u->size += u->l->size;
        u->xmin = min(u->xmin, u->l->xmin);
        u->xmax = max(u->xmax, u->l->xmax);
        u->ymin = min(u->ymin, u->l->ymin);
        u->ymax = max(u->ymax, u->l->ymax);
    }
    if (u->r) {
        u->size += u->r->size;
        u->xmin = min(u->xmin, u->r->xmin);
        u->xmax = max(u->xmax, u->r->xmax);
        u->ymin = min(u->ymin, u->r->ymin);
        u->ymax = max(u->ymax, u->r->ymax);
    }
}

vector<Node*> nodes;

void rebuild(Node *u) {
    if (!u) return;
    rebuild(u->l);
    nodes.push_back(u);
    rebuild(u->r);
}

bool cmp0(const Node *a, const Node *b) { return a->x < b->x; }
bool cmp1(const Node *a, const Node *b) { return a->y < b->y; }

Node *build(int l, int r, int d) {
    if (l >= r) return nullptr;
    int mid = (l + r) / 2;
    if (d == 0) nth_element(nodes.begin() + l, nodes.begin() + mid, nodes.begin() + r, cmp0);
    else nth_element(nodes.begin() + l, nodes.begin() + mid, nodes.begin() + r, cmp1);
    Node *u = nodes[mid];
    u->l = build(l, mid, (d + 1) % 2);
    u->r = build(mid + 1, r, (d + 1) % 2);
    pushup(u);
    return u;
}

const int alpha = 3;

Node *insert(Node *u, Node *p, int d) {
    if (!u) {
        pushup(p);
        return p;
    }
    if (d == 0) {
        if (p->x < u->x) u->l = insert(u->l, p, 1);
        else u->r = insert(u->r, p, 1);
    } else {
        if (p->y < u->y) u->l = insert(u->l, p, 0);
        else u->r = insert(u->r, p, 0);
    }
    pushup(u);
    if (max(size(u->l), size(u->r)) * 4 > u->size * alpha) {
        nodes.clear();
        rebuild(u);
        u = build(0, nodes.size(), 0);
    }
    return u;
}

inline int get_dist(Node *u, int x, int y) {
    if (!u) return 1e9;
    int dx = 0;
    if (x < u->xmin) dx = u->xmin - x;
    else if (x > u->xmax) dx = x - u->xmax;
    int dy = 0;
    if (y < u->ymin) dy = u->ymin - y;
    else if (y > u->ymax) dy = y - u->ymax;
    return dx + dy;
}

int ans;

void query(Node *u, int x, int y) {
    if (!u) return;
    int d = abs(x - u->x) + abs(y - u->y);
    if (d < ans) ans = d;
    int dl = get_dist(u->l, x, y);
    int dr = get_dist(u->r, x, y);
    if (dl < dr) {
        if (dl < ans) query(u->l, x, y);
        if (dr < ans) query(u->r, x, y);
    } else {
        if (dr < ans) query(u->r, x, y);
        if (dl < ans) query(u->l, x, y);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    if (!(cin >> Q)) return 0;
    Node *root = nullptr;
    int last_ans = 0;
    while (Q--) {
        int c, x, y;
        cin >> c >> x >> y;
        x = (last_ans + x) % 100000000 + 1;
        y = (last_ans + y) % 100000000 + 1;
        if (c == 1) {
            Node *p = newNode(x, y);
            root = insert(root, p, 0);
        } else {
            if (!root) {
                cout << 0 << '\n';
                last_ans = 0;
            } else {
                ans = 1e9;
                query(root, x, y);
                cout << ans << '\n';
                last_ans = ans;
            }
        }
    }
    return 0;
}
