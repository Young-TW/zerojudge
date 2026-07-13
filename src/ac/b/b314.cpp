#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

const int MAXV = 1005 * 1005 + 5;
int parent[MAXV];
int sz[MAXV];
int M_val;

struct Op {
    int node;
    int parent_node;
    int size_parent_node;
};

int find(int i) {
    while (parent[i] != i) {
        i = parent[i];
    }
    return i;
}

bool union_nodes(int u, int v, Op& op) {
    int root_u = find(u);
    int root_v = find(v);
    if (root_u == root_v) return false;
    if (sz[root_u] < sz[root_v]) {
        swap(root_u, root_v);
    }
    op.node = root_v;
    op.parent_node = root_u;
    op.size_parent_node = sz[root_u];
    parent[root_v] = root_u;
    sz[root_u] += sz[root_v];
    return true;
}

void undo(const Op& op) {
    parent[op.node] = op.node;
    sz[op.parent_node] = op.size_parent_node;
}

inline int get_id(int i, int j) {
    return i * (M_val + 1) + j;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, T;
    while (cin >> N >> M_val >> T) {
        int V = (N + 1) * (M_val + 1) + 2;
        int TOP = (N + 1) * (M_val + 1);
        int BOTTOM = TOP + 1;

        for (int i = 0; i < V; ++i) {
            parent[i] = i;
            sz[i] = 1;
        }

        for (int j = 0; j <= M_val; ++j) {
            int u = get_id(0, j);
            int v = TOP;
            int root_u = find(u);
            int root_v = find(v);
            if (root_u != root_v) {
                if (sz[root_u] < sz[root_v]) swap(root_u, root_v);
                parent[root_v] = root_u;
                sz[root_u] += sz[root_v];
            }
        }

        for (int j = 0; j <= M_val; ++j) {
            int u = get_id(N, j);
            int v = BOTTOM;
            int root_u = find(u);
            int root_v = find(v);
            if (root_u != root_v) {
                if (sz[root_u] < sz[root_v]) swap(root_u, root_v);
                parent[root_v] = root_u;
                sz[root_u] += sz[root_v];
            }
        }

        for (int t = 0; t < T; ++t) {
            int x, y;
            cin >> x >> y;
            int p1 = get_id(x, y);
            int p2 = get_id(x + 1, y);
            int p3 = get_id(x, y + 1);
            int p4 = get_id(x + 1, y + 1);

            Op ops[3];
            bool merged[3] = {false, false, false};
            merged[0] = union_nodes(p1, p2, ops[0]);
            merged[1] = union_nodes(p1, p3, ops[1]);
            merged[2] = union_nodes(p1, p4, ops[2]);

            if (find(TOP) == find(BOTTOM)) {
                cout << ">_<\n";
                if (merged[2]) undo(ops[2]);
                if (merged[1]) undo(ops[1]);
                if (merged[0]) undo(ops[0]);
            } else {
                cout << "<(_ _)>\n";
            }
        }
    }

    return 0;
}
