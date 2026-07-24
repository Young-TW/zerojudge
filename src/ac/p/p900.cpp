#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    vector<long long> A(10);
    vector<long long> B(10);
    
    for (int i = 0; i < 10; ++i) {
        cin >> A[i];
    }
    for (int i = 0; i < 10; ++i) {
        cin >> B[i];
    }
    
    long long min_cost = LLONG_MAX;
    int best_i = -1;
    int best_j = -1;
    
    // 枚舉所有可能的 i, j (1-based)
    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            long long cost = A[i-1] + B[j-1] + abs(i - j) * 1000LL;
            
            if (cost < min_cost) {
                min_cost = cost;
                best_i = i;
                best_j = j;
            }
            // 若 cost 相同，由於我們是按 i 從小到大、j 從小到大枚舉，
            // 第一個遇到的就是 i 最小、j 最小的解，所以不需要額外處理
        }
    }
    
    cout << best_i << " " << best_j << " " << min_cost << endl;
    
    return 0;
}
