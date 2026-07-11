#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int MAXN = 30005;
const int LOGN = 16;

int N, M;
int enemies[MAXN];
int parent[MAXN];
int depth[MAXN];
int up[MAXN][LOGN];
long long subtree_sum[MAXN];
vector<int> adj[MAXN];
bool active_edge[MAXN]; // To track if an edge to parent is active, though logic relies on connectivity checks

// DSU for connectivity components
int dsu_parent[MAXN];
int find_set(int v) {
    if (v == dsu_parent[v]) return v;
    return dsu_parent[v] = find_set(dsu_parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        dsu_parent[b] = a;
    }
}

// LCA and Tree Traversal helpers
void dfs(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    up[u][0] = p;
    for (int i = 1; i < LOGN; i++) {
        if (up[u][i-1] != -1)
            up[u][i] = up[up[u][i-1]][i-1];
        else
            up[u][i] = -1;
    }
    
    long long current_sum = enemies[u];
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
        // Only add child's sum if the edge (u, v) is currently active?
        // No, the problem says "initially all closed". 
        // The tree structure exists physically, but connectivity depends on active edges.
        // However, the query asks for the sum of the connected component containing u.
        // Since the edges form a tree when active, the component is a subtree rooted at some ancestor relative to u?
        // Actually, since it's a tree, removing edges splits it into forests.
        // The component containing u is simply the set of nodes reachable from u via active edges.
        // Calculating this dynamically with updates is hard if we just sum subtrees.
        // BUT: N=30000, M=100000. O(N) per query is too slow (3e9 ops).
        // We need a faster way.
        
        // Wait, re-reading the problem carefully.
        // "Tree shelter", "Open/Close channels".
        // If edges are closed, the graph becomes a forest.
        // Query: Sum of enemies in the connected component of u.
        // Updates: Link, Cut, Point Update.
        // This is a classic Dynamic Tree problem. Link-Cut Tree (LCT) or Euler Tour Tree (ETT).
        // Given constraints and C++14, implementing a full LCT might be heavy but feasible.
        // Alternatively, since the underlying structure is always a tree (when all edges open), 
        // and we only activate/deactivate edges of this static tree...
        // Actually, the operations say "Open channel between u and v" and "Close".
        // It guarantees "maintaining tree condition". This implies we never create cycles.
        // So we are maintaining a forest which is a subgraph of the original tree?
        // Or does "Open 1 2" mean adding an edge that might not have been in the initial input list?
        // Input format: First line N, M. Then N integers (enemies). THEN M operations.
        // The operations define the edges. The initial state has NO edges.
        // "Guaranteed ... maintaining tree condition".
        // This means the set of ACTIVE edges always forms a forest.
        // When we add an edge, it connects two previously disconnected components.
        // Since the final result (if all opened?) isn't necessarily a single tree, but the problem says "In a tree shelter...".
        // Usually this implies the potential edges form a tree structure, or the sequence of operations maintains a forest.
        // If the active edges form a forest, and we need component sums with link/cut/update.
        // Link-Cut Tree is the standard solution for O(log N) per op.
        
        // Let's re-evaluate complexity. N=30000. Maybe O(sqrt(N)) or heavy-light decomposition with some trick?
        // But edges are dynamic. HLD doesn't support cut/link easily without rebuilding or complex structures.
        // LCT is the way.
        
        // Implementation of Link-Cut Tree (Splay based) for Path Aggregation?
        // We need Subtree Aggregation? No, we need Connected Component Sum.
        // In LCT, a splay tree represents a preferred path. The auxiliary tree contains the whole component?
        // Standard LCT supports: link, cut, path queries.
        // For component sums: If we maintain the sum of the entire auxiliary tree in the splay node, 
        // then the root of the splay tree representing the component will hold the total sum?
        // Yes. In LCT, `access(u)` makes u the root of its preferred path. The splay tree containing u 
        // will contain all nodes in the same connected component IF we maintain the virtual children sums correctly.
        // Specifically, each node in LCT maintains:
        //   val: its own enemy count
        //   sum: sum of val in its splay subtree (including virtual children contributions)
        //   v_sum: sum of roots of virtual children (children in the represented tree but not in the preferred path)
        // Total sum of component containing u = sum of the root of the splay tree after access(u) and splay(u).
        
        // Let's implement LCT.
    }
}

