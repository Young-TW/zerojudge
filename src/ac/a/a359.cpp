#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (1LL<<60);

struct Rect {
    ll x1, y1, x2, y2;
};

struct Node {
    ll x, y;
    int nb[4];                 // 0=N,1=E,2=S,3=W   -1 = none
    Node() { nb[0]=nb[1]=nb[2]=nb[3]=-1; }
};

inline ll makeKey(ll a, ll b) {          // unique 64‑bit key for (a,b)
    return (a<<32) ^ (b & 0xffffffffLL);
}

/*---------------------------------------------------------------*/

bool intervalOverlap(const vector<pair<ll,ll>>& vec, ll l, ll r) {
    // open interval (l,r) , vec stores open intervals (a,b) sorted, disjoint
    // return true iff some (a,b) intersects (l,r)
    int lo = 0, hi = (int)vec.size();
    while (lo < hi) {
        int mid = (lo+hi)/2;
        if (vec[mid].second <= l) lo = mid+1;
        else hi = mid;
    }
    if (lo < (int)vec.size() && vec[lo].first < r) return true;
    return false;
}

/*---------------------------------------------------------------*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin>>T)) return 0;
    while (T--) {
        ll xs, ys, xt, yt;
        cin >> xs >> ys >> xt >> yt;
        int n;  cin >> n;
        vector<Rect> rects(n);
        for (int i=0;i<n;i++) {
            ll a,b,c,d; cin>>a>>b>>c>>d;
            if (a>c) swap(a,c);
            if (b>d) swap(b,d);
            rects[i]={a,b,c,d};
        }

        // ----- collect X and Y coordinates -----
        vector<ll> X, Y;
        X.reserve(2+2*n);
        Y.reserve(2+2*n);
        X.push_back(xs); X.push_back(xt);
        Y.push_back(ys); Y.push_back(yt);
        for (auto &r:rects) {
            X.push_back(r.x1); X.push_back(r.x2);
            Y.push_back(r.y1); Y.push_back(r.y2);
        }
        sort(X.begin(), X.end());
        X.erase(unique(X.begin(), X.end()), X.end());
        sort(Y.begin(), Y.end());
        Y.erase(unique(Y.begin(), Y.end()), Y.end());
        int NX = (int)X.size(), NY = (int)Y.size();

        // ----- blocked intervals on each vertical / horizontal line -----
        vector<vector<pair<ll,ll>>> blockY(NX);   // for each x : blocked y-intervals
        vector<vector<pair<ll,ll>>> blockX(NY);   // for each y : blocked x-intervals

        for (auto &r:rects) {
            // vertical lines
            int l = (int)(upper_bound(X.begin(), X.end(), r.x1) - X.begin());
            int rpos = (int)(lower_bound(X.begin(), X.end(), r.x2) - X.begin()) - 1;
            for (int xi=l; xi<=rpos; ++xi) {
                blockY[xi].push_back({r.y1, r.y2});
            }
            // horizontal lines
            int ly = (int)(upper_bound(Y.begin(), Y.end(), r.y1) - Y.begin());
            int ry = (int)(lower_bound(Y.begin(), Y.end(), r.y2) - Y.begin()) - 1;
            for (int yi=ly; yi<=ry; ++yi) {
                blockX[yi].push_back({r.x1, r.x2});
            }
        }
        // merge intervals
        auto mergeVec = [](vector<pair<ll,ll>>& v){
            if (v.empty()) return;
            sort(v.begin(), v.end());
            vector<pair<ll,ll>> res;
            ll curL=v[0].first, curR=v[0].second;
            for (size_t i=1;i<v.size();++i){
                if (v[i].first <= curR){ // overlap or touch (they are open, touching is fine)
                    curR = max(curR, v[i].second);
                }else{
                    res.push_back({curL,curR});
                    curL=v[i].first; curR=v[i].second;
                }
            }
            res.push_back({curL,curR});
            v.swap(res);
        };
        for (auto &v:blockY) mergeVec(v);
        for (auto &v:blockX) mergeVec(v);

        // ----- create nodes -----
        unordered_map<ll,int> idMap;
        vector<Node> nodes;
        nodes.reserve(2000000);
        auto addNode = [&](ll x, ll y)->int{
            ll key = makeKey(x,y);
            auto it = idMap.find(key);
            if (it!=idMap.end()) return it->second;
            int id = (int)nodes.size();
            idMap[key]=id;
            Node nd; nd.x=x; nd.y=y;
            nodes.push_back(nd);
            return id;
        };
        // rectangle border points
        for (auto &r:rects){
            // vertical sides
            for (ll y : Y){
                if (y<r.y1 || y>r.y2) continue;
                addNode(r.x1, y);
                addNode(r.x2, y);
            }
            // horizontal sides
            for (ll x : X){
                if (x<r.x1 || x>r.x2) continue;
                addNode(x, r.y1);
                addNode(x, r.y2);
            }
        }
        // start & target
        int startId = addNode(xs,ys);
        int targetId = addNode(xt,yt);

        // ----- check start / target not inside a hive -----
        auto insideAny = [&](ll x, ll y)->bool{
            for (auto &r:rects){
                if (x>r.x1 && x<r.x2 && y>r.y1 && y<r.y2) return true;
            }
            return false;
        };
        if (insideAny(xs,ys) || insideAny(xt,yt)){
            cout << "No Path\n";
            if (T) { string dummy; getline(cin,dummy); } // consume possible blank line
            continue;
        }

        // ----- per‑line node lists -----
        vector<vector<pair<ll,int>>> perX(NX), perY(NY);
        for (int id=0; id<(int)nodes.size(); ++id){
            ll x = nodes[id].x, y = nodes[id].y;
            int xi = (int)(lower_bound(X.begin(), X.end(), x) - X.begin());
            int yi = (int)(lower_bound(Y.begin(), Y.end(), y) - Y.begin());
            perX[xi].push_back({y,id});
            perY[yi].push_back({x,id});
        }
        // ----- connect neighbours on vertical lines -----
        for (int xi=0; xi<NX; ++xi){
            auto &vec = perX[xi];
            sort(vec.begin(), vec.end());
            for (size_t i=1;i<vec.size();++i){
                int idLow = vec[i-1].second;
                int idHigh = vec[i].second;
                ll yLow = vec[i-1].first;
                ll yHigh = vec[i].first;
                if (!intervalOverlap(blockY[xi], yLow, yHigh)){
                    nodes[idLow].nb[0] = idHigh; // north
                    nodes[idHigh].nb[2] = idLow; // south
                }
            }
        }
        // ----- connect neighbours on horizontal lines -----
        for (int yi=0; yi<NY; ++yi){
            auto &vec = perY[yi];
            sort(vec.begin(), vec.end());
            for (size_t i=1;i<vec.size();++i){
                int idL = vec[i-1].second;
                int idR = vec[i].second;
                ll xL = vec[i-1].first;
                ll xR = vec[i].first;
                if (!intervalOverlap(blockX[yi], xL, xR)){
                    nodes[idL].nb[1] = idR; // east
                    nodes[idR].nb[3] = idL; // west
                }
            }
        }

        // ----- Dijkstra -----
        vector<ll> dist(nodes.size(), INF);
        using PQItem = pair<ll,int>; // (dist, id)
        priority_queue<PQItem, vector<PQItem>, greater<PQItem>> pq;
        dist[startId]=0;
        pq.push({0,startId});
        while(!pq.empty()){
            auto cur = pq.top(); pq.pop();
            ll d = cur.first;
            int u = cur.second;
            if (d!=dist[u]) continue;
            if (u==targetId) break;
            for (int dir=0; dir<4; ++dir){
                int v = nodes[u].nb[dir];
                if (v==-1) continue;
                ll w = (dir==0||dir==2) ? llabs(nodes[u].y - nodes[v].y)
                                        : llabs(nodes[u].x - nodes[v].x);
                if (dist[v] > d + w){
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[targetId]==INF) cout << "No Path\n";
        else cout << dist[targetId] << "\n";

        if (T) { string dummy; getline(cin,dummy); } // consume blank line between cases
    }
    return 0;
}
