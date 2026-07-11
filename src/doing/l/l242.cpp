#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

struct State {
    int u; // current station index
    int cost;
    int bus_idx; // index of the bus we are currently on (-1 if not on any bus, or just started)
    int prev_u; // previous station index in the path
    int prev_bus_idx; // previous bus index used to get to u
    
    // For reconstruction: we need to know the sequence of (bus, stations)
    // Let's store the path differently.
};

// We will model the problem as a graph where nodes are stations.
// However, the cost depends on whether we switch buses.
// Actually, the cost is simply the number of stops traveled.
// "每個站一元" -> Cost = number of edges traversed? 
// Let's re-read carefully: "車費計算方式：每個站一元"
// Example 1: 
// Route: school -> home -> park (Bus 12). Stops: school(0), home(1), park(2). 
// Then park -> museum (Bus 5). Stops: park(0), museum(1).
// Total stops traveled: (school->home, home->park) = 2 stops? Or is it number of stations visited excluding start?
// Output says 3.
// Path: school -> home -> park -> museum.
// Stations visited: school, home, park, museum.
// If cost is 3, it implies cost = number of edges (transitions).
// school->home (1), home->park (1), park->museum (1). Total 3.
// So cost is the number of hops.

// But wait, the output format requires grouping by bus.
// "12 school home park" means we took bus 12 from school to park, passing home.
// "5 park museum" means we took bus 5 from park to museum.
// The cost is the total number of stops (hops).

// We need to find the path with minimum hops.
// If there are multiple paths with same minimum hops, the problem doesn't explicitly specify tie-breaking rules other than "least fare".
// However, usually in such problems, any valid shortest path is accepted, or there's an implicit lexicographical order.
// Looking at the failed example: 
// Expected: 12 school home park \n 5 park museum \n 3
// Actual (wrong): 2 library park museum ...
// The wrong answer suggests the previous code found a different path or calculated cost wrongly.
// Let's trace the example manually.
// Buses:
// 0: 12 [school, home, park]
// 1: 5 [library, park, museum]
// 2: 2 [beach, library, museum]
// Start: school, End: museum.
// Graph edges (undirected? Bus routes are usually bidirectional for fare calculation unless specified "order". 
// The problem says "經過的站的順序", which implies directionality? 
// But typically in these problems, you can go back and forth on the same bus line without extra penalty other than distance.
// However, "順序" might imply the bus only goes one way. Let's assume directed first? 
// But if I'm at 'park' and want to go to 'home', can I take bus 12? 
// If the bus goes school->home->park, can I board at park? Usually no, unless it's a two-way street or the bus returns.
// BUT, looking at the sample: school -> ... -> park -> ... -> museum.
// school to park is forward on bus 12. park to museum is forward on bus 5.
// What if I needed to go park -> school? 
// Let's assume the connections are undirected for simplicity unless the path fails. 
// Actually, standard interpretation for "bus route order" in competitive programming often allows travel in both directions along the route segments, OR it strictly follows the sequence.
// Given "順序", strict direction is safer? 
// Let's check connectivity: school->home->park. If directed, I can go school->park. Cannot go park->school.
// If undirected, I can go both ways.
// Let's assume undirected edges between consecutive stations on a bus route. Why? Because usually "bus line" implies connectivity between adjacent stops regardless of direction for the purpose of "minimum fare" unless it's a specific "one-way" problem. 
// However, the phrase "順序" (sequence) is strong. 
// Let's look at the sample again. 
// school -> home -> park (Bus 12). 
// library -> park -> museum (Bus 5).
// beach -> library -> museum (Bus 2).
// Target: school to museum.
// Path 1: school -> home -> park (Bus 12, 2 hops). At park, switch to Bus 5. park -> museum (Bus 5, 1 hop). Total 3 hops.
// Path 2: Is there another? 
// school is only on Bus 12. Must start with 12.
// From park, can go to museum (Bus 5) or home (back).
// If I go to library via some other way? No direct link from school/park/home to library except via park.
// So the path seems unique in terms of stations: school-home-park-museum.
// The issue with the previous failed output "2 library park museum" suggests the code might have started from the wrong place or found a path from library? 
// Ah, the input was "school,museum". The failed output started with Bus 2 which doesn't even contain 'school'. That was a major bug in the previous logic (probably parsing or start node identification).

