#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <functional>

using namespace std;

// 解決浮點數精度問題，使用一個極小值作為 epsilon
const double EPS = 1e-9;

// 四捨五入到小數第二位
double round_to_2(double val) {
    return floor(val * 100.0 + 0.5) / 100.0;
}

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double k;
    while (cin >> k) {
        vector<double> solutions;

        // 根據題意推導：
        // 定義誤差率 e = |(真實值 - 計算值) / 真實值|
        // 這裡「真實值」是真正的誤差率 x，「計算值」是我們算出來的 k
        // 而題目說「算出來的誤差率有誤差」，且這個誤差率就是 x 本身
        // 所以：x = |(x - k) / x|
        // 由於 x 是誤差率，必然 x >= 0。若 x = 0，則分母為 0 無意義，除非 k=0 且極限考慮，但通常誤差率定義分母不為 0。
        // 若 x > 0，則 x = |x - k| / x  =>  x^2 = |x - k|
        
        // 情況 1: x - k >= 0  (即 x >= k)
        // 方程式變為：x^2 = x - k  =>  x^2 - x + k = 0
        // 判別式 D1 = 1 - 4k
        // 若 D1 >= 0，則有實根：x = (1 ± sqrt(D1)) / 2
        // 需驗證根是否滿足 x >= k 且 x > 0
        
        // 情況 2: x - k < 0  (即 x < k)
        // 方程式變為：x^2 = -(x - k) = k - x  =>  x^2 + x - k = 0
        // 判別式 D2 = 1 + 4k
        // 若 D2 >= 0，則有實根：x = (-1 ± sqrt(D2)) / 2
        // 需驗證根是否滿足 x < k 且 x > 0

        // --- 處理情況 1: x^2 - x + k = 0 ---
        double D1 = 1.0 - 4.0 * k;
        if (D1 >= -EPS) { // 考慮浮點誤差
            if (D1 < 0) D1 = 0;
            double sqrt_D1 = sqrt(D1);
            double x1 = (1.0 + sqrt_D1) / 2.0;
            double x2 = (1.0 - sqrt_D1) / 2.0;

            // 驗證 x1
            if (x1 > EPS && x1 >= k - EPS) {
                solutions.push_back(x1);
            }
            // 驗證 x2
            if (x2 > EPS && x2 >= k - EPS) {
                solutions.push_back(x2);
            }
        }

        // --- 處理情況 2: x^2 + x - k = 0 ---
        double D2 = 1.0 + 4.0 * k;
        if (D2 >= -EPS) {
            if (D2 < 0) D2 = 0;
            double sqrt_D2 = sqrt(D2);
            double x3 = (-1.0 + sqrt_D2) / 2.0;
            double x4 = (-1.0 - sqrt_D2) / 2.0;

            // 驗證 x3 (x4 必為負，因為 sqrt(1+4k) >= 0, -1-sqrt(...) <= -1，直接忽略)
            if (x3 > EPS && x3 < k + EPS) {
                solutions.push_back(x3);
            }
        }

        if (solutions.empty()) {
            cout << "NULL" << "\n";
        } else {
            // 排序
            sort(solutions.begin(), solutions.end());

            // 去重：四捨五入後相同視為同一數
            vector<double> unique_sols;
            if (!solutions.empty()) {
                unique_sols.push_back(solutions[0]);
                for (size_t i = 1; i < solutions.size(); ++i) {
                    double r_curr = round_to_2(solutions[i]);
                    double r_prev = round_to_2(unique_sols.back());
                    if (abs(r_curr - r_prev) > EPS) {
                        unique_sols.push_back(solutions[i]);
                    }
                }
            }

            // 輸出
            cout << fixed << setprecision(2);
            for (size_t i = 0; i < unique_sols.size(); ++i) {
                if (i > 0) cout << " ";
                cout << unique_sols[i];
            }
            cout << "\n";
        }
    }

    return 0;
}
