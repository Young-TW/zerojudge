#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int case_num = 1;
    while (cin >> n && n) {
        vector<int> x(n), y(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }
        
        vector<vector<double>> dist(n, vector<double>(n, 0.0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                long long dx = x[i] - x[j];
                long long dy = y[i] - y[j];
                dist[i][j] = sqrt(dx * dx + dy * dy);
            }
        }
        
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = min(dist[i][j], max(dist[i][k], dist[k][j]));
                }
            }
        }
        
        cout << "Scenario #" << case_num << "\n";
        cout << fixed << setprecision(3) << "Frog Distance = " << dist[0][1] << "\n\n";
        case_num++;
    }
    
    return 0;
}
