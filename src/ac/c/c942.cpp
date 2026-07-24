#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// 使用 long double 提高精度，並在關鍵比較時使用整數運算避免誤差
int main() {
    int N, M;
    while (cin >> N >> M && (N != 0 || M != 0)) {
        vector<long long> R(N);
        vector<long double> C(N);
        long double total_circumference = 0.0;
        
        for (int i = 0; i < N; ++i) {
            cin >> R[i];
            C[i] = 2.0 * acos(-1.0L) * R[i];
            total_circumference += C[i];
        }
        
        // 二分搜尋最大化的最小距離 D
        long double low = 0.0, high = total_circumference;
        vector<int> result(N);
        
        // 進行足夠次數的二分以達到高精度
        for (int iter = 0; iter < 100; ++iter) {
            long double mid = (low + high) / 2.0;
            if (mid < 1e-9) {
                low = mid;
                continue;
            }
            
            int total_points = 0;
            for (int i = 0; i < N; ++i) {
                total_points += (int)(C[i] / mid);
            }
            
            if (total_points >= M) {
                low = mid;
            } else {
                high = mid;
            }
        }
        
        // 使用找到的最佳距離計算各圓點數
        long double best_D = low;
        vector<int> points(N);
        int sum_points = 0;
        
        for (int i = 0; i < N; ++i) {
            points[i] = (int)(C[i] / best_D);
            sum_points += points[i];
        }
        
        // 如果點數總和多於 M，需要調整
        // 優先減少那些「實際間距」較小的圓的點數
        while (sum_points > M) {
            int min_idx = -1;
            long double min_ratio = 1e18; // C[i] / points[i]
            
            for (int i = 0; i < N; ++i) {
                if (points[i] > 1) { // 每個圓至少要有1個點（題目保證）
                    long double ratio = C[i] / points[i];
                    if (ratio < min_ratio) {
                        min_ratio = ratio;
                        min_idx = i;
                    }
                }
            }
            
            if (min_idx == -1) break; // 無法再減少
            points[min_idx]--;
            sum_points--;
        }
        
        // 輸出結果
        for (int i = 0; i < N; ++i) {
            if (i > 0) cout << " ";
            cout << points[i];
        }
        cout << endl;
    }
    
    return 0;
}
