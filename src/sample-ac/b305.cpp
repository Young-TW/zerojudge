#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    while (cin >> T) {
        long long total_n = 0;
        long long total_sum = 0;
        long long total_sq_sum = 0;
        
        for (int i = 0; i < T; ++i) {
            long long n, u, s;
            cin >> n >> u >> s;
            total_n += n;
            total_sum += n * u;
            total_sq_sum += n * (s * s + u * u);
        }
        
        double mean = static_cast<double>(total_sum) / total_n;
        double variance = static_cast<double>(total_sq_sum) / total_n - mean * mean;
        if (variance < 0) variance = 0;
        double std_dev = sqrt(variance);
        
        cout << total_n << " " << fixed << setprecision(2) << mean << " " << std_dev << "\n";
    }
    
    return 0;
}
