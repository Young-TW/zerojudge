#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    while (n--) {
        int S, t, A, B;
        cin >> S >> t >> A >> B;
        vector<vector<pair<double,double> > > airports(S+1);
        vector<double> Ti(S+1);
        for (int i = 1; i <= S; i++) {
            double x1,y1,x2,y2,x3,y3;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> Ti[i];
            double xs[3] = {x1,x2,x3};
            double ys[3] = {y1,y2,y3};
            double x4, y4;
            double dx01 = xs[1]-xs[0], dy01 = ys[1]-ys[0];
            double dx02 = xs[2]-xs[0], dy02 = ys[2]-ys[0];
            double dot0 = dx01*dx02 + dy01*dy02;
            double dx10 = xs[0]-xs[1], dy10 = ys[0]-ys[1];
            double dx12 = xs[2]-xs[1], dy12 = ys[2]-ys[1];
            double dot1 = dx10*dx12 + dy10*dy12;
            if (fabs(dot0) < 1e-9) {
                x4 = xs[1] + xs[2] - xs[0];
                y4 = ys[1] + ys[2] - ys[0];
            } else if (fabs(dot1) < 1e-9) {
                x4 = xs[0] + xs[2] - xs[1];
                y4 = ys[0] + ys[2] - ys[1];
            } else {
                x4 = xs[0] + xs[1] - xs[2];
                y4 = ys[0] + ys[1] - ys[2];
            }
            airports[i].push_back(make_pair(x1,y1));
            airports[i].push_back(make_pair(x2,y2));
            airports[i].push_back(make_pair(x3,y3));
            airports[i].push_back(make_pair(x4,y4));
        }
        int N = 4*S;
        vector<vector<pair<int,double> > > adj(N);
        for (int i = 1; i <= S; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = j+1; k < 4; k++) {
                    double dx = airports[i][j].first - airports[i][k].first;
                    double dy = airports[i][j].second - airports[i][k].second;
                    double d = sqrt(dx*dx+dy*dy);
                    double c = d * Ti[i];
                    int u = (i-1)*4 + j;
                    int v = (i-1)*4 + k;
                    adj[u].push_back(make_pair(v, c));
                    adj[v].push_back(make_pair(u, c));
                }
            }
        }
        for (int i = 1; i <= S; i++) {
            for (int j = i+1; j <= S; j++) {
                for (int a = 0; a < 4; a++) {
                    for (int b = 0; b < 4; b++) {
                        double dx = airports[i][a].first - airports[j][b].first;
                        double dy = airports[i][a].second - airports[j][b].second;
                        double d = sqrt(dx*dx+dy*dy);
                        double c = d * (double)t;
                        int u = (i-1)*4 + a;
                        int v = (j-1)*4 + b;
                        adj[u].push_back(make_pair(v, c));
                        adj[v].push_back(make_pair(u, c));
                    }
                }
            }
        }
        vector<double> dist(N, 1e18);
        priority_queue<pair<double,int>, vector<pair<double,int> >, greater<pair<double,int> > > pq;
        for (int j = 0; j < 4; j++) {
            int u = (A-1)*4 + j;
            dist[u] = 0;
            pq.push(make_pair(0.0, u));
        }
        while (!pq.empty()) {
            pair<double,int> top = pq.top(); pq.pop();
            double d = top.first;
            int u = top.second;
            if (d > dist[u]) continue;
            for (size_t e = 0; e < adj[u].size(); e++) {
                int v = adj[u][e].first;
                double w = adj[u][e].second;
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        double ans = 1e18;
        for (int j = 0; j < 4; j++) {
            int u = (B-1)*4 + j;
            ans = min(ans, dist[u]);
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
