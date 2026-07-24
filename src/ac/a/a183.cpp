#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Segment {
    double t0, t1;   // [t0 , t1)
    double x0;       // left end at t0
    double v;        // velocity during the segment (may be 0)
};

struct Umbrella {
    int l;               // length
    int v;               // original signed speed
    int x0;              // initial left coordinate
    int Lmax;            // W - l
    vector<Segment> segs;
};

double get_left(const Umbrella &um, double t, int &idx) {
    // idx is guaranteed to be the segment containing t (or the last one)
    while (idx + 1 < (int)um.segs.size() && t >= um.segs[idx + 1].t0 - EPS)
        ++idx;
    const Segment &sg = um.segs[idx];
    return sg.x0 + sg.v * (t - sg.t0);
}

/* build the piecewise linear segments for one umbrella */
void build_segments(Umbrella &um, double T, int W) {
    if (um.l == W) {               // covers whole road forever
        um.segs.push_back({0.0, T, 0.0, 0.0});
        return;
    }
    if (um.v == 0) {
        um.segs.push_back({0.0, T, (double)um.x0, 0.0});
        return;
    }
    double pos = um.x0;
    double dir = (um.v > 0) ? 1.0 : -1.0;
    double speed = fabs((double)um.v);
    double t = 0.0;
    while (t < T - EPS) {
        double dist;
        if (dir > 0) dist = um.Lmax - pos;
        else          dist = pos;
        double dt = dist / speed;               // time to next border
        if (dt < EPS) {                          // already at border, reflect immediately
            dir = -dir;
            continue;
        }
        double tnext = t + dt;
        if (tnext > T) tnext = T;
        um.segs.push_back({t, tnext, pos, dir * speed});
        // advance
        pos += dir * speed * (tnext - t);
        t = tnext;
        if (t >= T - EPS) break;
        dir = -dir;                              // reflection
    }
}

/* add a crossing time if it lies strictly inside (a,b) */
inline void try_add(double a, double b, double t, vector<double> &ev) {
    if (t > a + EPS && t < b - EPS) ev.push_back(t);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, W, T, V;
    while (cin >> N >> W >> T >> V) {
        vector<Umbrella> us(N);
        for (int i = 0; i < N; ++i) {
            int x, l, v;
            cin >> x >> l >> v;
            us[i].x0 = x;
            us[i].l = l;
            us[i].v = v;
            us[i].Lmax = W - l;
        }

        // trivial case: any umbrella already covers whole road
        bool full = false;
        for (auto &u : us) if (u.l == W) { full = true; break; }
        if (full) {
            cout << fixed << setprecision(2) << 0.00 << "\n";
            continue;
        }

        // build segments
        for (auto &u : us) build_segments(u, (double)T, W);

        // collect event times
        vector<double> events;
        events.reserve(1000);
        events.push_back(0.0);
        events.push_back((double)T);
        for (auto &u : us) {
            for (auto &sg : u.segs) {
                events.push_back(sg.t0);
                events.push_back(sg.t1);
            }
        }

        // crossings of two end points
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                const auto &A = us[i];
                const auto &B = us[j];
                int p = 0, q = 0;
                while (p < (int)A.segs.size() && q < (int)B.segs.size()) {
                    double a = max(A.segs[p].t0, B.segs[q].t0);
                    double b = min(A.segs[p].t1, B.segs[q].t1);
                    if (a < b - EPS) {
                        // positions of left ends at time a
                        double xi = A.segs[p].x0 + A.segs[p].v * (a - A.segs[p].t0);
                        double xj = B.segs[q].x0 + B.segs[q].v * (a - B.segs[q].t0);
                        double vi = A.segs[p].v;
                        double vj = B.segs[q].v;
                        double dv = vi - vj;
                        if (fabs(dv) > EPS) {
                            // left-left
                            double t = a + (xj - xi) / dv;
                            try_add(a, b, t, events);
                            // left-right
                            t = a + (xj + B.l - xi) / dv;
                            try_add(a, b, t, events);
                            // right-left
                            t = a + (xj - (xi + A.l)) / dv;
                            try_add(a, b, t, events);
                            // right-right
                            t = a + (xj + B.l - (xi + A.l)) / dv;
                            try_add(a, b, t, events);
                        }
                    }
                    // advance the segment that ends first
                    if (A.segs[p].t1 < B.segs[q].t1 - EPS) ++p;
                    else if (B.segs[q].t1 < A.segs[p].t1 - EPS) ++q;
                    else { ++p; ++q; }
                }
            }
        }

        sort(events.begin(), events.end());
        vector<double> ev2;
        for (double t : events) {
            if (ev2.empty() || t - ev2.back() > EPS) ev2.push_back(t);
        }
        events.swap(ev2);
        int M = events.size();

        // pointers to current segment for each umbrella
        vector<int> curSeg(N, 0);
        vector<double> len(M, 0.0);
        vector<pair<double,double>> intervals(N);

        for (int k = 0; k < M; ++k) {
            double t = events[k];
            for (int i = 0; i < N; ++i) {
                const Umbrella &u = us[i];
                // move pointer if needed
                while (curSeg[i] + 1 < (int)u.segs.size() && t >= u.segs[curSeg[i] + 1].t0 - EPS)
                    ++curSeg[i];
                const Segment &sg = u.segs[curSeg[i]];
                double left = sg.x0 + sg.v * (t - sg.t0);
                intervals[i] = {left, left + u.l};
            }
            sort(intervals.begin(), intervals.end(),
                 [](const pair<double,double>& a, const pair<double,double>& b){
                     return a.first < b.first;
                 });
            double covered = 0.0;
            double curL = -1e100, curR = -1e100;
            for (auto &in : intervals) {
                if (in.first > curR + EPS) {
                    covered += curR - curL;
                    curL = in.first;
                    curR = in.second;
                } else {
                    curR = max(curR, in.second);
                }
            }
            covered += curR - curL;
            len[k] = covered;
        }

        // integrate
        double coveredTime = 0.0;
        for (int k = 0; k + 1 < M; ++k) {
            double dt = events[k+1] - events[k];
            coveredTime += (len[k] + len[k+1]) * 0.5 * dt;
        }

        double answer = V * ( (double)W * T - coveredTime );
        if (answer < 0) answer = 0;          // numerical safety
        cout << fixed << setprecision(2) << answer + 1e-9 << "\n";
    }
    return 0;
}
