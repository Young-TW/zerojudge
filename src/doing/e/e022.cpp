#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Edge {
    int to;
    int type; // 0: movable, 1: concrete
};

int M, N, K, L;
vector<Edge> adjA[1005]; // Adjacency for A cities (1..M)
vector<Edge> adjB[1005]; // Adjacency for B cities (1..N)
bool hasConcreteA[1005];
bool hasConcreteB[1005];

int maxLen;

// DFS function
// u: current city index
// region: 0 for A, 1 for B
// lastType: type of the bridge used to arrive here (0 or 1). -1 for start.
// length: current path length (number of bridges)
// visitedA: visited status for A cities
// visitedB: visited status for B cities
void dfs(int u, int region, int lastType, int length, vector<bool>& visitedA, vector<bool>& visitedB) {
    if (length > maxLen) {
        maxLen = length;
    }

    // If we reached L, we can't go further
    if (length >= L) return;

    // Determine next expected bridge type
    // Rule: movable(0) -> concrete(1) -> movable(0) ...
    // Start must be movable(0). So if lastType == -1, next must be 0.
    // If lastType == 0, next must be 1.
    // If lastType == 1, next must be 0.
    int nextType = (lastType == -1) ? 0 : (1 - lastType);

    if (region == 0) {
        // Currently in A, move to B
        if (visitedA[u]) return; // Should be handled before call, but safety check
        // We mark visited when entering? 
        // Actually, let's mark visited before recursing to avoid cycles in current path
        
        for (const auto& edge : adjA[u]) {
            if (edge.type == nextType) {
                int v = edge.to; // v is in B
                if (!visitedB[v]) {
                    // Check constraint: if this is the end of a potential path, 
                    // the endpoint must not have concrete bridge.
                    // But we are in the middle of DFS, we don't know if it's the end yet.
                    // The constraint "Start and End cities themselves have no concrete bridge"
                    // applies to the specific path found.
                    // So:
                    // 1. Start node (initial call) must not have concrete bridge. (Checked before calling dfs)
                    // 2. If we stop at node v, then v must not have concrete bridge.
                    //    This is implicitly handled because if v has concrete bridge, 
                    //    we might continue, but if we CAN'T continue or choose to stop, 
                    //    does it count?
                    // The problem says: "Find a path... satisfying characteristics".
                    // Characteristic 3: "Start and End cities themselves have no concrete bridge".
                    // This means a valid path CANNOT end at a city with a concrete bridge.
                    // So if we are at v, and we decide to stop (or cannot move further), 
                    // we only update maxLen if v satisfies the condition.
                    // HOWEVER, we might be able to move further from v.
                    // If v has a concrete bridge, we MUST move further? 
                    // No, the path definition requires the END point to satisfy the condition.
                    // So any path ending at a node with a concrete bridge is INVALID.
                    // Thus, we can only consider 'length' as a candidate answer if the current node 
                    // (which would be the end if we stopped) satisfies the condition.
                    // But wait, we are looking for the LONGEST path.
                    // If we are at v, and v has a concrete bridge, we cannot STOP here. 
                    // We must try to extend. If we can't extend, then this branch yields no valid path ending here.
                    
                    // Let's refine:
                    // Update maxLen ONLY IF the current node (v) satisfies the "no concrete bridge" condition.
                    // Because if it doesn't, this path length is not a valid "Augmenting Path" ending here.
                    
                    visitedB[v] = true;
                    dfs(v, 1, edge.type, length + 1, visitedA, visitedB);
                    visitedB[v] = false;
                }
            }
        }
    } else {
        // Currently in B, move to A
        if (visitedB[u]) return;

        for (const auto& edge : adjB[u]) {
            if (edge.type == nextType) {
                int v = edge.to; // v is in A
                if (!visitedA[v]) {
                    visitedA[v] = true;
                    dfs(v, 0, edge.type, length + 1, visitedA, visitedB);
                    visitedA[v] = false;
                }
            }
        }
    }
}