// Algorithm:
// 1. Parse input. Map station names to IDs. Store bus routes as list of station IDs.
// 2. Build a graph where nodes are stations. Edges exist between consecutive stations in a bus route.
//    Since we need to reconstruct the path with bus numbers, we should store which bus connects two stations.
//    Note: Two stations might be connected by multiple buses.
//    Edge: (u, v) with bus_id.
//    Is it directed? Let's assume undirected for now. If the problem implies strict direction, we might fail, but usually "minimum fare" implies physical connectivity. 
//    Wait, if it's directed, school->park works. park->school doesn't. 
//    Let's assume undirected. If the bus goes A->B->C, you can travel A-B, B-C. Can you travel C-B? In real life, yes (same line, opposite direction). In strict "sequence" problems, maybe not. 
//    Given the sample doesn't test reverse, and typical CP bus problems treat lines as undirected graphs of stops, I'll use undirected.
// 3. BFS to find shortest path (minimum hops) from start to end.
//    State in BFS: current station.
//    We need to reconstruct the path. Since multiple buses can connect u and v, we need to store which bus was used.
//    dist[u] = minimum hops to reach u.
//    parent[u] = {prev_station, bus_id_used_to_come_from_prev}
// 4. Reconstruct path:
//    Trace back from end to start using parent pointers.
//    This gives a list of segments: (u, v, bus_id).
//    Reverse to get start->end.
//    Merge consecutive segments with the same bus_id into one line of output.
//    Calculate total cost (number of hops).

// Data structures:
// map<string, int> nameToId;
// vector<string> idToName;
// struct Edge { int to; int busIdx; };
// vector<vector<Edge>> adj;
// Bus info: vector<pair<int, vector<int>>> buses; // busId (original string converted to int index?), original string needed for output.
// Actually, store original bus number string in a vector `busNumbers`.

// Parsing details:
// First line T.
// Next T lines: "BusNum s1 s2 s3 ..."
// Last line: "start,end"

// Corner cases:
// - Start == End: Cost 0? Output format? Probably just the station? Or nothing then 0? 
//   Problem says "route". If start==end, maybe no bus needed. But let's assume start != end based on context.
// - Disconnected: Problem implies a solution exists.
// - Multiple shortest paths: Any is fine? Or lexicographically smallest bus number? 
//   The problem doesn't specify. We'll pick the first one found by BFS (which depends on insertion order). 
//   To be deterministic and potentially match judge expectations, we might want to sort neighbors? 
//   But without explicit rules, standard BFS order is usually acceptable. 
//   However, the sample output uses Bus 12 then Bus 5. 
//   If there was a choice, maybe smaller bus number? 
//   Let's try to prioritize smaller bus number or lexicographical station name if costs are equal? 
//   Standard BFS finds the shortest path. If multiple, the one discovered first. 
//   We iterate buses in input order. 
//   Let's stick to simple BFS.

// Reconstruction logic:
// Path: s0 -(b0)-> s1 -(b0)-> s2 -(b1)-> s3 ...
// Group by bus: 
// b0: s0, s1, s2
// b1: s2, s3 ...
// Note: The station where we switch (s2) appears in both lines? 
// Sample output: 
// 12 school home park
// 5 park museum
// Yes, 'park' is the last stop of bus 12 and first stop of bus 5.

// Implementation steps:
// 1. Read T. Loop T times to read bus lines.
// 2. Read start, end.
// 3. Build graph.
// 4. BFS.
// 5. Reconstruct and print.

// Important: The bus number is a string (could be "12", "5", "A1", etc.).
// Station names are strings.

// Complexity: 
// V = number of unique stations. E = sum of (stops per bus - 1) * 2 (undirected).
// BFS is O(V+E). This is efficient enough.

// One detail: "車站可能有很多個".
// Input format: "巴士號碼 車站..."
// We need to parse line by line.

// Let's code.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

struct Edge {
    int to;
    int busIdx; // index in the buses vector
};