// Since I started writing DFS and realized it's not enough, I will scrap the DFS approach for the main logic
// and implement a Link-Cut Tree.

struct Node {
    int ch[2];
    int fa;
    int val; // enemies count
    long long sum; // sum of this splay subtree (real + virtual)
    long long v_sum; // sum of virtual children
    bool rev;
    
    Node() : ch{0,0}, fa(0), val(0), sum(0), v_sum(0), rev(false) {}
} tree[MAXN];

bool is_root(int x) {
    if (!x) return false;
    int f = tree[x].fa;
    if (!f) return true;
    return (tree[f].ch[0] != x && tree[f].ch[1] != x);
}

void push_up(int x) {
    if (!x) return;
    tree[x].sum = (long long)tree[x].val + tree[tree[x].ch[0]].sum + tree[tree[x].ch[1]].sum + tree[x].v_sum;
}

void push_rev(int x) {
    if (!x) return;
    tree[x].rev ^= 1;
    swap(tree[x].ch[0], tree[x].ch[1]);
}

void push_down(int x) {
    if (x && tree[x].rev) {
        if (tree[x].ch[0]) push_rev(tree[x].ch[0]);
        if (tree[x].ch[1]) push_rev(tree[x].ch[1]);
        tree[x].rev = false;
    }
}

void rotate(int x) {
    int y = tree[x].fa;
    int z = tree[y].fa;
    int k = (tree[y].ch[1] == x);
    
    if (!is_root(y))
        tree[z].ch[tree[z].ch[1] == y] = x;
    tree[x].fa = z;
    
    tree[y].ch[k] = tree[x].ch[k^1];
    if (tree[x].ch[k^1]) tree[tree[x].ch[k^1]].fa = y;
    
    tree[x].ch[k^1] = y;
    tree[y].fa = x;
    
    push_up(y);
    push_up(x);
}

int st[MAXN];
void splay(int x) {
    int top = 0;
    st[++top] = x;
    for (int i = x; !is_root(i); i = tree[i].fa)
        st[++top] = tree[i].fa;
    while (top) push_down(st[top--]);
    
    while (!is_root(x)) {
        int y = tree[x].fa;
        int z = tree[y].fa;
        if (!is_root(y)) {
            if ((tree[y].ch[0] == x) ^ (tree[z].ch[0] == y))
                rotate(x);
            else
                rotate(y);
        }
        rotate(x);
    }
}

void access(int x) {
    int last = 0;
    for (int t = x; t; last = t, t = tree[t].fa) {
        splay(t);
        // The right child becomes a virtual child
        if (tree[t].ch[1]) {
            tree[t].v_sum += tree[tree[t].ch[1]].sum;
        }
        tree[t].ch[1] = last;
        // The new right child (last) was a root of a splay tree, so its sum was including its virtual children.
        // Now it's a real child, so we subtract its total sum from v_sum?
        // Wait, logic:
        // Before: t's right child was old_real. We detach old_real. old_real becomes virtual.
        //   tree[t].v_sum += tree[old_real].sum
        // After: we attach last. last was a root of a splay tree (virtual child of t effectively before this step? No).
        // Actually, 'last' comes from below. In the loop, 'last' is the node we just accessed from below.
        // When we move up, the node 'last' becomes the real right child of 't'.
        // Previously, 'last' contributed to 't'.v_sum? 
        // No. 'last' was the root of a preferred path below. It was connected via a virtual edge to 't'?
        // Not necessarily directly. But in the represented tree, 'last' is a child of 't' (or in the subtree).
        // Correct LCT update for virtual sum:
        // When detaching right child (d): v_sum += sum[d]
        // When attaching new right child (c): v_sum -= sum[c] (because c is no longer virtual, it's real now)
        if (last) {
            tree[t].v_sum -= tree[last].sum;
        }
        push_up(t);
    }
}

void make_root(int x) {
    access(x);
    splay(x);
    push_rev(x);
}

int find_root(int x) {
    access(x);
    splay(x);
    while (tree[x].ch[0]) {
        push_down(x);
        x = tree[x].ch[0];
    }
    splay(x);
    return x;
}

