#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> sz;
    int components;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        components = n;
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return false;
        if (sz[rx] < sz[ry]) swap(rx, ry);
        parent[ry] = rx;
        sz[rx] += sz[ry];
        components--;
        return true;
    }

    int get_size(int x) {
        return sz[find(x)];
    }
};

struct Edge {
    int u, v;
    int id;
};

struct Meteor {
    int t;
    int p; // edge id (1-based)
};

int main() {
    int N, E, R, M;
    if (!(cin >> N >> E >> R >> M)) return 0;

    vector<Edge> edges(E + 1); // 1-based indexing for edges
    for (int i = 1; i <= E; ++i) {
        cin >> edges[i].u >> edges[i].v;
        edges[i].id = i;
    }

    vector<Meteor> meteors(R);
    for (int i = 0; i < R; ++i) {
        cin >> meteors[i].t >> meteors[i].p;
    }

    vector<int> C(M);
    for (int i = 0; i < M; ++i) {
        cin >> C[i];
    }

    // Determine the time each edge is destroyed.
    // If an edge is never hit, its destruction time is infinity.
    // We use a large number for infinity, but since we need to output INF string,
    // we can handle it logically. Let's use -1 to represent "never destroyed".
    vector<int> destroy_time(E + 1, -1);
    
    for (int i = 0; i < R; ++i) {
        int t = meteors[i].t;
        int p = meteors[i].p;
        // If an edge is hit multiple times, the earliest time matters?
        // The problem says "R meteorites... each will hit one of the E roads".
        // It implies distinct roads or sequential events.
        // "Every meteorite will hit... road pj at time tj".
        // If a road is hit twice, the first hit destroys it.
        // However, usually in such problems, the list of meteorites describes unique events or the first one counts.
        // Given the constraints and typical problem style, let's assume if a road is listed multiple times,
        // the earliest time is when it gets destroyed. Or simply, the input guarantees unique roads?
        // The problem says "R顆隕石...打在其中R條負責連接...的E條道路上面", implying R distinct roads are hit.
        // So we can assume each pj appears once.
        destroy_time[p] = t;
    }

    // Prepare queries: For each elderly person with requirement c_i, find the max time T such that
    // the component size containing their city (which city? The problem says "his city".
    // Wait, the input doesn't specify WHICH city each elderly person lives in!
    // Re-reading: "給你...M個老人的ci". It doesn't say where they live.
    // "如果第i個老人發現了自己的城市所在地可連通到的城市(含自己這座)少於ci座"
    // This implies the answer must be independent of the specific city, OR the problem assumes
    // the worst case? Or maybe the input format description missed the city index?
    // Let's re-read carefully.
    // "輸入說明...最後一行有M個正整數ci以空格隔開。"
    // There is NO city index for each elderly person.
    // How can we determine if they leave without knowing their city?
    // Maybe the condition applies to ANY city they could be in?
    // "使得這位老人可以在定居最久...的前提下"
    // If the graph becomes disconnected such that SOME components have size < ci, does everyone leave?
    // No, "if he finds HIS city's component...".
    // Is it possible the problem implies we must ensure the condition holds for ALL possible cities?
    // Or perhaps the question asks: What is the time until the graph state becomes such that 
    // there EXISTS a component with size < ci? No, that would force someone to leave, but not necessarily "the" elder.
    // Wait, look at the sample cases.
    // Sample 1: N=5. Edges: (1,2), (5,1), (4,5), (2,3), (1,3), (3,4). Graph is connected initially (size 5).
    // Meteors: (t=1, p=2), (t=2, p=6), (t=3, p=1), (t=4, p=4).
    // Roads: 1:(1,2), 2:(5,1), 3:(4,5), 4:(2,3), 5:(1,3), 6:(3,4).
    // Destructions:
    // t=1: Road 2 (5-1) breaks.
    // t=2: Road 6 (3-4) breaks.
    // t=3: Road 1 (1-2) breaks.
    // t=4: Road 4 (2-3) breaks.
    // Elders: c = {5, 3, 1}.
    // Output: 2, 4, INF.
    
    // Analysis of Sample 1:
    // Initially (t=0): All connected. Component sizes: {5}.
    // If an elder needs c=5, they are fine as long as their component is 5.
    // At t=1 (Road 2 breaks): Path 5-1 gone. Graph: 5-4-3-2-1 (via 3-4, 2-3, 1-3, 1-2? Wait).
    // Let's trace connectivity.
    // Initial edges: {1,2}, {5,1}, {4,5}, {2,3}, {1,3}, {3,4}.
    // t=1: Remove {5,1}. Remaining: {1,2}, {4,5}, {2,3}, {1,3}, {3,4}.
    // Connectivity: 1-2-3-4-5. Still connected? 1-2, 2-3, 3-4, 4-5. Yes. Size 5.
    // t=2: Remove {3,4} (Road 6). Remaining: {1,2}, {4,5}, {2,3}, {1,3}.
    // Connections: 1-2, 2-3, 1-3 (Triangle 1-2-3). And 4-5.
    // Components: {1,2,3} (size 3), {4,5} (size 2).
    // Elder 1 (c=5): If living in {1,2,3}, size=3 < 5 -> Leave. If in {4,5}, size=2 < 5 -> Leave.
    // So at t=2, everyone with c=5 must leave. Max time = 2? Output says 2. Correct.
    // Elder 2 (c=3): If in {1,2,3}, size=3 >= 3 OK. If in {4,5}, size=2 < 3 -> Leave.
    // The problem asks "for each elder". But we don't know their city.
    // Does "must leave" mean if there is ANY scenario where they might be forced?
    // Or does the problem imply the elder lives in a specific city that makes the condition hardest?
    // Actually, re-reading the problem statement in Chinese context often implies:
    // "Find the time T such that for the elder to stay as long as possible, he MUST leave by T."
    // If the elder's city is not given, maybe the answer is based on the WORST-CASE city?
    // i.e., The earliest time when THERE EXISTS a component with size < ci?
    // If such a component exists, an elder living there would leave. Since we don't know where they live,
    // to guarantee they don't violate the condition ("must leave"), we must assume they might be in the bad component.
    // Thus, the time they must leave is the first time ANY component has size < ci.
    // Let's verify with Elder 2 (c=3) in Sample 1.
    // At t=2, components are {3, 2}. Min size = 2. Since 2 < 3, someone must leave.
    // If the elder is unlucky, they are in the size-2 component. So they must leave by t=2?
    // But the sample output for c=3 is 4. Why?
    // Maybe the elder chooses the best city? "使得這位老人可以在定居最久...的前提下".
    // Ah, "he can stay the longest". This implies the elder can CHOOSE his city optimally to maximize stay time?
    // Or maybe the input implicitly assumes something else?
    // Wait, "第i個老人發現了自己的城市所在地". It sounds like the city is fixed but unknown to us?
    // No, that doesn't make sense for a deterministic output.
    // Interpretation B: The elder lives in a city that allows him to stay the longest.
    // i.e., We look for the maximum time T such that there EXISTS a component with size >= ci at time T.
    // If at time T, all components have size < ci, then he MUST leave by T.
    // Let's re-evaluate Sample 1 with this logic.
    // c=5: Need component size >= 5.
    // t=0: {5} (OK). t=1: {5} (OK). t=2: {3, 2} (Max=3 < 5). Fail.
    // So he must leave before t=2 completes? Or at t=2?
    // The meteor hits at time t. "必须在几年内搬出".
    // If at time t=2, the road breaks and component shrinks. Immediately after t=2, condition fails.
    // So he must leave BY year 2? Output is 2. Matches.
    
    // c=3: Need component size >= 3.
    // t=0: {5} (OK). t=1: {5} (OK). t=2: {3, 2} (Max=3 >= 3). OK (can live in {1,2,3}).
    // t=3: Remove Road 1 (1-2).
    // Current edges at t=2 (after removing 2, 6): {1,2}, {4,5}, {2,3}, {1,3}.
    // Remove {1,2}. Remaining: {4,5}, {2,3}, {1,3}.
    // Connections: 1-3-2. (1,3,2 connected). 4-5.
    // Components: {1,2,3} (size 3), {4,5} (size 2). Max=3. OK.
    // t=4: Remove Road 4 (2-3).
    // Remaining: {4,5}, {1,3}. (2 is isolated? Edge {2,3} removed, {1,2} removed earlier).
    // Edges left: {4,5}, {1,3}. Nodes: 1-3, 4-5, 2 alone.
    // Components: {1,3} (2), {4,5} (2), {2} (1). Max=2.
    // 2 < 3. Fail.
    // So at t=4, condition fails. Must leave by 4. Output is 4. Matches!
    
    // c=1: Need size >= 1. Always true as long as node exists. Output INF. Matches.
    
    // Conclusion: The problem asks for the earliest time T such that MAX(component_sizes) < ci.
    // The elder can choose to live in the largest component. He stays as long as the largest component is >= ci.
    // Once the largest component drops below ci, he must leave.
    // The answer is the time T of the event that causes max_size < ci.
    
    // Algorithm:
    // 1. Collect all destruction events (time, edge_id). Sort by time ascending.
    // 2. Add a sentinel event at time INF (or just process until end).
    // 3. We need to find the state of the graph at different times.
    // Since N, E, R are small? Constraints not given but typical for ZeroJudge C++ might be up to 10^5.
    // If R is large, simulating step-by-step with BFS/DFS is O(R * (N+E)). Might be too slow if R ~ 10^5.
    // Better approach: Reverse time.
    // Start from the final state (all meteors fallen). Add edges back in reverse order of destruction.
    // Maintain the maximum component size using DSU.
    // Store the max component size for each time interval.
    // Then for each query ci, find the earliest time where max_size < ci.
    
    // Steps for Reverse Approach:
    // 1. Identify all edges that are destroyed. Record their destruction time.
    // 2. Build the graph with ONLY edges that are NEVER destroyed (time = -1).
    // 3. Initialize DSU with these edges. Calculate initial max_component_size.
    // 4. Collect destroyed edges and sort them by destruction time DESCENDING.
    // 5. Iterate through sorted destroyed edges. For each group of edges destroyed at the same time T:
    //    - Before adding them, the current max_size represents the state AFTER time T (i.e., from T to next_event).
    //    - Wait, logic check:
    //      Time flows 0 -> T1 -> T2 ...
    //      At time T, edge breaks. State changes.
    //      Reverse: Start at "End" (all broken). Add edges with largest T first.
    //      When we are about to add edges with time T, the current DSU state represents the graph for time > T (specifically T to next_larger_T? No).
    //      Let's clarify intervals.
    //      Events at t1 < t2 < ... < tk.
    //      Intervals: [0, t1), [t1, t2), ..., [tk, infinity).
    //      In forward time:
    //      State 0: [0, t1). Edges: All except those with time <= t1? No.
    //      At time t1, edge breaks. So for t in [0, t1), edge exists. At t=t1, it's gone.
    //      So State 0 (valid for t < t1) has all edges with destroy_time >= t1 (and never destroyed).
    //      Actually, strictly speaking:
    //      If an edge breaks at t, it is present for time < t, and absent for time >= t.
    //      So for a query "must leave by X", it means at time X, the condition fails.
    //      So we need the state at exact time T (after destructions at T happen).
    //      
    //      Reverse process:
    //      Start with NO destroyed edges added (only never-destroyed). This is state at t = max(t_all) + epsilon.
    //      Actually, let's just consider the set of active edges at time T is { e | destroy_time[e] > T or destroy_time[e] == -1 }.
    //      Wait, if destroy_time == T, it breaks AT T. So at time T, it is gone.
    //      So active at T: destroy_time > T.
    //      
    //      Let's sort unique destruction times: T1 < T2 < ... < Tk.
    //      We want to know max_size at time T1, T2, etc.
    //      State at time Tk (after Tk events): Edges with time > Tk (none) + never destroyed.
    //      State at time T(k-1): Edges with time > T(k-1) (includes Tk) + never destroyed.
    //      
    //      Reverse iteration:
    //      1. Start DSU with never-destroyed edges.
    //      2. Current max_size corresponds to time > Tk (infinity).
    //      3. Add edges with destroy_time == Tk. Now DSU represents state where edges with time >= Tk are present?
    //         No. If we add edges with time == Tk, we are reverting the break at Tk.
    //         So the new state represents time < Tk (but >= T(k-1)).
    //         Specifically, just before Tk happens.
    //         But we need the state AT Tk (after break).
    //         
    //      Let's refine:
    //      We need to evaluate condition at t = T1, T2, ..., Tk.
    //      Condition fails at T if max_size(T) < ci.
    //      max_size(T) uses edges with destroy_time > T.
    //      
    //      Plan:
    //      - Group edges by destroy_time.
    //      - Get sorted unique times: t_1 < t_2 < ... < t_k.
    //      - Start DSU with edges that are never destroyed (destroy_time == -1).
    //      - Current max_size is for time > t_k (effectively infinity).
    //      - We iterate from largest time to smallest: t_k, t_{k-1}, ..., t_1.
    //      - Before processing time t_i, the DSU contains edges with destroy_time > t_i (and -1).
    //        This is exactly the state AT time t_i (since edges with time == t_i are broken at t_i).
    //      - So, record: At time t_i, max_size = current_max.
    //      - Then, add all edges with destroy_time == t_i to DSU.
    //      - Move to t_{i-1}.
    //      
    //      After the loop, we have max_size for each t_i.
    //      Also need state at t=0?
    //      If no meteors, state is always initial.
    //      If meteors exist, the first event is t_1.
    //      For t < t_1, the graph is fully connected (all edges present).
    //      We should also consider the state "before any meteor".
    //      But the question is "must leave within X years".
    //      If condition fails at t_1, answer is t_1.
    //      If condition holds at t_1, t_2, ... t_k, then INF.
    //      What if condition fails immediately at t=0? (e.g. initial graph already bad? Unlikely given problem, but possible if c_i > N).
    //      If c_i > N, output -1.
    //      
    //      Data structure to store results: Map<time, max_size>.
    //      Also handle the case where c_i is never satisfied even at t=0?
    //      Check initial state (all edges). If max_size < c_i, output -1.
    //      
    //      Implementation details:
    //      - Map or vector of pairs (time, max_size_at_that_time).
    //      - Sort unique times descending.
    //      - DSU operations.
    //      - Answer queries by binary search or linear scan (M is likely small or we can precompute answers).
    //      - Since we need "earliest time T where max_size(T) < ci", and max_size is non-increasing with time (edges break),
    //        the function f(T) = max_size(T) is a step function decreasing over time.
    //        We want smallest T such that f(T) < ci.
    //        
    //      Special case: If f(0) < ci, output -1.
    //      If f(t_k) >= ci, output INF.
    //      
    //      Wait, f(0) is the state with ALL edges.
    //      Our reverse process starts with "never destroyed" and adds back.
    //      After adding all destroyed edges, we reach the state at t=0 (actually t < t_1).
    //      So we can capture the state "before t_1" as well.
    //      But the failure times are specifically the event times t_j.
    //      Because between events, the graph doesn't change.
    //      If it's good at t_j, it's good until t_{j+1}.
    //      So we only check at t_1, t_2, ..., t_k.
    //      
    //      Steps:
    //      1. Read input.
    //      2. Compute destroy_time for each edge.
    //      3. Check if c_i > N -> -1.
    //      4. Build list of events: map<int, vector<int>> time_to_edges.
    //      5. Get sorted unique times: times[].
    //      6. Init DSU with edges having destroy_time == -1.
    //      7. current_max = max component size.
    //      8. Create a list of checkpoints: vector<pair<int, int>> checks; // (time, max_size)
    //      9. Iterate t in times (descending):
    //         - Record (t, current_max). This is the state AT time t (after breaks).
    //         - Add edges with destroy_time == t to DSU. Update current_max.
    //      10. After loop, we have states at all t_j.
    //          We also need to know if it fails BEFORE any meteor?
    //          If c_i > initial_max_size (with all edges), then -1.
    //          How to get initial_max_size? It's the current_max after adding ALL edges in reverse step.
    //          So after the loop finishes (processed t_1), we add edges of t_1, then current_max is the state for t < t_1.
    //          Let's call this initial_max.
    //          
    //      Query logic for c:
    //      - If c > initial_max: return -1.
    //      - Find smallest t in checks such that max_size < c.
    //      - If no such t, return INF.
    //      
    //      Note: "checks" stores (t, size_at_t).
    //      Since we iterated descending, checks is sorted by time descending.
    //      We can reverse it to be ascending, then find first element with size < c.
    //      
    //      Corner case: Multiple meteors at same time. Handled by grouping.
    //      Constraints: N, E, R, M. Assuming standard competitive programming limits (e.g., 10^5).
    //      Complexity: O(E log E + R log R + M log R). Efficient enough.

    // One detail: "If the elder should not have lived there originally" -> -1.
    // This corresponds to c > initial_max (state at t=0).
    
    // Another detail: "INF" if condition never fails.
    
    // Let's code.

    // Map time to list of edge indices
    vector<pair<int, int>> meteor_events; // (time, edge_index)
    for (int i = 0; i < R; ++i) {
        meteor_events.push_back({meteors[i].t, meteors[i].p});
    }
    
    // Sort events by time? Not strictly needed if we group by time later, but good for ordering.
    // We need unique times sorted descending.
    vector<int> unique_times;
    // Use a map to group edges by time
    // Actually, we can just sort meteor_events by time descending.
    sort(meteor_events.begin(), meteor_events.end(), [](const pair<int,int>& a, const pair<int,int>& b){
        return a.first > b.first;
    });
    
    // Extract unique times in descending order
    for (int i = 0; i < R; ) {
        int t = meteor_events[i].first;
        unique_times.push_back(t);
        while(i < R && meteor_events[i].first == t) i++;
    }
    
    // Initialize DSU with never-destroyed edges
    DSU dsu(N);
    int current_max = 1; // Minimum component size is 1 (single node)
    if (N == 0) current_max = 0; // Edge case, though N is positive integer
    
    // Helper to update global max
    auto update_max = [&](int root) {
        if (dsu.sz[root] > current_max) {
            current_max = dsu.sz[root];
        }
    };

    // Add never-destroyed edges
    for (int i = 1; i <= E; ++i) {
        if (destroy_time[i] == -1) {
            if (dsu.unite(edges[i].u, edges[i].v)) {
                update_max(dsu.find(edges[i].u));
            }
        }
    }
    // Recalculate max just in case N>0 but no edges, max is 1.
    // The unite function updates current_max, but if no edges, current_max remains 1. Correct.
    // However, if we start with 1, and N=5, max is 1. Correct.
    // Wait, if we have edges, current_max grows.
    // But what if the initial max (with no edges) is 1, and we add edges, it grows.
    // Is it possible current_max is not updated correctly if we don't track all roots?
    // DSU unite updates the new root's size. We compare with global current_max.
    // This works because component sizes only grow in reverse process.
    
    // Store checkpoints: (time, max_size_at_this_time)
    // We traverse unique_times (descending).
    // Before adding edges of time t, the current state is the state AT time t.
    vector<pair<int, int>> checkpoints;
    
    for (int t : unique_times) {
        checkpoints.push_back({t, current_max});
        
        // Add all edges destroyed at time t
        // Find range in meteor_events
        // Since meteor_events is sorted descending by time, we can iterate.
        // But we need to be careful to process all edges with this t.
        // We can use a pointer or just re-scan? Better to use the sorted list.
        // Let's refactor the loop to use the sorted meteor_events directly.
    }
    
    // Refactoring the reverse simulation loop properly
    checkpoints.clear();
    // Reset DSU and current_max
    DSU dsu2(N);
    current_max = (N > 0 ? 1 : 0);
    
    // Add never-destroyed
    for (int i = 1; i <= E; ++i) {
        if (destroy_time[i] == -1) {
            if (dsu2.unite(edges[i].u, edges[i].v)) {
                if (dsu2.sz[dsu2.find(edges[i].u)] > current_max) {
                    current_max = dsu2.sz[dsu2.find(edges[i].u)];
                }
            }
        }
    }
    
    // Process events descending
    int idx = 0;
    int total_events = meteor_events.size();
    
    while (idx < total_events) {
        int t = meteor_events[idx].first;
        
        // Record state AT time t (before adding these edges back)
        checkpoints.push_back({t, current_max});
        
        // Add all edges with this time t
        while (idx < total_events && meteor_events[idx].first == t) {
            int edge_idx = meteor_events[idx].second;
            if (dsu2.unite(edges[edge_idx].u, edges[edge_idx].v)) {
                int root = dsu2.find(edges[edge_idx].u);
                if (dsu2.sz[root] > current_max) {
                    current_max = dsu2.sz[root];
                }
            }
            idx++;
        }
    }
    
    // Now current_max is the state at t < min_time (initial state)
    int initial_max = current_max;
    
    // Prepare answers
    // checkpoints are in descending time order. Reverse them for easier processing?
    // Or just search. We need the SMALLEST t such that size < c.
    // Since size decreases as t increases, the condition size < c will be false for small t, then become true.
    // Wait.
    // Time 0 -> t1 -> t2 ...
    // Size: S0 (largest) -> S1 -> S2 ... (smallest)
    // We want first t_i where S_i < c.
    // Our checkpoints: (t_k, S_k), (t_{k-1}, S_{k-1}), ..., (t_1, S_1).
    // Where S_k is size at t_k (smallest), S_1 is size at t_1.
    // Note: S_i corresponds to state AFTER t_i.
    // So if S_i < c, then at time t_i, the condition fails.
    // We want the smallest t_i.
    // In our list, t_1 is the last element. t_k is the first.
    // Sizes: S_k <= S_{k-1} <= ... <= S_1.
    // We look for the largest index in checkpoints (closest to end) where size < c?
    // No.
    // List: [(t_k, S_k), (t_{k-1}, S_{k-1}), ..., (t_1, S_1)]
    // Times: t_k > t_{k-1} > ... > t_1.
    // Sizes: S_k <= S_{k-1} <= ... <= S_1.
    // We want smallest t such that S(t) < c.
    // Since S is non-decreasing as we go backwards in time (or non-increasing forward),
    // If S_1 < c, then all S_i < c. Smallest t is t_1.
    // If S_1 >= c, check S_2...
    // Actually, since S_1 >= S_2 >= ... >= S_k.
    // If S_1 < c, then answer is t_1.
    // If S_1 >= c but S_2 < c, answer is t_2.
    // ...
    // If S_k < c, answer is t_k.
    // If S_k >= c, then never fails -> INF.
    // So we need to find the first element in the sequence S_1, S_2, ..., S_k that is < c?
    // No, S_1 is the largest. If S_1 < c, then all are < c.
    // We want the EARLIEST time.
    // Earliest time is t_1.
    // Condition fails at t_1 if S_1 < c.
    // If S_1 >= c, then t_1 is safe. Check t_2.
    // Fails at t_2 if S_2 < c.
    // So we iterate from t_1 to t_k (ascending time).
    // Our checkpoints are descending. So iterate from end to begin.
    
    // Reverse checkpoints to get ascending time
    reverse(checkpoints.begin(), checkpoints.end());
    // Now: [(t_1, S_1), (t_2, S_2), ..., (t_k, S_k)]
    // With t_1 < t_2 < ... < t_k
    // And S_1 >= S_2 >= ... >= S_k
    
    for (int i = 0; i < M; ++i) {
        int c = C[i];
        
        if (c > initial_max) {
            cout << -1 << "\n";
            continue;
        }
        
        int ans_time = -1;
        bool found = false;
        
        // Scan for first t where S < c
        for (auto& cp : checkpoints) {
            if (cp.second < c) {
                ans_time = cp.first;
                found = true;
                break;
            }
        }
        
        if (found) {
            cout << ans_time << "\n";
        } else {
            cout << "INF" << "\n";
        }
    }

    return 0;
}
