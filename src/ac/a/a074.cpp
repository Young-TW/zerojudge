#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;                 // scaled by 2
    bool operator<(const Point& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
};

struct Segment {
    int x1, y1, x2, y2;       // scaled endpoints
    int a, b, c;              // line: a*x + b*y = c
    int xmin, xmax, ymin, ymax;
};

int sgn(int v) { return (v > 0) - (v < 0); }

int dirOrder(int dx, int dy) {
    int sx = sgn(dx), sy = sgn(dy);
    if (sx == 1 && sy == 0) return 0;          // east
    if (sx == 1 && sy == 1) return 1;          // NE
    if (sx == 0 && sy == 1) return 2;          // north
    if (sx == -1 && sy == 1) return 3;         // NW
    if (sx == -1 && sy == 0) return 4;         // west
    if (sx == -1 && sy == -1) return 5;        // SW
    if (sx == 0 && sy == -1) return 6;         // south
    return 7;                                  // (1,-1) SE
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, N, K;
    while (cin >> M >> N >> K) {
        vector<Segment> segs;
        // rectangle borders
        auto addRect = [&](int x1,int y1,int x2,int y2){
            Segment s;
            s.x1 = 2*x1; s.y1 = 2*y1;
            s.x2 = 2*x2; s.y2 = 2*y2;
            if (s.x1 == s.x2) { // vertical
                s.a = 1; s.b = 0; s.c = s.x1;
            } else if (s.y1 == s.y2) { // horizontal
                s.a = 0; s.b = 1; s.c = s.y1;
            } else if ((s.y2 - s.y1) == (s.x2 - s.x1)) { // slope +1
                s.a = -1; s.b = 1; s.c = s.y1 - s.x1;
            } else { // slope -1
                s.a = 1; s.b = 1; s.c = s.y1 + s.x1;
            }
            s.xmin = min(s.x1, s.x2);
            s.xmax = max(s.x1, s.x2);
            s.ymin = min(s.y1, s.y2);
            s.ymax = max(s.y1, s.y2);
            segs.push_back(s);
        };
        addRect(0,0,M,0);
        addRect(0,N,M,N);
        addRect(0,0,0,N);
        addRect(M,0,M,N);
        // input lines
        for (int i=0;i<K;i++) {
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Segment s;
            s.x1 = 2*x1; s.y1 = 2*y1;
            s.x2 = 2*x2; s.y2 = 2*y2;
            if (s.x1 == s.x2) { // vertical
                s.a = 1; s.b = 0; s.c = s.x1;
            } else if (s.y1 == s.y2) { // horizontal
                s.a = 0; s.b = 1; s.c = s.y1;
            } else if ((s.y2 - s.y1) == (s.x2 - s.x1)) { // slope +1
                s.a = -1; s.b = 1; s.c = s.y1 - s.x1;
            } else { // slope -1
                s.a = 1; s.b = 1; s.c = s.y1 + s.x1;
            }
            s.xmin = min(s.x1, s.x2);
            s.xmax = max(s.x1, s.x2);
            s.ymin = min(s.y1, s.y2);
            s.ymax = max(s.y1, s.y2);
            segs.push_back(s);
        }

        // ----- collect all vertices -----
        map<pair<int,int>, int> idMap;
        vector<Point> points;
        auto addPoint = [&](int X,int Y){
            auto key = make_pair(X,Y);
            if (idMap.find(key)==idMap.end()){
                int id = (int)points.size();
                idMap[key]=id;
                points.push_back({X,Y});
            }
        };
        // endpoints
        for (auto &s: segs){
            addPoint(s.x1,s.y1);
            addPoint(s.x2,s.y2);
        }
        // intersections
        int S = (int)segs.size();
        for (int i=0;i<S;i++){
            for (int j=i+1;j<S;j++){
                long long a1=segs[i].a, b1=segs[i].b, c1=segs[i].c;
                long long a2=segs[j].a, b2=segs[j].b, c2=segs[j].c;
                long long D = a1*b2 - a2*b1;
                if (D==0) continue; // parallel or collinear
                long long X = (c1*b2 - c2*b1);
                long long Y = (a1*c2 - a2*c1);
                // D is ±1 or ±2, division yields integer
                if (X % D != 0 || Y % D != 0) continue; // should not happen
                X /= D; Y /= D;
                // check inside both bounding boxes
                if (X < segs[i].xmin || X > segs[i].xmax ||
                    Y < segs[i].ymin || Y > segs[i].ymax) continue;
                if (X < segs[j].xmin || X > segs[j].xmax ||
                    Y < segs[j].ymin || Y > segs[j].ymax) continue;
                addPoint((int)X,(int)Y);
            }
        }

        int V = (int)points.size();
        vector<vector<int>> adjSet(V);
        vector<unordered_set<int>> adjTmp(V); // to avoid duplicates

        // ----- create edges for each segment -----
        for (auto &s: segs){
            vector<pair<long long,int>> onSeg; // (t, vertex id)
            for (int vid=0; vid<V; ++vid){
                const Point& p = points[vid];
                if ((long long)s.a * p.x + (long long)s.b * p.y != s.c) continue;
                if (p.x < s.xmin || p.x > s.xmax || p.y < s.ymin || p.y > s.ymax) continue;
                int dx = sgn(s.x2 - s.x1);
                int dy = sgn(s.y2 - s.y1);
                long long t = (long long)(p.x - s.x1) * dx + (long long)(p.y - s.y1) * dy;
                onSeg.push_back({t, vid});
            }
            sort(onSeg.begin(), onSeg.end(),
                 [](const pair<long long,int>& a, const pair<long long,int>& b){
                     return a.first < b.first;
                 });
            for (size_t i=1;i<onSeg.size();++i){
                int u = onSeg[i-1].second;
                int v = onSeg[i].second;
                if (adjTmp[u].insert(v).second) adjSet[u].push_back(v);
                if (adjTmp[v].insert(u).second) adjSet[v].push_back(u);
            }
        }

        // ----- sort adjacency by direction order (CCW) -----
        for (int u=0; u<V; ++u){
            sort(adjSet[u].begin(), adjSet[u].end(),
                 [&](int a, int b){
                     int dx1 = points[a].x - points[u].x;
                     int dy1 = points[a].y - points[u].y;
                     int dx2 = points[b].x - points[u].x;
                     int dy2 = points[b].y - points[u].y;
                     return dirOrder(dx1,dy1) < dirOrder(dx2,dy2);
                 });
        }

        // ----- face walking -----
        unordered_set<long long> visited;
        long long triCnt = 0;
        for (int u=0; u<V; ++u){
            for (int v : adjSet[u]){
                long long code = ((long long)u<<32) | (unsigned int)v;
                if (visited.count(code)) continue;
                // start new face
                int start_u = u, start_v = v;
                int cur_u = u, cur_v = v;
                int len = 0;
                while (true){
                    visited.insert(((long long)cur_u<<32) | (unsigned int)cur_v);
                    ++len;
                    // find predecessor of cur_u in adjacency of cur_v
                    const vector<int>& neigh = adjSet[cur_v];
                    int deg = (int)neigh.size();
                    int idx = -1;
                    for (int i=0;i<deg;i++) if (neigh[i]==cur_u){ idx=i; break; }
                    int w = neigh[(idx - 1 + deg) % deg];
                    int next_u = cur_v;
                    int next_v = w;
                    cur_u = next_u;
                    cur_v = next_v;
                    if (cur_u==start_u && cur_v==start_v) break;
                }
                if (len==3) ++triCnt;
            }
        }

        cout << triCnt << "\n";
    }
    return 0;
}
