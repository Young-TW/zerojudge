#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    while (cin >> T) {
        while (T--) {
            int N;
            cin >> N;
            long long sum = 0;
            long long sum_sq = 0;
            for (int i = 0; i < N; ++i) {
                int x;
                cin >> x;
                sum += x;
                sum_sq += static_cast<long long>(x) * x;
            }
            
            double mean = static_cast<double>(sum) / N;
            double var = static_cast<double>(sum_sq) / N - mean * mean;
            if (var < 0) var = 0;
            double sigma = sqrt(var);
            
            cout << fixed << setprecision(2);
            cout << sigma << "\n";
            
            int Q;
            cin >> Q;
            while (Q--) {
                double a, b;
                cin >> a >> b;
                double new_sigma = fabs(a) * sigma;
                cout << new_sigma << "\n";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
