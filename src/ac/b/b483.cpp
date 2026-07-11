#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 300005; // N, M up to 100,000. Total nodes = N + M.

struct Node {
    int ch[2];
    int p;
    int rev;
    int maxVal;
    int id; // The LCT node index that holds the maxVal in this subtree
    int val; // Weight of this node (0 for vertices, w for edges)
    
    Node() {
        ch[0] = ch[1] = p = rev = 0;
        maxVal = 0;
        id = 0;
        val = 0;
    }
} tree[MAXN];

int lctU[MAXN]; // Maps LCT node index -> U
int lctV[MAXN]; // Maps LCT node index -> V

bool isRoot(int x) {
    if (!tree[x].p) return true;
    int p = tree[x].p;
    return tree[p].ch[0] != x && tree[p].ch[1] != x;
}

void pushUp(int x) {
    tree[x].maxVal = tree[x].val;
    tree[x].id = x;
    
    if (tree[x].ch[0]) {
        if (tree[tree[x].ch[0]].maxVal > tree[x].maxVal) {
            tree[x].maxVal = tree[tree[x].ch[0]].maxVal;
            tree[x].id = tree[tree[x].ch[0]].id;
        }
    }
    if (tree[x].ch[1]) {
        if (tree[tree[x].ch[1]].maxVal > tree[x].maxVal) {
            tree[x].maxVal = tree[tree[x].ch[1]].maxVal;
            tree[x].id = tree[tree[x].ch[1]].id;
        }
    }
}

void pushDown(int x) {
    if (tree[x].rev) {
        if (tree[x].ch[0]) {
            tree[tree[x].ch[0]].rev ^= 1;
            swap(tree[tree[x].ch[0]].ch[0], tree[tree[x].ch[0]].ch[1]);
        }
        if (tree[x].ch[1]) {
            tree[tree[x].ch[1]].rev ^= 1;
            swap(tree[tree[x].ch[1]].ch[0], tree[tree[x].ch[1]].ch[1]);
        }
        tree[x].rev = 0;
    }
}

void rotate(int x) {
    int y = tree[x].p;
    int z = tree[y].p;
    int k = (tree[y].ch[1] == x);
    
    if (!isRoot(y)) {
        if (tree[z].ch[0] == y) tree[z].ch[0] = x;
        else tree[z].ch[1] = x;
    }
    tree[x].p = z;
    
    tree[y].ch[k] = tree[x].ch[k ^ 1];
    if (tree[x].ch[k ^ 1]) tree[tree[x].ch[k ^ 1]].p = y;
    
    tree[x].ch[k ^ 1] = y;
    tree[y].p = x;
    
    pushUp(y);
    pushUp(x);
}

int q[MAXN];
void splay(int x) {
    int top = 0;
    q[++top] = x;
    for (int i = x; !isRoot(i); i = tree[i].p) {
        q[++top] = tree[i].p;
    }
    while (top) pushDown(q[top--]);
    
    while (!isRoot(x)) {
        int y = tree[x].p;
        int z = tree[y].p;
        if (!isRoot(y)) {
            if ((tree[y].ch[0] == x) ^ (tree[z].ch[0] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}

void access(int x) {
    int t = 0;
    while (x) {
        splay(x);
        tree[x].ch[1] = t;
        pushUp(x);
        t = x;
        x = tree[x].p;
    }
}

void makeRoot(int x) {
    access(x);
    splay(x);
    tree[x].rev ^= 1;
    swap(tree[x].ch[0], tree[x].ch[1]);
}

int findRoot(int x) {
    access(x);
    splay(x);
    while (tree[x].ch[0]) {
        pushDown(x);
        x = tree[x].ch[0];
    }
    splay(x);
    return x;
}

void split(int x, int y) {
    makeRoot(x);
    access(y);
    splay(y);
}

bool link(int x, int y) {
    makeRoot(x);
    if (findRoot(y) == x) return false;
    tree[x].p = y;
    return true;
}

void cut(int x, int y) {
    makeRoot(x);
    if (findRoot(y) == x && tree[y].p == x && !tree[y].ch[0]) {
        tree[y].p = 0;
        tree[x].ch[1] = 0;
        pushUp(x);
    }
}

int main() {
    int N, M;
    int caseId = 0;
    
    while (cin >> N >> M) {
        caseId++;
        printf("Case #%d\n", caseId);
        
        int limit = N + M;
        for (int i = 0; i <= limit; ++i) {
            tree[i] = Node();
            if (i >= 1 && i <= N) {
                tree[i].val = 0;
                tree[i].maxVal = 0;
                tree[i].id = 0;
            }
        }
        
        long long currentMSTCost = 0;
        int nodeCounter = N;
        
        for (int i = 1; i <= M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            
            nodeCounter++;
            int edgeNode = nodeCounter;
            
            tree[edgeNode].val = w;
            tree[edgeNode].maxVal = w;
            tree[edgeNode].id = edgeNode;
            lctU[edgeNode] = u;
            lctV[edgeNode] = v;
            
            if (findRoot(u) != findRoot(v)) {
                link(u, edgeNode);
                link(edgeNode, v);
                currentMSTCost += w;
            } else {
                split(u, v);
                int maxEdgeNode = tree[v].id;
                int maxW = tree[maxEdgeNode].val;
                
                if (w < maxW) {
                    int oldU = lctU[maxEdgeNode];
                    int oldV = lctV[maxEdgeNode];
                    
                    cut(oldU, maxEdgeNode);
                    cut(maxEdgeNode, oldV);
                    
                    currentMSTCost -= maxW;
                    currentMSTCost += w;
                    
                    link(u, edgeNode);
                    link(edgeNode, v);
                }
            }
            printf("%lld\n", currentMSTCost);
        }
    }
    return 0;
}