void split(int x, int y) {
    make_root(x);
    access(y);
    splay(y);
}

void link(int x, int y) {
    make_root(x);
    if (find_root(y) == x) return; // Should not happen per problem statement
    // Make x a virtual child of y
    // Since y is root of its splay tree (after find_root or make_root? make_root(y) puts y at root)
    // We need y to be the parent of x in the represented tree.
    // Standard link: make_root(x), then set x.fa = y, and y.v_sum += x.sum
    make_root(y); // Ensure y is root of its tree to attach x cleanly? 
    // Actually standard: make_root(x); if (find_root(y) != x) { tree[x].fa = y; tree[y].v_sum += tree[x].sum; push_up(y); }
    // But we need to be careful about splay state.
    // Let's stick to: make_root(x); make_root(y); ... no.
    // Correct sequence:
    make_root(x);
    // Now x is root of its component.
    // We want to add edge x-y.
    // We assume y is in another component.
    // We set x's parent to y.
    // Since y might not be splayed, we access(y) then splay(y)?
    // Simpler: 
    make_root(y); // Make y root of its component.
    // Now attach x as a virtual child of y.
    tree[x].fa = y;
    tree[y].v_sum += tree[x].sum;
    push_up(y);
}

void cut(int x, int y) {
    // Remove edge x-y. Assumes edge exists.
    make_root(x);
    access(y);
    splay(y);
    // Now y should have x as left child? 
    // If edge x-y exists and x is root, then y's left child must be x and x has no right child?
    // Actually, if we make_root(x), then access(y), the path x->y is the preferred path.
    // Since x is root, y is the deepest. In the splay tree rooted at y, x should be the left-most node?
    // Wait, if x is root of the tree, and we access(y), the path from x to y is in the splay tree.
    // Since x is the root of the represented tree, it has no parent.
    // In the splay tree at y, x will be the node with minimum depth.
    // Specifically, if the edge is direct, y's left child is x, and x has no right child (since x is root of whole thing? No).
    // Let's verify conditions:
    // tree[y].ch[0] == x && tree[x].ch[1] == 0 && tree[x].fa == y
    if (tree[y].ch[0] == x && tree[x].ch[1] == 0) {
        tree[y].ch[0] = 0;
        tree[x].fa = 0;
        push_up(y);
    } else {
        // Fallback or error? Problem guarantees valid ops.
        // Maybe the direction is y->x?
        // Try swapping? No, make_root(x) fixes direction.
        // If edge exists, x must be left child of y after make_root(x); access(y); splay(y).
        // Unless I messed up make_root.
        // Let's re-verify: make_root(x) reverses path from root to x. So x becomes root.
        // Then access(y) exposes path x->y.
        // Splay(y) brings y to top. The path from x to y is in the left spine of y?
        // Yes, because x is the ancestor (root).
        // So y->left should be x (or a chain ending in x).
        // If the edge is direct, y->left is x.
        // What if there are intermediate nodes? Then y->left is some node z, which eventually leads to x.
        // But we are cutting the edge between x and y. They must be adjacent.
        // If they are adjacent, and x is root, then y's parent in the tree is x.
        // So in the splay tree, y's left child is x?
        // Yes, because x is the immediate predecessor in the DFS order of the path?
        // Actually, if x is parent of y, then in the preferred path, x comes before y.
        // In the splay tree, x will be the max node in the left subtree of y?
        // No, x is the root of the path. So x is the smallest depth.
        // In the splay tree (in-order = depth), x is the leftmost?
        // If x is parent of y, and they are adjacent in preferred path, then x is the immediate predecessor of y in the path.
        // So x is the rightmost node of the left subtree of y? Or just left child?
        // If there are no nodes between them, x is the left child of y.
        // And x cannot have a right child (because that would be deeper than x but shallower than y? No node exists).
        // So condition: tree[y].ch[0] == x && tree[x].ch[1] == 0.
        // This holds.
        
        // Just in case, try the other direction if failed? 
        // But make_root(x) ensures x is root. If edge exists, x is parent of y.
        // If the cut fails, maybe the edge was y->x in input but logically undirected?
        // The problem says "channel between u and v". Undirected.
        // Our link made x child of y? Or y child of x?
        // In link(x, y): make_root(x); make_root(y); tree[x].fa = y.
        // This makes x a child of y.
        // So in cut(x, y): we expect x to be child of y?
        // If we call cut(u, v), we don't know who is parent.
        // But make_root(u) makes u the root. If edge exists, u becomes parent of v?
        // No. make_root(u) flips the tree so u is root.
        // If u and v are connected, and we make u root, then v is in u's subtree.
        // If they are adjacent, v is a direct child of u.
        // Then access(v) makes the path u->v preferred.
        // Splay(v). v's left child should be u.
        // And u's right child should be null.
        // So the check `tree[v].ch[0] == u` is correct.
        // My code above used x, y. Called with x, y.
        // make_root(x). x is root.
        // If edge exists, x is parent of y.
        // access(y). splay(y).
        // Check tree[y].ch[0] == x.
        // This seems correct.
    }
}

