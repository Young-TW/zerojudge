#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int numProblems;
    while (cin >> numProblems) {
        while (numProblems--) {
            long long C, T;
            cin >> C >> T;
            int N;
            cin >> N;
            vector<long long> v(N), t(N);
            for (int i = 0; i < N; i++) {
                cin >> v[i] >> t[i];
            }
            
            vector<long long> pv(N+1, 0), pvt(N+1, 0);
            for (int i = 0; i < N; i++) {
                pv[i+1] = pv[i] + v[i];
                pvt[i+1] = pvt[i] + v[i]*t[i];
            }
            
            long long bestNum = 0, bestDen = 1;
            int bestL = -1, bestR = -1;
            
            for (int l = 0; l < N; l++) {
                for (int r = l; r < N; r++) {
                    long long sumV = pv[r+1] - pv[l];
                    long long sumVT = pvt[r+1] - pvt[l];
                    if (2*sumV < C) continue;
                    if (sumV > C) break;
                    long long diff = sumVT - T*sumV;
                    if (diff < 0) diff = -diff;
                    if (diff > 5*sumV) continue;
                    
                    if (bestL == -1) {
                        bestNum = diff;
                        bestDen = sumV;
                        bestL = l;
                        bestR = r;
                    } else {
                        __int128 left = (__int128)diff * bestDen;
                        __int128 right = (__int128)bestNum * sumV;
                        if (left < right) {
                            bestNum = diff;
                            bestDen = sumV;
                            bestL = l;
                            bestR = r;
                        }
                    }
                }
            }
            
            if (bestL == -1) {
                cout << "Not possible\n";
            } else {
                cout << bestL << " " << bestR << "\n";
            }
        }
    }
    return 0;
}
