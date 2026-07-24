#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    bool isEndpoint = false;
    int nb[4];      // neighbor point id in direction 0:E,1:N,2:W,3:S
    int eid[4];     // directed edge id in that direction
    Point() {
        for (int i = 0; i < 4; ++i) nb[i] = eid[i] = -1;
    }
};

struct DirEdge {
    int from, to;
    long long len;
    int rev;    // reverse edge id
    int nxt;    // next edge id according to rule
};

int dirFromTo(const Point& a, const Point& b) {
    if (b.x > a.x) return 0;          // East
    if (b.y > a.y) return 1;          // North
    if (b.x < a.x) return 2;          // West
    return 3;                         // South
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long T;
    if (!(cin >> n >> T)) return 0;
    struct Seg {
        int x1, y1, x2, y2;
        bool vert;                 // true if vertical
        vector<int> pts;           // point ids on this segment
    };
    vector<Seg> segs(n);
    vector<Point> points;
    unordered_map<long long, int> mp;   // (x<<32)|y -> point id

    auto getPointId = [&](int x, int y, bool endpointFlag) -> int {
        long long key = ( (long long)x << 32 ) | (unsigned int)y;
        auto it = mp.find(key);
        if (it != mp.end()) {
            int id = it->second;
            if (endpointFlag) points[id].isEndpoint = true;
            return id;
        }
        int id = (int)points.size();
        Point p;
        p.x = x; p.y = y; p.isEndpoint = endpointFlag;
        points.push_back(p);
        mp[key] = id;
        return id;
    };

    for (int i = 0; i < n; ++i) {
        int bx, by, ex, ey;
        cin >> bx >> by >> ex >> ey;
        segs[i].x1 = bx; segs[i].y1 = by;
        segs[i].x2 = ex; segs[i].y2 = ey;
        segs[i].vert = (bx == ex);
        int id1 = getPointId(bx, by, true);
        int id2 = getPointId(ex, ey, true);
        segs[i].pts.push_back(id1);
        segs[i].pts.push_back(id2);
    }

    // compute intersections
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            const Seg& a = segs[i];
            const Seg& b = segs[j];
            if (a.vert == b.vert) continue; // both horiz or both vert -> never intersect per statement
            const Seg* v = a.vert ? &a : &b; // vertical
            const Seg* h = a.vert ? &b : &a; // horizontal
            int xv = v->x1;
            int yv1 = min(v->y1, v->y2), yv2 = max(v->y1, v->y2);
            int yh = h->y1;
            int xh1 = min(h->x1, h->x2), xh2 = max(h->x1, h->x2);
            if (xv >= xh1 && xv <= xh2 && yh >= yv1 && yh <= yv2) {
                // proper intersection (not at endpoints)
                int pid = getPointId(xv, yh, false);
                segs[i].pts.push_back(pid);
                segs[j].pts.push_back(pid);
            }
        }
    }

    // Build directed edges
    vector<DirEdge> edges;
    vector<int> revIdx; // temporary storage for reverse linking
    for (int i = 0; i < n; ++i) {
        Seg& s = segs[i];
        // sort points along the segment
        sort(s.pts.begin(), s.pts.end(), [&](int a, int b) {
            if (s.vert) return points[a].y < points[b].y;
            else return points[a].x < points[b].x;
        });
        // remove duplicates (possible if intersection coincides with endpoint, though problem says it doesn't)
        s.pts.erase(unique(s.pts.begin(), s.pts.end()), s.pts.end());
        for (size_t k = 0; k + 1 < s.pts.size(); ++k) {
            int u = s.pts[k];
            int v = s.pts[k + 1];
            long long len = (long long)abs(points[u].x - points[v].x) + (long long)abs(points[u].y - points[v].y);
            // direction u -> v
            int dir_uv = dirFromTo(points[u], points[v]);
            int dir_vu = (dir_uv + 2) % 4;
            int id1 = (int)edges.size();
            DirEdge e1; e1.from = u; e1.to = v; e1.len = len; e1.rev = -1; e1.nxt = -1;
            edges.push_back(e1);
            int id2 = (int)edges.size();
            DirEdge e2; e2.from = v; e2.to = u; e2.len = len; e2.rev = -1; e2.nxt = -1;
            edges.push_back(e2);
            edges[id1].rev = id2;
            edges[id2].rev = id1;
            // fill neighbor info
            points[u].nb[dir_uv] = v;
            points[u].eid[dir_uv] = id1;
            points[v].nb[dir_vu] = u;
            points[v].eid[dir_vu] = id2;
        }
    }

    // compute next edge for each directed edge
    for (size_t i = 0; i < edges.size(); ++i) {
        const DirEdge& e = edges[i];
        int dir = dirFromTo(points[e.from], points[e.to]); // direction of travel
        int v = e.to;
        if (points[v].isEndpoint) {
            edges[i].nxt = edges[i].rev; // bounce back
        } else {
            // left turn: (dx,dy) -> (-dy,dx)
            // direction order: 0:E,1:N,2:W,3:S ; left turn is +1 mod 4
            int left_dir = (dir + 1) % 4;
            int nxtEdge = points[v].eid[left_dir];
            // safety check (should exist)
            edges[i].nxt = nxtEdge;
        }
    }

    // start edge
    int startPt = getPointId(segs[0].x1, segs[0].y1, true); // bx1,by1
    int otherPt = getPointId(segs[0].x2, segs[0].y2, true);
    int startDir = dirFromTo(points[startPt], points[otherPt]);
    int startEdge = points[startPt].eid[startDir];
    // simulation to find cycle
    vector<int> firstIdx(edges.size(), -1);
    vector<long long> cumTime; // start time of each visited edge
    vector<int> edgeSeq;
    long long curTime = 0;
    int curEdge = startEdge;
    while (firstIdx[curEdge] == -1) {
        firstIdx[curEdge] = (int)edgeSeq.size();
        edgeSeq.push_back(curEdge);
        cumTime.push_back(curTime);
        curTime += edges[curEdge].len;
        curEdge = edges[curEdge].nxt;
    }
    int cycle_start_idx = firstIdx[curEdge];
    long long cycle_start_time = cumTime[cycle_start_idx];
    long long cycle_len = curTime - cycle_start_time;

    long long query = T;
    if (query >= curTime) {
        if (cycle_len == 0) { // should not happen
            query = curTime - 1;
        } else {
            long long offset = (query - cycle_start_time) % cycle_len;
            query = cycle_start_time + offset;
        }
    }

    // locate edge
    int idx = (int)(upper_bound(cumTime.begin(), cumTime.end(), query) - cumTime.begin()) - 1;
    int eId = edgeSeq[idx];
    long long offsetAlong = query - cumTime[idx];
    const DirEdge& e = edges[eId];
    const Point& A = points[e.from];
    const Point& B = points[e.to];
    int x = A.x, y = A.y;
    if (B.x != A.x) {
        if (B.x > A.x) x += (int)offsetAlong;
        else x -= (int)offsetAlong;
    } else {
        if (B.y > A.y) y += (int)offsetAlong;
        else y -= (int)offsetAlong;
    }
    cout << x << ' ' << y << '\n';
    return 0;
}