void solve() {
    // Reset data structures
    for (int i = 1; i <= M; ++i) {
        adjA[i].clear();
        hasConcreteA[i] = false;
    }
    for (int i = 1; i <= N; ++i) {
        adjB[i].clear();
        hasConcreteB[i] = false;
    }

    for (int i = 0; i < K; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        // u in A, v in B
        adjA[u].push_back({v, t});
        adjB[v].push_back({u, t});
        if (t == 1) {
            hasConcreteA[u] = true;
            hasConcreteB[v] = true;
        }
    }

    maxLen = -1;

    // Try starting from every city in A
    for (int i = 1; i <= M; ++i) {
        // Constraint: Start city must not have concrete bridge
        if (hasConcreteA[i]) continue;
        
        // Must start with a movable bridge (type 0)
        bool hasMovable = false;
        for (const auto& e : adjA[i]) {
            if (e.type == 0) {
                hasMovable = true;
                break;
            }
        }
        if (!hasMovable) continue;

        vector<bool> visitedA(M + 1, false);
        vector<bool> visitedB(N + 1, false);
        
        visitedA[i] = true;
        // Start DFS: at A[i], lastType = -1 (meaning next must be 0), length = 0
        // But wait, the path length is number of bridges.
        // If we step to a neighbor, length becomes 1.
        // The DFS function design:
        // We are at 'u'. We look for next edges.
        // If we traverse an edge, length increases.
        // Inside DFS, after moving to v, we check if v is a valid end point.
        
        // Let's restructure slightly to handle the "End point constraint" cleanly.
        // We pass the current node and the length so far.
        // At the beginning of DFS(u, ...), we check if u is a valid end point.
        // If yes, update maxLen.
        // Then try to extend.
        
        // Re-call logic:
        // Start at i (Region A). Length 0.
        // But a path must have at least 1 bridge.
        // So we shouldn't update maxLen at length 0.
        // The DFS will move to a neighbor, length becomes 1, then check validity.
        
        dfs(i, 0, -1, 0, visitedA, visitedB);
    }

    // Try starting from every city in B
    for (int i = 1; i <= N; ++i) {
        if (hasConcreteB[i]) continue;
        
        bool hasMovable = false;
        for (const auto& e : adjB[i]) {
            if (e.type == 0) {
                hasMovable = true;
                break;
            }
        }
        if (!hasMovable) continue;

        vector<bool> visitedA(M + 1, false);
        vector<bool> visitedB(N + 1, false);
        
        visitedB[i] = true;
        dfs(i, 1, -1, 0, visitedA, visitedB);
    }

    cout << maxLen << endl;
}

// Overloaded DFS to handle the validation at each step correctly
void dfsValid(int u, int region, int lastType, int length, vector<bool>& visitedA, vector<bool>& visitedB) {
    // If length > 0, we have traversed at least one bridge.
    // Check if current node can be an endpoint (no concrete bridge connected)
    if (length > 0) {
        bool isValidEnd = false;
        if (region == 0) {
            if (!hasConcreteA[u]) isValidEnd = true;
        } else {
            if (!hasConcreteB[u]) isValidEnd = true;
        }

        if (isValidEnd) {
            if (length > maxLen) maxLen = length;
        }
    }

    if (length >= L) return;

    int nextType = (lastType == -1) ? 0 : (1 - lastType);

    if (region == 0) {
        for (const auto& edge : adjA[u]) {
            if (edge.type == nextType) {
                int v = edge.to;
                if (!visitedB[v]) {
                    visitedB[v] = true;
                    dfsValid(v, 1, edge.type, length + 1, visitedA, visitedB);
                    visitedB[v] = false;
                }
            }
        }
    } else {
        for (const auto& edge : adjB[u]) {
            if (edge.type == nextType) {
                int v = edge.to;
                if (!visitedA[v]) {
                    visitedA[v] = true;
                    dfsValid(v, 0, edge.type, length + 1, visitedA, visitedB);
                    visitedA[v] = false;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> M >> N >> K >> L) {
        // Reset
        for (int i = 1; i <= M; ++i) {
            adjA[i].clear();
            hasConcreteA[i] = false;
        }
        for (int i = 1; i <= N; ++i) {
            adjB[i].clear();
            hasConcreteB[i] = false;
        }

        for (int i = 0; i < K; ++i) {
            int u, v, t;
            cin >> u >> v >> t;
            adjA[u].push_back({v, t});
            adjB[v].push_back({u, t});
            if (t == 1) {
                hasConcreteA[u] = true;
                hasConcreteB[v] = true;
            }
        }

        maxLen = -1;

        // Start from A
        for (int i = 1; i <= M; ++i) {
            if (hasConcreteA[i]) continue;
            // Optimization: if no movable bridge from start, skip
            bool canStart = false;
            for(auto& e : adjA[i]) if(e.type == 0) { canStart = true; break; }
            if(!canStart) continue;

            vector<bool> visitedA(M + 1, false);
            vector<bool> visitedB(N + 1, false);
            visitedA[i] = true;
            dfsValid(i, 0, -1, 0, visitedA, visitedB);
        }

        // Start from B
        for (int i = 1; i <= N; ++i) {
            if (hasConcreteB[i]) continue;
            bool canStart = false;
            for(auto& e : adjB[i]) if(e.type == 0) { canStart = true; break; }
            if(!canStart) continue;

            vector<bool> visitedA(M + 1, false);
            vector<bool> visitedB(N + 1, false);
            visitedB[i] = true;
            dfsValid(i, 1, -1, 0, visitedA, visitedB);
        }

        cout << maxLen << endl;
    }

    return 0;
}
