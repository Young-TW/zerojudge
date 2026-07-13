#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    int region_num = 1;
    while (cin >> m >> n && (m || n)) {
        int N = m * n;
        vector<int> h(N);
        for (int i = 0; i < N; ++i) {
            cin >> h[i];
        }
        long long V;
        cin >> V;
        
        sort(h.begin(), h.end());
        
        long long S = 0;
        long long prev_Vk = 0;
        int prev_h = 0;
        double H = 0;
        int C = 0;
        
        for (int i = 0; i < N; ++i) {
            S += h[i];
            long long Vk = ((long long)h[i] * (i + 1) - S) * 100;
            if (Vk >= V) {
                if (Vk == V) {
                    H = h[i];
                    C = lower_bound(h.begin(), h.end(), h[i]) - h.begin();
                } else {
                    H = prev_h + (double)(V - prev_Vk) / (100.0 * i);
                    C = i;
                }
                break;
            }
            prev_Vk = Vk;
            prev_h = h[i];
            if (i == N - 1) {
                H = h[N - 1] + (double)(V - Vk) / (100.0 * N);
                C = N;
                break;
            }
        }
        
        cout << "Region " << region_num++ << "\n";
        cout << "Water level is " << fixed << setprecision(2) << H << " meters.\n";
        cout << fixed << setprecision(2) << (double)C / N * 100.0 << " percent of the region is under water.\n";
        cout << "\n";
    }
    
    return 0;
}
