#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, tc = 1;
    while (cin >> N && N) {
        vector<double> X(N), H(N), B(N);
        for (int i = 0; i < N; i++) cin >> X[i] >> H[i] >> B[i];
        
        int M = 2 * N;
        vector<double> sx1(M), sy1(M), sx2(M), sy2(M), sslp(M), sintercept(M);
        
        for (int i = 0; i < N; i++) {
            double xl = X[i] - B[i] / 2.0;
            double xr = X[i] + B[i] / 2.0;
            // Left segment: (xl, 0) to (X[i], H[i])
            sx1[2*i] = xl; sy1[2*i] = 0; sx2[2*i] = X[i]; sy2[2*i] = H[i];
            sslp[2*i] = H[i] / (X[i] - xl);
            sintercept[2*i] = -sslp[2*i] * xl;
            // Right segment: (X[i], H[i]) to (xr, 0)
            sx1[2*i+1] = X[i]; sy1[2*i+1] = H[i]; sx2[2*i+1] = xr; sy2[2*i+1] = 0;
            sslp[2*i+1] = -H[i] / (xr - X[i]);
            sintercept[2*i+1] = H[i] - sslp[2*i+1] * X[i];
        }
        
        // Collect critical x-coordinates
        vector<double> critX;
        for (int i = 0; i < M; i++) {
            critX.push_back(sx1[i]);
            critX.push_back(sx2[i]);
        }
        
        // Sort segments by x1 for pruning
        vector<int> segOrder(M);
        iota(segOrder.begin(), segOrder.end(), 0);
        sort(segOrder.begin(), segOrder.end(), [&](int a, int b) { return sx1[a] < sx1[b]; });
        
        // Find intersections between segments with overlapping x-ranges
        for (int ii = 0; ii < M; ii++) {
            int i = segOrder[ii];
            for (int jj = ii + 1; jj < M; jj++) {
                int j = segOrder[jj];
                if (sx1[j] > sx2[i] + EPS) break;
                double xOverlapL = max(sx1[i], sx1[j]);
                double xOverlapR = min(sx2[i], sx2[j]);
                if (xOverlapL > xOverlapR + EPS) continue;
                
                if (fabs(sslp[i] - sslp[j]) < EPS) continue;
                
                double xc = (sintercept[j] - sintercept[i]) / (sslp[i] - sslp[j]);
                if (xc >= xOverlapL - EPS && xc <= xOverlapR + EPS) {
                    critX.push_back(xc);
                }
            }
        }
        
        sort(critX.begin(), critX.end());
        critX.erase(unique(critX.begin(), critX.end(), [](double a, double b) { return fabs(a - b) < EPS; }), critX.end());
        
        // Sweep
        double total = 0;
        int segPtr = 0;
        vector<int> active;
        
        for (int k = 0; k + 1 < (int)critX.size(); k++) {
            double xa = critX[k], xb = critX[k + 1];
            if (xb - xa < EPS) continue;
            
            while (segPtr < M && sx1[segOrder[segPtr]] <= xa + EPS) {
                active.push_back(segOrder[segPtr]);
                segPtr++;
            }
            active.erase(remove_if(active.begin(), active.end(), 
                [&](int s) { return sx2[s] < xa - EPS; }), active.end());
            
            double xm = (xa + xb) / 2;
            double bestY = -1;
            int bestSeg = -1;
            for (int s : active) {
                if (sx1[s] <= xm + EPS && sx2[s] >= xm - EPS) {
                    double y = sslp[s] * xm + sintercept[s];
                    if (y > bestY) {
                        bestY = y;
                        bestSeg = s;
                    }
                }
            }
            
            if (bestSeg >= 0 && bestY > EPS) {
                double ya = sslp[bestSeg] * xa + sintercept[bestSeg];
                double yb = sslp[bestSeg] * xb + sintercept[bestSeg];
                double dx = xb - xa;
                double dy = yb - ya;
                if (fabs(dy) > EPS) {
                    total += sqrt(dx * dx + dy * dy);
                }
            }
        }
        
        long long ans = llround(total);
        cout << "Case " << tc << ": " << ans << "\n\n";
        tc++;
    }
    return 0;
}
