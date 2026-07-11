#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int key;
    int w;
    int freq;
    int original_w;
};

int N;
long long K;
vector<Node> nodes;
vector<long long> prefix_sum;
vector<vector<long long>> dp[405];
vector<vector<bool>> visited[405];

long long get_sum(int i, int j) {
    if (i > j) return 0;
    return prefix_sum[j] - prefix_sum[i-1];
}

long long solve(int l, int r, int min_w_idx) {
    if (l > r) return 0;
    
    if (visited[l][r][min_w_idx]) {
        return dp[l][r][min_w_idx];
    }
    
    long long ans = LLONG_MAX;
    
    // Option 1: Don't change the root's weight structure relative to available minimums
    // We must pick a root from [l, r] whose original weight index is >= min_w_idx
    // Actually, the state min_w_idx represents the index in the sorted-by-weight array
    // of the smallest weight we are allowed to use for the root of this subtree.
    
    // Let's re-evaluate the DP state based on the standard solution for this problem.
    // Sort nodes by key first.
    // Let dp[i][j][k] be the min cost for range [i, j] where the root has weight rank >= k.
    // The weights are sorted. Let sorted_weights be w_1 < w_2 < ... < w_N.
    // k is an index into this sorted list (1-based).
    
    // Transitions:
    // For a range [i, j], we can choose any node p in [i, j] as root.
    // If we choose node p as root:
    // 1. If original_weight_rank[p] >= k:
    //    Cost = solve(i, p-1, k) + solve(p+1, j, k) + sum_freq(i, j)
    //    We don't pay K because we can keep the original weight (or assign a valid one without modification penalty? No.)
    //    Wait, the problem says we can modify weights. If we modify, we pay K.
    //    If we don't modify, the node keeps its original weight.
    //    The constraint is: root weight < children weights.
    //    Since we process by weight ranks, if we pick a root with weight rank 'r',
    //    then the left and right subtrees must have roots with weight rank > r.
    //    
    //    Correction on logic:
    //    We sort all unique original weights. Let them be v_1, v_2, ..., v_m (m <= N).
    //    Actually, since we can change weights to ANY real number, we just need to maintain relative order.
    //    The "modification" allows us to treat a node as having a weight that fits anywhere in the sequence,
    //    but at a cost of K. If we don't modify, it must respect its original relative order against others?
    //    No, the problem says: "modify certain nodes' weights... cost K... new weights must be distinct".
    //    Key insight from similar problems (NOI2009 Tree):
    //    We sort the nodes by their original weights. Let this order be p_1, p_2, ..., p_N.
    //    dp[i][j][k] = min cost for key-range [i, j], using only nodes with original-weight-rank >= k as roots.
    //    
    //    For each possible root 'r' in [i, j]:
    //      Case A: We do NOT modify node r's weight.
    //         This is only allowed if original_rank[r] >= k.
    //         Then the children must have weights > weight[r]. So their roots must have original_rank > original_rank[r]?
    //         No, if we don't modify r, its weight is fixed at W_r.
    //         Children must have weights > W_r.
    //         Any child subtree root 'c' must satisfy: if 'c' is not modified, W_c > W_r.
    //         If 'c' is modified, we can make its weight anything > W_r.
    //         However, the DP state definition usually simplifies this:
    //         If we enforce that the root of [i,j] has a weight value corresponding to at least the k-th smallest original weight...
    //
    //    Let's stick to the standard interpretation for this specific problem (d911 / NOI2009):
    //    1. Sort nodes by KEY. This defines the inorder traversal. Indices 1..N.
    //    2. Collect all original weights, sort them, remove duplicates (though problem says distinct).
    //       Map each node's original weight to its rank (1..N).
    //    3. dp[i][j][k] = min cost to build optimal BST for keys i..j, such that the root's weight is >= the k-th smallest original weight.
    //    
    //    Transition for dp[i][j][k]:
    //    We iterate through all possible roots 'r' in [i, j].
    //    Option 1: Modify node r.
    //       Cost = K + dp[i][r-1][k] + dp[r+1][j][k] + sum_freq(i, j).
    //       Why k for children? Because if we modify r, we can assign it a very small weight (but still >= k-th smallest? No).
    //       If we modify r, we can make its weight arbitrarily small relative to the subtree constraints, 
    //       BUT the constraint is that the root's weight must be SMALLER than children.
    //       Wait, the problem says: "root weight < children weights".
    //       So if root has weight W, children must have weights > W.
    //       If we define state k as "root weight must be >= sorted_weights[k]", then:
    //       If we pick r as root:
    //         If we DON'T modify r:
    //           Allowed only if rank[r] >= k.
    //           Root weight becomes W_r (which is >= sorted_weights[k]).
    //           Children must have weights > W_r.
    //           So children roots must have weights >= next rank after rank[r]?
    //           Actually, since weights are distinct, children must have original rank > rank[r] IF they are not modified.
    //           If they are modified, they can be anything > W_r.
    //           To simplify: if root is r (unmodified), children subproblems must satisfy root weight >= sorted_weights[rank[r] + 1].
    //           Cost = dp[i][r-1][rank[r]+1] + dp[r+1][j][rank[r]+1] + sum_freq(i, j).
    //
    //         If we DO modify r:
    //           We pay K. We can assign r a weight such that it satisfies the >= k constraint.
    //           To minimize cost for children, we want r's weight to be as small as possible (so children have more freedom? No).
    //           Children must be > r. If r is small, children can be small too.
    //           Actually, if we modify r, we can conceptually set its weight to be the k-th smallest value (or slightly above k-1).
    //           Then children must be > this value. So children must have weights >= k? Or k+1?
    //           Since we can pick ANY real number, if we modify r, we can pick a weight W' such that sorted_weights[k-1] < W' < sorted_weights[k] (if k>1).
    //           But the state k means "available weights start from index k".
    //           Standard solution logic:
    //           If we modify r, we treat it as having a weight that allows children to start from k.
    //           Wait, if root is modified, we can make it smaller than any unmodified node in the subtree?
    //           Yes. So if we modify r, the constraint passed to children is just k (they must be >= k-th smallest original weight? No).
    //           Let's rethink: The set of available "base" weights are the original ones.
    //           If we modify a node, we can slot it anywhere.
    //           Correct Logic from known solutions:
    //           dp[i][j][k] = min over r in [i,j] of:
    //             (if rank[r] >= k) dp[i][r-1][rank[r]+1] + dp[r+1][j][rank[r]+1] + sum_freq(i, j)
    //             dp[i][r-1][k] + dp[r+1][j][k] + sum_freq(i, j) + K
    //           And we take the minimum of these options for all r.
    //           Also, dp[i][j][k] = min(dp[i][j][k], dp[i][j][k+1]) because if we can satisfy >= k+1, we definitely satisfy >= k (by potentially modifying root to be slightly larger or just picking a different root).
    //           Actually, the recurrence is usually computed backwards for k (from N down to 1).
    //           dp[i][j][k] = min(
    //               dp[i][j][k+1], // Option: ignore the k-th weight constraint effectively by satisfying a stricter one? 
    //                              // No, it means we can form a tree with root weight >= w_{k+1}, which implies >= w_k.
    //               min_over_r ( ... )
    //           )
    //
    //           Let's refine the transition for a fixed k:
    //           val = infinity
    //           For r from i to j:
    //              cost_modify = dp[i][r-1][k] + dp[r+1][j][k] + K
    //              cost_keep = infinity
    //              if (rank[r] >= k)
    //                 cost_keep = dp[i][r-1][rank[r]+1] + dp[r+1][j][rank[r]+1]
    //              val = min(val, cost_keep, cost_modify)
    //           dp[i][j][k] = val + sum_freq(i, j)
    //           Finally: dp[i][j][k] = min(dp[i][j][k], dp[i][j][k+1])
    //
    //           Base cases:
    //           If i > j, cost is 0.
    //           k goes from N+1 down to 1. If k > N, cost is infinity (unless i>j).
    
    // Implementation details:
    // N <= 70? Problem says data values up to 400000, but N?
    // Typical NOI problems N=50 or N=70 for O(N^4). If N=300, need O(N^3).
    // Looking up d911 constraints: N <= 70. O(N^4) is acceptable. 70^4 = 24M, feasible.
    
    // We need to memoize.
    // Dimensions: i(1..N), j(1..N), k(1..N+1).
    
    // Let's restart the function body with this logic.
    return 0; // Placeholder to stop compilation errors before rewriting fully below
}

