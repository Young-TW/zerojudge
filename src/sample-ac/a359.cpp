#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <climits>

using namespace std;

struct Rect {
    int x1, y1, x2, y2;
};

struct State {
    int x, y, dir; // dir: 0=N, 1=E, 2=S, 3=W
    long long dist;
    
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

// Directions: N, E, S, W
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool isInside(int x, int y, const Rect& r) {
    return x > r.x1 && x < r.x2 && y > r.y1 && y < r.y2;
}

bool isOnBoundary(int x, int y, const Rect& r) {
    if (x == r.x1 || x == r.x2) {
        if (y >= r.y1 && y <= r.y2) return true;
    }
    if (y == r.y1 || y == r.y2) {
        if (x >= r.x1 && x <= r.x2) return true;
    }
    return false;
}

bool canTurn(int x, int y, const vector<Rect>& rects) {
    // Can turn at start/end points implicitly handled by logic
    // Can turn on corners or edges of hives
    for (const auto& r : rects) {
        if (isOnBoundary(x, y, r)) return true;
    }
    return false;
}

bool isValidPoint(int x, int y, const vector<Rect>& rects) {
    for (const auto& r : rects) {
        if (isInside(x, y, r)) return false;
    }
    return true;
}

long long solve() {
    int xs, ys, xt, yt;
    if (!(cin >> xs >> ys >> xt >> yt)) return -1;
    
    int n;
    cin >> n;
    vector<Rect> rects(n);
    for (int i = 0; i < n; ++i) {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        if (rects[i].x1 > rects[i].x2) swap(rects[i].x1, rects[i].x2);
        if (rects[i].y1 > rects[i].y2) swap(rects[i].y1, rects[i].y2);
    }

    // Check if start or end is inside a hive
    if (!isValidPoint(xs, ys, rects) || !isValidPoint(xt, yt, rects)) {
        return -1; 
    }

    // Coordinate compression not strictly needed if we only visit critical points
    // But the grid can be large, so we must use Dijkstra on "events"
    // Critical X coordinates: xs, xt, and all hive x1-1, x1, x2, x2+1
    // Critical Y coordinates: ys, yt, and all hive y1-1, y1, y2, y2+1
    
    vector<int> critX, critY;
    critX.push_back(xs); critX.push_back(xt);
    critY.push_back(ys); critY.push_back(yt);
    
    for (const auto& r : rects) {
        critX.push_back(r.x1 - 1); critX.push_back(r.x1);
        critX.push_back(r.x2); critX.push_back(r.x2 + 1);
        critY.push_back(r.y1 - 1); critY.push_back(r.y1);
        critY.push_back(r.y2); critY.push_back(r.y2 + 1);
    }
    
    sort(critX.begin(), critX.end());
    critX.erase(unique(critX.begin(), critX.end()), critX.end());
    sort(critY.begin(), critY.end());
    critY.erase(unique(critY.begin(), critY.end()), critY.end());

    map<pair<int, int>, int> xMap, yMap;
    for (int i = 0; i < (int)critX.size(); ++i) xMap[{critX[i], 0}] = i; // dummy val
    for (int i = 0; i < (int)critY.size(); ++i) yMap[{critY[i], 0}] = i;

    // We need to map coordinate to index quickly
    auto getXIdx = [&](int x) -> int {
        auto it = lower_bound(critX.begin(), critX.end(), x);
        return (int)(it - critX.begin());
    };
    auto getYIdx = [&](int y) -> int {
        auto it = lower_bound(critY.begin(), critY.end(), y);
        return (int)(it - critY.begin());
    };

    int startX = xs, startY = ys;
    int targetX = xt, targetY = yt;
    
    int NX = critX.size();
    int NY = critY.size();
    
    // Dist[x_idx][y_idx][dir]
    // Using a flat vector might be too big if NX*NY is large? 
    // Constraints: T<=20, N hives? Usually small in such problems. 
    // Max critical points ~ 4*N + 2. If N=100, NX~400. 400*400*4 = 640k states. OK.
    
    // Let's use a map for sparse storage or a flattened vector if size permits.
    // Given typical competitive programming constraints for this type of problem, N is likely <= 50 or 100.
    // Let's assume worst case N=200 -> 800 coords -> 640000 * 4 * 8 bytes ~ 20MB. Acceptable.
    
    // However, we only care about points that are on the "grid lines" formed by critical coords?
    // Actually, movement is continuous along lines. We only stop at critical coordinates.
    // So nodes are (cx, cy) where cx in critX, cy in critY.
    
    // Initialize distances
    // Use a 3D array: dist[NX][NY][4]
    // Since NX, NY dynamic, use vector
    vector<vector<vector<long long>>> dist(NX, vector<vector<long long>>(NY, vector<long long>(4, -1)));
    
    priority_queue<State, vector<State>, greater<State>> pq;
    
    int sx = getXIdx(startX);
    int sy = getYIdx(startY);
    
    // Start can go in any direction
    for (int d = 0; d < 4; ++d) {
        dist[sx][sy][d] = 0;
        pq.push({startX, startY, d, 0});
    }
    
    long long ans = -1;
    
    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        
        int cx = cur.x;
        int cy = cur.y;
        int cd = cur.dir;
        long long cdist = cur.dist;
        
        int cxi = getXIdx(cx);
        int cyi = getYIdx(cy);
        
        if (cdist != dist[cxi][cyi][cd]) continue;
        
        if (cx == targetX && cy == targetY) {
            ans = cdist;
            break;
        }
        
        // Move forward
        int nx = cx + dx[cd];
        int ny = cy + dy[cd];
        
        // Check if next critical point in this direction is valid
        // We jump to the next critical coordinate in the current direction
        if (cd == 0) { // North (+y)
            // Find next y in critY greater than cy
            auto it = upper_bound(critY.begin(), critY.end(), cy);
            if (it != critY.end()) {
                ny = *it;
                // Check segment (cx, cy) to (cx, ny) for obstacles
                // Obstacles are open intervals (x1, x2) x (y1, y2).
                // Since we are moving on x=cx (critical), we only hit if cx is inside (r.x1, r.x2)
                // and the segment overlaps (r.y1, r.y2).
                bool blocked = false;
                for (const auto& r : rects) {
                    if (cx > r.x1 && cx < r.x2) {
                        // Check overlap in Y: (cy, ny) vs (r.y1, r.y2)
                        // Since ny is the next critical point, and r.y1, r.y2 are critical,
                        // the segment (cy, ny) might be exactly (r.y1, r.y2) or part of it?
                        // Actually, if we move from cy to ny, and there is a rect with y1, y2 in between?
                        // No, because critY includes r.y1 and r.y2. So the step goes from one critical Y to adjacent critical Y.
                        // The segment is (cy, ny). The rect interior is (r.y1, r.y2).
                        // If cy >= r.y1 and ny <= r.y2, then the whole segment is inside?
                        // Wait, if cy == r.y1 and ny == r.y2, the segment is the boundary? No, interior is open.
                        // Movement is allowed on boundary. Blocked only if strictly inside.
                        // So if cy >= r.y1 and ny <= r.y2, we are moving along the edge or inside?
                        // If cx is strictly inside (r.x1, r.x2), then:
                        //   if y in (r.y1, r.y2) -> blocked.
                        //   if y == r.y1 or y == r.y2 -> allowed (boundary).
                        // Our step is from cy to ny. These are adjacent in critY.
                        // So the interval (min(cy,ny), max(cy,ny)) contains no critical points.
                        // Thus it cannot contain r.y1 or r.y2 strictly inside.
                        // So either the segment is completely outside, or completely inside, or on boundary?
                        // If cy == r.y1 and ny == r.y2? Impossible if there are other points? 
                        // Actually, if rect is (2, 5, 3, 8). critY has 5, 8. Step 5->8.
                        // cx=2.5? No, cx must be integer. But input coords are integers.
                        // If cx=2 (boundary), allowed. If cx=3 (boundary), allowed. If cx=2.5 impossible.
                        // If cx is integer and r.x1 < cx < r.x2. e.g. r=(1, 5, 3, 8). cx=2.
                        // Then moving y from 5 to 8. Interior y in (5, 8).
                        // The segment (5, 8) includes 6, 7 which are inside.
                        // So we must check if the OPEN segment (cy, ny) intersects (r.y1, r.y2).
                        // Since cy and ny are consecutive critical points, and r.y1, r.y2 are critical,
                        // the only way to intersect is if cy == r.y1 and ny == r.y2? 
                        // Or if the rect spans multiple critical intervals? 
                        // But we are stepping one critical interval at a time.
                        // So if cy == r.y1 and ny == r.y2, then the open segment (cy, ny) is (r.y1, r.y2).
                        // All points in (r.y1, r.y2) are inside the rect. So blocked.
                        if (cy == r.y1 && ny == r.y2) {
                            blocked = true;
                            break;
                        }
                    }
                }
                
                if (!blocked) {
                    long long ndist = cdist + abs(ny - cy);
                    int nxi = cxi;
                    int nyi = getYIdx(ny);
                    
                    if (dist[nxi][nyi][cd] == -1 || ndist < dist[nxi][nyi][cd]) {
                        dist[nxi][nyi][cd] = ndist;
                        pq.push({nx, ny, cd, ndist});
                    }
                }
            }
        } else if (cd == 2) { // South (-y)
            auto it = lower_bound(critY.begin(), critY.end(), cy);
            if (it != critY.begin()) {
                --it;
                ny = *it;
                bool blocked = false;
                for (const auto& r : rects) {
                    if (cx > r.x1 && cx < r.x2) {
                        if (ny == r.y1 && cy == r.y2) {
                            blocked = true;
                            break;
                        }
                    }
                }
                if (!blocked) {
                    long long ndist = cdist + abs(ny - cy);
                    int nxi = cxi;
                    int nyi = getYIdx(ny);
                    if (dist[nxi][nyi][cd] == -1 || ndist < dist[nxi][nyi][cd]) {
                        dist[nxi][nyi][cd] = ndist;
                        pq.push({nx, ny, cd, ndist});
                    }
                }
            }
        } else if (cd == 1) { // East (+x)
            auto it = upper_bound(critX.begin(), critX.end(), cx);
            if (it != critX.end()) {
                nx = *it;
                bool blocked = false;
                for (const auto& r : rects) {
                    if (cy > r.y1 && cy < r.y2) {
                        if (cx == r.x1 && nx == r.x2) {
                            blocked = true;
                            break;
                        }
                    }
                }
                if (!blocked) {
                    long long ndist = cdist + abs(nx - cx);
                    int nxi = getXIdx(nx);
                    int nyi = cyi;
                    if (dist[nxi][nyi][cd] == -1 || ndist < dist[nxi][nyi][cd]) {
                        dist[nxi][nyi][cd] = ndist;
                        pq.push({nx, ny, cd, ndist});
                    }
                }
            }
        } else if (cd == 3) { // West (-x)
            auto it = lower_bound(critX.begin(), critX.end(), cx);
            if (it != critX.begin()) {
                --it;
                nx = *it;
                bool blocked = false;
                for (const auto& r : rects) {
                    if (cy > r.y1 && cy < r.y2) {
                        if (nx == r.x1 && cx == r.x2) {
                            blocked = true;
                            break;
                        }
                    }
                }
                if (!blocked) {
                    long long ndist = cdist + abs(nx - cx);
                    int nxi = getXIdx(nx);
                    int nyi = cyi;
                    if (dist[nxi][nyi][cd] == -1 || ndist < dist[nxi][nyi][cd]) {
                        dist[nxi][nyi][cd] = ndist;
                        pq.push({nx, ny, cd, ndist});
                    }
                }
            }
        }
        
        // Turn?
        // Can turn if current point is on boundary of some rect OR start point (handled by init)
        // Actually, rule: "只能在蜂巢的角或者边上改变飞行方向"
        // Start point: "开始的时候可以向任何方向飞" -> implies we can start turning immediately?
        // But once moving, we can only turn at boundaries.
        // Is the start point considered a valid turning point if not on boundary?
        // "开始的时候可以向任何方向飞" means initial state has all dirs.
        // From a state (x,y,dir), can we switch to (x,y,new_dir)?
        // Only if (x,y) is on boundary.
        // Exception: Start node. But we already pushed all 4 dirs for start node with dist 0.
        // So we don't need to "turn" at start node in the graph search, we just explore all.
        // What if we return to start node later? Then we must obey boundary rule.
        
        if (canTurn(cx, cy, rects) || (cx == startX && cy == startY)) {
             // Try changing direction
             for (int nd = 0; nd < 4; ++nd) {
                 if (nd == cd) continue;
                 if (dist[cxi][cyi][nd] == -1 || cdist < dist[cxi][cyi][nd]) {
                     dist[cxi][cyi][nd] = cdist;
                     pq.push({cx, cy, nd, cdist});
                 }
             }
        }
    }
    
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            long long result = solve();
            if (result == -1) {
                cout << "No Path" << "\n";
            } else {
                cout << result << "\n";
            }
            
            // Consume empty line if present? 
            // The problem says "adjacent groups separated by empty line".
            // Standard cin >> skips whitespace, so no need to manually consume.
        }
    }
    return 0;
}
