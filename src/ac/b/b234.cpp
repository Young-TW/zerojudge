#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    bool operator==(const Point& o) const {
        return fabs(x - o.x) < EPS && fabs(y - o.y) < EPS;
    }
};

inline Point operator+(const Point& a, const Point& b){ return {a.x+b.x, a.y+b.y}; }
inline Point operator-(const Point& a, const Point& b){ return {a.x-b.x, a.y-b.y}; }
inline Point operator*(const Point& a, double k){ return {a.x*k, a.y*k}; }

inline double cross(const Point& a, const Point& b){ return a.x*b.y - a.y*b.x; }
inline double dot  (const Point& a, const Point& b){ return a.x*b.x + a.y*b.y; }

bool segment_intersection(const Point& a, const Point& b,
                          const Point& c, const Point& d,
                          Point& out)
{
    Point r = b - a;
    Point s = d - c;
    double rxs = cross(r, s);
    if (fabs(rxs) < EPS) return false;               // parallel (ignore collinear)
    Point ca = c - a;
    double t = cross(ca, s) / rxs;
    double u = cross(ca, r) / rxs;
    if (t < -EPS || t > 1.0 + EPS) return false;
    if (u < -EPS || u > 1.0 + EPS) return false;
    out = a + r * t;
    return true;
}

/***  half‑edge structure ***/
struct Half {
    int origin;   // vertex id
    int to;       // vertex id
    int rev;      // index of twin half‑edge
    int next;     // next half‑edge along left face
    int face;     // face id (-1 = not visited)
    double angle; // atan2(to - origin)
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int K;
    if (!(cin >> K)) return 0;
    while (K--) {
        int n;
        cin >> n;
        vector<Point> P(n);
        for (int i = 0; i < n; ++i) cin >> P[i].x >> P[i].y;

        /* ---------- 1. collect points on each original segment ---------- */
        struct SegInfo {
            Point a, b;
            vector<Point> pts;
        };
        vector<SegInfo> segs(n);
        for (int i = 0; i < n; ++i) {
            segs[i].a = P[i];
            segs[i].b = P[(i + 1) % n];
            segs[i].pts.clear();
            segs[i].pts.push_back(segs[i].a);
            segs[i].pts.push_back(segs[i].b);
        }

        // all intersections
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                Point ip;
                if (segment_intersection(segs[i].a, segs[i].b,
                                         segs[j].a, segs[j].b, ip)) {
                    segs[i].pts.push_back(ip);
                    segs[j].pts.push_back(ip);
                }
            }
        }

        /* ---------- 2. split each segment, store raw points ---------- */
        struct EdgeRaw { int aIdx, bIdx; };
        vector<Point> rawPoints;          // every occurrence
        vector<EdgeRaw> rawEdges;          // each edge piece

        for (int i = 0; i < n; ++i) {
            Point a = segs[i].a, b = segs[i].b;
            Point dir = b - a;
            double len2 = dot(dir, dir);
            auto &v = segs[i].pts;
            sort(v.begin(), v.end(),
                 [&](const Point& p1, const Point& p2) {
                     double t1 = dot(p1 - a, dir) / len2;
                     double t2 = dot(p2 - a, dir) / len2;
                     return t1 < t2;
                 });
            // remove duplicates on this segment
            vector<Point> uniq;
            for (auto &p : v) {
                if (uniq.empty() || !(p == uniq.back())) uniq.push_back(p);
            }
            for (size_t k = 0; k + 1 < uniq.size(); ++k) {
                int idx1 = (int)rawPoints.size(); rawPoints.push_back(uniq[k]);
                int idx2 = (int)rawPoints.size(); rawPoints.push_back(uniq[k+1]);
                rawEdges.push_back({idx1, idx2});
            }
        }

        /* ---------- 3. deduplicate vertices ---------- */
        int R = (int)rawPoints.size();
        vector<int> order(R);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(),
             [&](int i, int j){
                 if (fabs(rawPoints[i].x - rawPoints[j].x) > EPS)
                     return rawPoints[i].x < rawPoints[j].x;
                 return rawPoints[i].y < rawPoints[j].y - EPS;
             });
        vector<Point> uniqV;
        vector<int> pointId(R, -1);
        for (int idx : order) {
            if (uniqV.empty() || !(rawPoints[idx] == uniqV.back())) {
                uniqV.push_back(rawPoints[idx]);
            }
            pointId[idx] = (int)uniqV.size() - 1;
        }
        int V = (int)uniqV.size();

        /* ---------- 4. build half‑edges ---------- */
        vector<Half> halfs;
        vector<vector<int>> out(V);          // outgoing half‑edge indices
        for (auto &e : rawEdges) {
            int u = pointId[e.aIdx];
            int v = pointId[e.bIdx];
            if (u == v) continue;            // degenerate, should not happen
            int id1 = (int)halfs.size();
            int id2 = id1 + 1;
            Half h1, h2;
            h1.origin = u; h1.to = v; h1.rev = id2; h1.next = -1; h1.face = -1;
            h2.origin = v; h2.to = u; h2.rev = id1; h2.next = -1; h2.face = -1;
            halfs.push_back(h1);
            halfs.push_back(h2);
            out[u].push_back(id1);
            out[v].push_back(id2);
        }
        int H = (int)halfs.size();

        // compute angles
        for (int i = 0; i < H; ++i) {
            const Point& a = uniqV[halfs[i].origin];
            const Point& b = uniqV[halfs[i].to];
            halfs[i].angle = atan2(b.y - a.y, b.x - a.x);
        }

        // sort outgoing edges CCW and store position
        vector<int> pos(H, -1);
        for (int v = 0; v < V; ++v) {
            auto &vec = out[v];
            sort(vec.begin(), vec.end(),
                 [&](int i, int j){
                     return halfs[i].angle < halfs[j].angle;
                 });
            for (size_t k = 0; k < vec.size(); ++k) pos[vec[k]] = (int)k;
        }

        // set next pointers (left‑face traversal)
        for (int i = 0; i < H; ++i) {
            int rev = halfs[i].rev;
            int to = halfs[i].to;
            int deg = (int)out[to].size();
            int nxtPos = (pos[rev] + 1) % deg;
            halfs[i].next = out[to][nxtPos];
        }

        /* ---------- 5. walk faces, compute signed areas ---------- */
        vector<double> faceArea;
        int faceCnt = 0;
        for (int i = 0; i < H; ++i) if (halfs[i].face == -1) {
            int cur = i;
            double area = 0.0;
            do {
                halfs[cur].face = faceCnt;
                int u = halfs[cur].origin;
                int v = halfs[cur].to;
                const Point& pu = uniqV[u];
                const Point& pv = uniqV[v];
                area += pu.x * pv.y - pv.x * pu.y;
                cur = halfs[cur].next;
            } while (cur != i);
            faceArea.push_back(area * 0.5);
            ++faceCnt;
        }

        // outer face = face with largest absolute area (negative orientation)
        int outerFace = -1;
        double bestAbs = -1.0;
        for (int f = 0; f < faceCnt; ++f) {
            double a = fabs(faceArea[f]);
            if (a > bestAbs) {
                bestAbs = a;
                outerFace = f;
            }
        }

        /* ---------- 6. count boundary edges ---------- */
        int answer = 0;
        for (int i = 0; i < H; i += 2) {
            int f1 = halfs[i].face;
            int f2 = halfs[i^1].face;
            bool onBoundary = (f1 == outerFace) ^ (f2 == outerFace);
            if (onBoundary) ++answer;
        }

        cout << answer << '\n';
    }
    return 0;
}
