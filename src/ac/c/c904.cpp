#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <functional>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    while (cin >> N >> M) {
        vector<int> w(N), v(N);
        double max_ratio = 0.0;
        for (int i = 0; i < N; ++i) {
            cin >> w[i] >> v[i];
            if ((double)v[i] / w[i] > max_ratio) {
                max_ratio = (double)v[i] / w[i];
            }
        }
        
        cout << fixed << setprecision(2);
        
        for (int i = 0; i < M; ++i) {
            int K;
            cin >> K;
            
            double L = 0.0, R = max_ratio;
            if (R == 0.0) R = 1.0; 
            
            for (int iter = 0; iter < 100; ++iter) {
                double mid = (L + R) / 2.0;
                vector<double> val(N);
                for (int j = 0; j < N; ++j) {
                    val[j] = v[j] - mid * w[j];
                }
                sort(val.begin(), val.end(), greater<double>());
                
                double sum = 0;
                for (int j = 0; j < K; ++j) {
                    sum += val[j];
                }
                
                if (sum >= 0) {
                    L = mid;
                } else {
                    R = mid;
                }
            }
            
            cout << L << "\n";
        }
    }
    
    return 0;
}
