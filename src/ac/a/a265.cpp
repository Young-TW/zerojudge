#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

struct Node {
    int val;
    int left = -1;
    int right = -1;
};

int n;
vector<Node> nodes;
vector<int> indeg;
vector<vector<ull>> dpBlack, dpRed;   // dp[color][bh]

void dfs(int u) {
    if (u == -1) return;
    int l = nodes[u].left;
    int r = nodes[u].right;
    if (l != -1) dfs(l);
    if (r != -1) dfs(r);

    // temporary arrays for child contributions
    vector<ull> leftWays(n + 2, 0), rightWays(n + 2, 0);
    // we will fill them later for each colour of current node
    // compute for colour = red (0) and black (1)
    for (int colour = 0; colour <= 1; ++colour) {
        // allowed colours for children
        bool allowRed = (colour == 1);   // if current node is black, child may be red
        bool allowBlack = true;          // child may always be black

        // build leftWays
        fill(leftWays.begin(), leftWays.end(), 0);
        if (l == -1) {
            leftWays[0] = 1; // NIL
        } else {
            for (int bh = 0; bh <= n; ++bh) {
                if (allowRed) leftWays[bh] += dpRed[l][bh];
                if (allowBlack) leftWays[bh] += dpBlack[l][bh];
            }
        }
        // build rightWays
        fill(rightWays.begin(), rightWays.end(), 0);
        if (r == -1) {
            rightWays[0] = 1;
        } else {
            for (int bh = 0; bh <= n; ++bh) {
                if (allowRed) rightWays[bh] += dpRed[r][bh];
                if (allowBlack) rightWays[bh] += dpBlack[r][bh];
            }
        }

        // combine
        for (int bhL = 0; bhL <= n; ++bhL) if (leftWays[bhL]) {
            for (int bhR = 0; bhR <= n; ++bhR) if (rightWays[bhR]) {
                if (bhL != bhR) continue;               // black‑height must match
                int bhNode = bhL + (colour == 1 ? 1 : 0);
                ull ways = leftWays[bhL] * rightWays[bhR];
                if (colour == 0) dpRed[u][bhNode]   += ways;
                else            dpBlack[u][bhNode] += ways;
            }
        }
    }
}

// verify BST property recursively
bool checkBST(int u, long long lo, long long hi) {
    if (u == -1) return true;
    long long v = nodes[u].val;
    if (!(lo < v && v < hi)) return false;
    return checkBST(nodes[u].left, lo, v) && checkBST(nodes[u].right, v, hi);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNo = 1;
    while (cin >> n) {
        nodes.clear(); nodes.reserve(n);
        indeg.assign(2 * n + 5, 0); // map value -> index via unordered_map later
        unordered_map<int,int> id; id.reserve(n*2);
        vector<pair<int,int>> edges;
        edges.reserve(n-1);
        for (int i = 0; i < n-1; ++i) {
            int P,S; cin >> P >> S;
            edges.emplace_back(P,S);
            if (!id.count(P)) { int idx = nodes.size(); id[P]=idx; nodes.push_back({P}); }
            if (!id.count(S)) { int idx = nodes.size(); id[S]=idx; nodes.push_back({S}); }
        }
        // ensure all nodes exist (in case n==1)
        if (n==1) {
            // find the single value (no edges)
            // we cannot know its value from edges, but problem guarantees distinct values.
            // In this case, we can just create a dummy node with value 0.
            // However, when n==1 there will be no edge lines, so we need to read nothing.
            // We'll treat the tree as a single node with arbitrary value 0.
            nodes.push_back({0});
        }

        // initialise children to -1
        for (auto &nd : nodes) { nd.left = nd.right = -1; }

        // build tree
        bool invalid = false;
        for (auto &e : edges) {
            int p = id[e.first];
            int s = id[e.second];
            indeg[s]++;
            if (e.second < e.first) { // child value < parent => left
                if (nodes[p].left != -1) { invalid = true; break; }
                nodes[p].left = s;
            } else if (e.second > e.first) { // right
                if (nodes[p].right != -1) { invalid = true; break; }
                nodes[p].right = s;
            } else { // equal values not allowed
                invalid = true; break;
            }
        }
        // find root
        int root = -1;
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (indeg[i] == 0) {
                if (root != -1) { invalid = true; break; }
                root = (int)i;
            }
        }
        if (root == -1) invalid = true;

        // check each node has at most two children (already ensured) and BST ordering globally
        if (!invalid) {
            if (!checkBST(root, LLONG_MIN, LLONG_MAX)) invalid = true;
        }

        ull answer = 0;
        if (!invalid) {
            dpBlack.assign(nodes.size(), vector<ull>(n + 2, 0));
            dpRed.assign(nodes.size(),   vector<ull>(n + 2, 0));
            dfs(root);
            for (int bh = 0; bh <= n; ++bh) answer += dpBlack[root][bh];
        }

        cout << "Case " << caseNo++ << ":" << answer << "\n";
    }
    return 0;
}