int main() {
    // Optimize I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> K)) return 0;

    vector<int> keys(N);
    for (int i = 0; i < N; ++i) cin >> keys[i];

    vector<int> weights(N);
    for (int i = 0; i < N; ++i) cin >> weights[i];

    vector<int> freqs(N);
    for (int i = 0; i < N; ++i) cin >> freqs[i];

    // Combine into nodes
    vector<Node> nodes(N);
    for (int i = 0; i < N; ++i) {
        nodes[i] = {keys[i], weights[i], freqs[i], 0};
    }

    // Sort by key to establish inorder traversal (1..N)
    sort(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
        return a.key < b.key;
    });

    // Coordinate compression for weights to get ranks
    vector<int> sorted_weights = weights;
    sort(sorted_weights.begin(), sorted_weights.end());
    // Remove duplicates just in case, though problem says distinct
    sorted_weights.erase(unique(sorted_weights.begin(), sorted_weights.end()), sorted_weights.end());

    int M = sorted_weights.size();
    
    // Assign rank to each node (1-based)
    for (int i = 0; i < N; ++i) {
        auto it = lower_bound(sorted_weights.begin(), sorted_weights.end(), nodes[i].w);
        nodes[i].original_w = (int)(it - sorted_weights.begin()) + 1;
    }

    // Prefix sums for frequencies
    // 1-based indexing for DP convenience
    vector<long long> P(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        P[i+1] = P[i] + nodes[i].freq;
    }

    auto get_sum = [&](int i, int j) {
        if (i > j) return 0LL;
        return P[j] - P[i-1];
    };

    // DP initialization
    // dp[len][i][k] or dp[i][j][k]?
    // Let's use flat vectors or static arrays if N is small.
    // N <= 70.
    // dp[i][j][k]
    // Using vector<vector<vector<long long>>>
    
    // Initialize with 0 for base cases (i > j) handled logically or explicitly
    // We will iterate length from 1 to N
    // k from M+1 down to 1
    
    // To save memory/time, we can use a large static array if stack allows, or vector.
    // 70*70*72 * 8 bytes ~= 2.8 MB. Very safe.
    
    static long long dp[75][75][75];
    // Initialize with a large value? 
    // We will fill it systematically.

    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= N; ++j) {
            for (int k = 0; k <= M + 1; ++k) {
                dp[i][j][k] = 0; 
                // Base case: if i > j, cost is 0. We'll handle i<=j in loops.
            }
        }
    }

    // Iterate over lengths
    for (int len = 1; len <= N; ++len) {
        for (int i = 1; i <= N - len + 1; ++i) {
            int j = i + len - 1;
            
            // Iterate k from M+1 down to 1
            for (int k = M + 1; k >= 1; --k) {
                long long best = -1; // Infinity placeholder

                // Option 1: Inherit from k+1 (if k <= M)
                if (k <= M) {
                    best = dp[i][j][k+1];
                } else {
                    best = LLONG_MAX;
                }

                // Option 2: Try every root r in [i, j]
                for (int r = i; r <= j; ++r) {
                    long long current_cost = LLONG_MAX;
                    
                    // Case A: Modify root r
                    // Cost = K + dp[i][r-1][k] + dp[r+1][j][k]
                    // Note: if i > r-1, dp is 0. Same for r+1 > j.
                    long long left_cost = (r > i) ? dp[i][r-1][k] : 0;
                    long long right_cost = (r < j) ? dp[r+1][j][k] : 0;
                    
                    if (left_cost != LLONG_MAX && right_cost != LLONG_MAX) {
                        current_cost = min(current_cost, left_cost + right_cost + K);
                    }

                    // Case B: Keep original weight of r
                    // Only if rank[r] >= k
                    if (nodes[r-1].original_w >= k) {
                        int next_k = nodes[r-1].original_w + 1;
                        // If next_k > M+1, then children must be empty? 
                        // If next_k > M, then for non-empty children, cost is INF.
                        long long l_c = 0;
                        long long r_c = 0;
                        
                        if (r > i) {
                            if (next_k > M + 1) l_c = LLONG_MAX;
                            else l_c = dp[i][r-1][min(next_k, M+1)];
                        }
                        if (r < j) {
                            if (next_k > M + 1) r_c = LLONG_MAX;
                            else r_c = dp[r+1][j][min(next_k, M+1)];
                        }
                        
                        if (l_c != LLONG_MAX && r_c != LLONG_MAX) {
                            current_cost = min(current_cost, l_c + r_c);
                        }
                    }

                    if (current_cost != LLONG_MAX) {
                        if (best == -1 || current_cost < best) {
                            best = current_cost;
                        }
                    }
                }

                if (best == -1) best = LLONG_MAX;
                
                // Add frequency sum for this level
                if (best != LLONG_MAX) {
                    dp[i][j][k] = best + get_sum(i, j);
                } else {
                    dp[i][j][k] = LLONG_MAX;
                }
            }
        }
    }

    cout << dp[1][N][1] << endl;

    return 0;
}
