#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long p;
    while (cin >> p) {
        int n;
        if (!(cin >> n)) break;

        vector<long long> c(n);
        vector<long long> d(n);

        for (int i = 0; i < n; ++i) {
            cin >> c[i] >> d[i];
        }

        // Min-heap: pair<price, index>
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

        long long current_fuel = 0;
        long long total_cost = 0;

        for (int i = 0; i < n; ++i) {
            // Add current station's price to the heap
            pq.push({c[i], i});

            long long distance_needed = d[i];
            
            // If we don't have enough fuel to reach the next point
            if (current_fuel < distance_needed) {
                long long fuel_to_buy = distance_needed - current_fuel;
                
                while (fuel_to_buy > 0) {
                    if (pq.empty()) {
                        // Should not happen based on problem description assuming a solution exists
                        break;
                    }

                    pair<long long, int> cheapest = pq.top();
                    long long price = cheapest.first;
                    int idx = cheapest.second;

                    // Calculate how much fuel we can actually buy from this station
                    // Limited by: 
                    // 1. Fuel still needed (fuel_to_buy)
                    // 2. Tank capacity constraint relative to when we passed this station
                    //    We are currently at some point after station 'idx'.
                    //    The max fuel we could have had when leaving station 'idx' is p.
                    //    We need to track how much fuel we have already "virtually" bought from this station.
                    // A simpler greedy approach with priority queue for this specific problem:
                    // We treat it as: we buy fuel when we need it, looking back at the cheapest available station
                    // we have passed and haven't exhausted its potential contribution within tank limits.
                    
                    // However, the standard "tank capacity" constraint makes simple PQ tricky.
                    // Correct Logic:
                    // We maintain the fuel in the tank. When moving from i to i+1:
                    // 1. We consume d[i] fuel.
                    // 2. If fuel < 0, we must have bought more earlier.
                    // Instead, let's simulate forward:
                    // At each station, we fill up to full if the current price is the cheapest so far? No.
                    // Standard Greedy with PQ for "Refueling with costs":
                    // We push stations into PQ. When we need fuel, we pop the cheapest station.
                    // But we can only use a station's fuel if we could have reached it and carried it.
                    // Actually, a simpler view:
                    // We iterate through segments. We need d[i] fuel for segment i.
                    // We can "buy" this fuel from any station j <= i that we have passed, 
                    // provided that buying it doesn't violate the tank capacity constraint at the time we left j.
                    
                    // Let's refine the "virtual buying" strategy:
                    // We assume we start with 0 fuel.
                    // At station i, we add (price, i) to PQ.
                    // We need to cover distance d[i].
                    // We take fuel from the cheapest available station in PQ.
                    // Constraint: The amount of fuel bought from station j cannot exceed p minus the fuel 
                    // already in the tank when arriving at j? No.
                    // Constraint: At any point k, the total fuel bought from stations <= k minus total distance traveled <= p.
                    // This is equivalent to: Total fuel bought from stations in range [j, k] <= p + (distance traveled before j)? 
                    // Actually, the constraint is: Fuel_in_tank <= p at all times.
                    // Fuel_in_tank after leaving station i = (Total bought from 0..i) - (Total dist 0..i).
                    // So, (Total bought from 0..i) - (Total dist 0..i) <= p
                    // => Total bought from 0..i <= p + Total dist 0..i.
                    
                    // This looks like we can just buy greedily? 
                    // Wait, if we buy too much at a cheap station early, we might overflow the tank later?
                    // No, because we only buy when we *need* it (when fuel runs low).
                    // But we are looking back. 
                    // Correct Algorithm:
                    // Use a min-priority queue to store prices of stations we've passed.
                    // Maintain `current_fuel`.
                    // For each segment i with distance d[i]:
                    //   While current_fuel < d[i]:
                    //     If PQ is empty -> impossible (but problem implies possible).
                    //     Pop cheapest station (price, idx).
                    //     How much can we buy from this station?
                    //     We can buy up to 'p' units total from this station? No, station has infinite fuel.
                    //     Limit is tank capacity.
                    //     When we were at station `idx`, we could have filled up to `p`.
                    //     We need to track how much we have already "bought" from station `idx`.
                    //     Let `bought_from[idx]` be the amount.
                    //     Max we can buy from `idx` is `p`? No.
                    //     The constraint is: At the moment we leave station `idx`, fuel <= p.
                    //     Fuel leaving `idx` = (Fuel arriving at `idx`) + (Bought at `idx`).
                    //     This depends on future decisions if we do it backwards.
                    
                    // Let's try the forward simulation with "refunding" or simply the standard logic:
                    // "Buy fuel at the cheapest station seen so far whenever you need it."
                    // But we must ensure we didn't carry more than `p`.
                    // Actually, if we only buy when `current_fuel` is insufficient to reach the next station,
                    // and we "retroactively" buy from the cheapest past station, we must ensure that
                    // retroactive purchase was possible.
                    // It was possible if the total fuel accumulated from stations 0..k never exceeded p + dist(0..k).
                    // Since we only buy when necessary, we minimize the fuel carried.
                    // The only hard constraint is: We cannot buy more from station `j` than `p`? No.
                    // We cannot have more than `p` in the tank.
                    // If we buy 1 unit from station `j` to cover a gap at `k` (k > j), it means we carried that unit from j to k.
                    // This is valid only if carrying it didn't violate capacity at any point between j and k.
                    // Since we only buy when we run out, we are essentially keeping the tank as empty as possible.
                    // The only limitation is: We can't buy from `j` if we already bought enough from `j` such that 
                    // leaving `j` would have exceeded `p`.
                    // But since we buy incrementally only when needed, the "tank level" at `j` (in our retroactive model)
                    // is determined by how much we decided to buy from stations <= `j` to cover gaps up to current point.
                    // Actually, the standard solution for this problem is:
                    // Maintain a min-PQ of prices.
                    // Current fuel `fuel`.
                    // For each station i (and final destination):
                    //   Dist to next = d[i].
                    //   While fuel < d[i]:
                    //     Get min price from PQ.
                    //     Buy 1 unit (or bulk).
                    //     fuel++.
                    //     cost += price.
                    //   fuel -= d[i].
                    //   Push current station price to PQ.
                    // WAIT, this simple logic ignores the tank capacity `p` completely!
                    // If `p` is small, we might need to buy at an expensive station because we couldn't carry enough from a cheap one.
                    // Example: p=10. Station 0: $1, Station 1: $100 (dist 5), Station 2: $1 (dist 10 from 1).
                    // Path: 0 -> 1 (5km), 1 -> 2 (10km).
                    // At 0: Fill 10 ($10). Drive 5 to 1. Fuel=5.
                    // At 1: Need 10 to reach 2. Have 5. Need 5 more.
                    // Can we buy from 0? No, we already left 0. We could have bought max 10 at 0.
                    // If we bought 10 at 0, we arrive at 1 with 5. We can't get more from 0.
                    // So we MUST buy at 1.
                    // The simple PQ logic above would see $1 in PQ and try to buy from it, which is wrong because we can't carry more than p.
                    
                    // Correct Approach with Capacity:
                    // We need to track how much fuel we "took" from each station.
                    // But actually, we can model it as:
                    // At station i, we can fill up to p.
                    // Strategy:
                    // 1. If current price is the cheapest so far, fill the tank to full (if beneficial for future).
                    // 2. If not, just buy enough to reach the next cheaper station, or if none, enough to reach destination (or next stop if unavoidable).
                    // This is the "Monotonic Queue" or "Next Smaller Element" approach.
                    
                    // Algorithm:
                    // Find the next station `j` > `i` such that `c[j] < c[i]`.
                    // If such `j` exists:
                    //   We only need enough fuel to reach `j`.
                    //   Required fuel to reach `j` = dist(i, j).
                    //   If current_fuel >= dist(i, j), buy 0.
                    //   Else, buy (dist(i, j) - current_fuel).
                    //   Note: We can't buy more than `p` - current_fuel obviously, but since we only buy to reach `j`,
                    //   and `j` is reachable if the problem is solvable, and dist(i,j) might be > p?
                    //   If dist(i, j) > p, we can't reach `j` directly even with full tank.
                    //   In that case, we fill to full (`p`), drive to next station, and repeat.
                    // If no such `j` exists (current is cheapest till end):
                    //   We need enough to reach destination (or as far as possible).
                    //   Actually, if it's the cheapest, we should fill as much as needed to reach the end, bounded by `p`.
                    //   But wait, if we fill to `p`, we might carry too much if the remaining distance is small.
                    //   So: buy min(p - current_fuel, remaining_distance_to_end - current_fuel).
                    
                    // Refined Greedy:
                    // Iterate i from 0 to n-1.
                    // Calculate distance to next cheaper station `next_cheaper[i]`.
                    // Let `dist_to_target` be the distance to `next_cheaper[i]` if exists, else distance to end.
                    // However, if `dist_to_target` > `p`, we can't reach it in one go.
                    // In that case, we just fill to full (`p`) because the current station is the cheapest option for the next `p` distance.
                    // If `dist_to_target` <= `p`, we only buy enough to reach `target`.
                    
                    // Steps:
                    // 1. Precompute `next_cheaper` index for each station using a monotonic stack.
                    //    If no cheaper station ahead, mark as -1.
                    // 2. Simulate:
                    //    current_fuel = 0
                    //    total_cost = 0
                    //    For i = 0 to n-1:
                    //      If i > 0: 
                    //         travel from i-1 to i (dist d[i-1])
                    //         current_fuel -= d[i-1]
                    //      
                    //      Determine target distance:
                    //      If next_cheaper[i] exists (let idx = next_cheaper[i]):
                    //         dist_needed = sum(d[i] ... d[idx-1])
                    //      Else:
                    //         dist_needed = sum(d[i] ... d[n-1]) (total remaining)
                    //      
                    //      If dist_needed > p:
                    //         # Cannot reach the cheaper station (or end) in one tank.
                    //         # Since current is cheapest in range [i, i+range_covered_by_p], fill to full.
                    //         buy_amount = p - current_fuel
                    //      Else:
                    //         # Can reach target. Only buy what's needed to reach target.
                    //         buy_amount = dist_needed - current_fuel
                    //      
                    //      buy_amount = max(0LL, buy_amount)
                    //      # Also cannot exceed tank capacity (already handled by p - current_fuel logic above, but double check)
                    //      if (buy_amount > p - current_fuel) buy_amount = p - current_fuel; 
                    //         # Actually, if dist_needed > p, we set buy_amount = p - current_fuel.
                    //         # If dist_needed <= p, buy_amount = dist_needed - current_fuel.
                    //         # Since dist_needed <= p, then dist_needed - current_fuel <= p - current_fuel. Safe.
                    //
                    //      total_cost += buy_amount * c[i]
                    //      current_fuel += buy_amount
                    //
                    // Complexity: O(N) for next_cheaper, O(N) for simulation. Total O(N).
                    
                    // Implementation details:
                    // Prefix sums for distances to quickly calculate dist(i, j).
                    // prefix_dist[k] = sum(d[0]...d[k-1]). Distance from i to j (where j > i) is prefix_dist[j] - prefix_dist[i].
                    // Note: d[i] is dist from i to i+1.
                    // Location of station 0 = 0.
                    // Location of station k = sum(d[0]...d[k-1]).
                    // Destination = sum(d[0]...d[n-1]).
                    
                    break; // Break inner while, restructuring loop below
                }
            }
        }
        
        // Re-implementing cleanly inside the while(cin) loop
        
        vector<long long> prefix_dist(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_dist[i+1] = prefix_dist[i] + d[i];
        }
        
        // Next Cheaper Element
        vector<int> next_cheaper(n, -1);
        vector<int> st; // stack of indices
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && c[st.back()] >= c[i]) {
                st.pop_back();
            }
            if (!st.empty()) {
                next_cheaper[i] = st.back();
            }
            st.push_back(i);
        }
        
        long long fuel = 0;
        long long cost = 0;
        
        for (int i = 0; i < n; ++i) {
            // Arrive at station i (except i=0)
            if (i > 0) {
                fuel -= d[i-1];
            }
            
            // Calculate distance to target
            long long dist_to_target;
            if (next_cheaper[i] != -1) {
                // Distance from station i to station next_cheaper[i]
                // Location of next_cheaper[i] - Location of i
                dist_to_target = prefix_dist[next_cheaper[i]] - prefix_dist[i];
            } else {
                // Distance from station i to destination
                dist_to_target = prefix_dist[n] - prefix_dist[i];
            }
            
            long long buy = 0;
            if (dist_to_target > p) {
                // Can't reach target in one go, fill to full
                buy = p - fuel;
            } else {
                // Can reach target, buy just enough
                buy = dist_to_target - fuel;
            }
            
            if (buy < 0) buy = 0;
            if (buy > p - fuel) buy = p - fuel; // Safety cap
            
            cost += buy * c[i];
            fuel += buy;
        }
        
        cout << cost << "\n";
    }

    return 0;
}