void update_val(int x, int w) {
    access(x);
    splay(x);
    tree[x].val = w;
    push_up(x);
}

long long query_component(int x) {
    make_root(x);
    // Now x is the root of the splay tree representing the whole component?
    // Yes, make_root(x) accesses x and splays it. Since it's the root of the component,
    // the splay tree contains all nodes in the component (via virtual children sums propagated up).
    // The total sum is stored in tree[x].sum.
    return tree[x].sum;
}

int main() {
    // Fast IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N >> M) {
        // Reset
        for (int i = 1; i <= N; i++) {
            tree[i] = Node();
            tree[i].fa = 0;
            tree[i].ch[0] = tree[i].ch[1] = 0;
            tree[i].rev = false;
            tree[i].v_sum = 0;
        }

        for (int i = 1; i <= N; i++) {
            int w;
            cin >> w;
            tree[i].val = w;
            tree[i].sum = w;
        }

        for (int i = 0; i < M; i++) {
            int type;
            cin >> type;
            if (type == 1) {
                int u, v;
                cin >> u >> v;
                link(u, v);
            } else if (type == 2) {
                int u, v;
                cin >> u >> v;
                cut(u, v);
                cut(v, u); // Try both? No, cut is symmetric in logic if implemented right?
                // My cut implementation assumes specific orientation after make_root.
                // If I call cut(u, v), it makes u root, expects v to be child.
                // If the edge was stored as v->u (v child of u), then make_root(u) makes u root, v is child. OK.
                // What if the internal representation had u as child of v?
                // make_root(u) flips everything. So u becomes root regardless of previous orientation.
                // So if edge exists, u will be parent of v after make_root(u).
                // So one call to cut(u, v) is sufficient.
                // However, my cut function has a condition. If it fails, maybe I should try cut(v, u)?
                // Theoretically make_root(u) ensures u is root. If edge (u,v) exists, v is direct child.
                // So tree[v].ch[0] should be u.
                // Let's trust the logic. If not, maybe the edge wasn't there? But problem guarantees valid ops.
                // Wait, what if I call cut(u, v) and the edge exists, but my condition `tree[x].ch[1] == 0` fails?
                // That implies x (u) has a right child in the splay tree.
                // But u is the root of the represented tree. In the splay tree, can it have a right child?
                // The right child in splay tree represents nodes with greater depth in the preferred path.
                // Since u is root (depth 0 relative to component), and v is child (depth 1), the path is u->v.
                // In splay tree rooted at v, u is to the left. u cannot have a right child that is part of the path to v.
                // Could u have a right child that is a virtual child? No, virtual children are not in the splay structure as ch[1].
                // ch[1] is strictly the right child in the splay tree (preferred path successor).
                // Since u is the start of the path, it has no predecessor in the path? No, successor is v.
                // In the splay tree, the in-order traversal is the path from top to bottom.
                // So u comes before v. u is in the left subtree of v.
                // Does u have a right child? That would be a node between u and v in depth.
                // But they are adjacent. So no node between. So u.ch[1] must be 0.
                // Logic holds.
            } else if (type == 3) {
                int u, w;
                cin >> u >> w;
                update_val(u, w);
            } else if (type == 4) {
                int u;
                cin >> u;
                cout << query_component(u) << "\n";
            }
        }
    }
    return 0;
}
