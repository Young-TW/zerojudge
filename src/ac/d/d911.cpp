#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int key;
    int w;
    int freq;
};

int N;
long long K;
vector<Node> nodes;
vector<long long> prefix_sum;
vector<vector<vector<long long>>> dp;
vector<vector<vector<bool>>> visited;

long long get_sum(int i, int j) {
    if (i > j) return 0;
    return prefix_sum[j] - prefix_sum[i - 1];
}

long long solve(int l, int r, int min_w_idx) {
    if (l > r) return 0;
    
    if (visited[l][r][min_w_idx]) {
        return dp[l][r][min_w_idx];
    }
    
    long long ans = LLONG_MAX;
    long long sum = get_sum(l, r);
    
    for (int p = l; p <= r; ++p) {
        // Option 1: Modify node p's weight
        // We can assign it a weight that satisfies the >= min_w_idx constraint.
        // To give children the maximum flexibility, we assign it the smallest possible weight,
        // which means children only need to satisfy >= min_w_idx.
        long long cost_modify = K + solve(l, p - 1, min_w_idx) + solve(p + 1, r, min_w_idx) + sum;
        if (cost_modify < ans) {
            ans = cost_modify;
        }
        
        // Option 2: Do not modify node p's weight
        // This is only valid if its original weight rank is >= min_w_idx.
        if (nodes[p].w >= min_w_idx) {
            // Since we don't modify it, its weight is fixed at nodes[p].w.
            // Children must have weights strictly greater than nodes[p].w.
            // So their minimum allowed weight index must be nodes[p].w + 1.
            long long cost_no_modify = solve(l, p - 1, nodes[p].w + 1) + solve(p + 1, r, nodes[p].w + 1) + sum;
            if (cost_no_modify < ans) {
                ans = cost_no_modify;
            }
        }
    }
    
    visited[l][r][min_w_idx] = true;
    dp[l][r][min_w_idx] = ans;
    return ans;
;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N >> K) {
        nodes.resize(N + 1);
        for (int i = 1; i <= N; ++i) cin >> nodes[i].key;
        for (int i = 1; i <= N; ++i) cin >> nodes[i].w;
        for (int i = 1; i <= N; ++i) cin >> nodes[i].freq;

        // Sort by key to form the inorder traversal of the BST
        sort(nodes.begin() + 1, nodes.end(), [](const Node& a, const Node& b) {
            return a.key < b.key;
        });

        // Coordinate compression for weights
        vector<int> weights;
        for (int i = 1; i <= N; ++i) {
            weights.push_back(nodes[i].w);
        }
        sort(weights.begin(), weights.end());
        weights.erase(unique(weights.begin(), weights.end()), weights.end());
        
        for (int i = 1; i <= N; ++i) {
            nodes[i].w = lower_bound(weights.begin(), weights.end(), nodes[i].w) - weights.begin() + 1;
        }

        prefix_sum.resize(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            prefix_sum[i] = prefix_sum[i - 1] + nodes[i].freq;
        }

        int max_w = weights.size();
        // dp[i][j][k] where k ranges from 1 to max_w + 1
        dp.assign(N + 2, vector<vector<long long>>(N + 2, vector<long long>(max_w + 2, 0)));
        visited.assign(N + 2, vector<vector<bool>>(N + 2, vector<bool>(max_w + 2, false)));

        cout << solve(1, N, 1) << "\n";
    }

    return 0;
}