int main() {
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;
    
    // Consume the newline after T
    string dummy;
    getline(cin, dummy); 

    vector<string> busNumbers;
    vector<vector<int>> busRoutes;
    map<string, int> stationToId;
    vector<string> idToStation;
    auto getStationId = [&](const string& s) {
        if (stationToId.find(s) == stationToId.end()) {
            stationToId[s] = idToStation.size();
            idToStation.push_back(s);
        }
        return stationToId[s];
    };

    for (int i = 0; i < T; ++i) {
        string line;
        getline(cin, line);
        if (line.empty()) {
            // Handle potential empty lines if any
            i--; 
            continue;
        }
        stringstream ss(line);
        string busNum;
        ss >> busNum;
        busNumbers.push_back(busNum);
        
        vector<int> route;
        string station;
        while (ss >> station) {
            route.push_back(getStationId(station));
        }
        busRoutes.push_back(route);
    }

    string startEndLine;
    getline(cin, startEndLine);
    // Parse "start,end"
    size_t commaPos = startEndLine.find(',');
    string startStr = startEndLine.substr(0, commaPos);
    string endStr = startEndLine.substr(commaPos + 1);

    // Trim possible whitespace (though problem format suggests tight packing)
    // Just in case
    auto trim = [](string& s) {
        size_t first = s.find_first_not_of(" \t\r\n");
        if (first == string::npos) return;
        size_t last = s.find_last_not_of(" \t\r\n");
        s = s.substr(first, (last - first + 1));
    };
    trim(startStr);
    trim(endStr);

    if (stationToId.find(startStr) == stationToId.end() || stationToId.find(endStr) == stationToId.end()) {
        // Should not happen based on problem description
        return 0;
    }

    int startNode = stationToId[startStr];
    int endNode = stationToId[endStr];

    if (startNode == endNode) {
        cout << 0 << endl;
        return 0;
    }

    int N = idToStation.size();
    vector<vector<Edge>> adj(N);

    // Build graph (undirected)
    for (int i = 0; i < (int)busRoutes.size(); ++i) {
        const vector<int>& route = busRoutes[i];
        for (size_t j = 0; j + 1 < route.size(); ++j) {
            int u = route[j];
            int v = route[j+1];
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }
    }

    // BFS
    vector<int> dist(N, -1);
    vector<int> parentStation(N, -1);
    vector<int> parentBus(N, -1); // Bus index used to reach this node from parentStation

    queue<int> q;
    q.push(startNode);
    dist[startNode] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == endNode) break;

        // Sort neighbors to ensure deterministic behavior? 
        // Not strictly required but good for debugging. 
        // However, sorting by bus index or station name might help if multiple shortest paths exist.
        // Let's just iterate. The order of adding edges is based on input order.
        
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parentStation[v] = u;
                parentBus[v] = edge.busIdx;
                q.push(v);
            }
        }
    }

    if (dist[endNode] == -1) {
        // No path found
        return 0;
    }

    // Reconstruct path
    // Path is a list of steps: (from, to, busIdx)
    // We backtrack from endNode to startNode
    struct Step {
        int from;
        int to;
        int busIdx;
    };
    vector<Step> pathSteps;
    
    int curr = endNode;
    while (curr != startNode) {
        int prev = parentStation[curr];
        int bIdx = parentBus[curr];
        pathSteps.push_back({prev, curr, bIdx});
        curr = prev;
    }
    reverse(pathSteps.begin(), pathSteps.end());

    // Group by bus
    // Output format:
    // BusNum s1 s2 ... sk
    // NextBusNum sk ... sm
    // ...
    // Total Cost

    if (pathSteps.empty()) {
        cout << 0 << endl;
        return 0;
    }

    int totalCost = dist[endNode];
    
    // Iterate through steps and group
    int i = 0;
    while (i < (int)pathSteps.size()) {
        int currentBus = pathSteps[i].busIdx;
        cout << busNumbers[currentBus];
        
        // Print the starting station of this segment
        cout << " " << idToStation[pathSteps[i].from];
        
        // Continue while the bus is the same
        int j = i;
        while (j < (int)pathSteps.size() && pathSteps[j].busIdx == currentBus) {
            cout << " " << idToStation[pathSteps[j].to];
            j++;
        }
        cout << "\n";
        
        i = j;
    }
    
    cout << totalCost << endl;

    return 0;
}
