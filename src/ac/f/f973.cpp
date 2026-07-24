#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

// 計算 Weierstrass 函數 f(x) = sum(a^n * cos(b^n * pi * x))
// 由於 0 < a < 0.1，級數收斂非常快，計算約 20 項即可達到 double 精度極限
double calculate_f(double a, double b, double x) {
    double sum = 0.0;
    double a_n = 1.0; // a^0
    double b_n = 1.0; // b^0
    const double PI = acos(-1.0);
    
    // 迭代計算直到項的值小到可以忽略不計 (小於 1e-15)
    // 對於 a < 0.1，大約 15-20 次迭代就足夠了
    for (int n = 0; n < 100; ++n) {
        double term = a_n * cos(b_n * PI * x);
        sum += term;
        
        // 準備下一項
        // 如果 a_n 已經非常小，後續項對結果影響可忽略，提前結束
        if (fabs(term) < 1e-15 && n > 10) {
            break;
        }
        
        a_n *= a;
        b_n *= b;
        
        // 防止 b_n 過大導致 inf，雖然在 double 範圍內 cos 會處理，但保險起見
        // 不過題目 ab >= 6, a < 0.1 => b >= 60, b^n 增長極快
        // 當 b_n 大到一定程度，cos 的參數會失去精度，但這是浮點數不可避免的限制
        // 我們主要依賴 a^n 的快速衰減來保證總和的精度
    }
    return sum;
}

int main() {
    // 優化 I/O 操作
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double a, b;
    double x1, x2;

    // 讀取多筆測資直到 EOF
    while (cin >> a >> b >> x1 >> x2) {
        double f1 = calculate_f(a, b, x1);
        double f2 = calculate_f(a, b, x2);

        double diff = f1 - f2;
        
        // 判斷勝負條件：差距小於 1 為平手
        // 注意：題目說 "差距小於 1"，即 |f1 - f2| < 1
        if (fabs(diff) < 1.0) {
            cout << "Tie" << "\n";
        } else {
            if (f1 > f2) {
                cout << "Bully Maguire Wins" << "\n";
                // 根據 Weierstrass 函數性質，當 ab >= 6 時，函數處處連續但處處不可微
                // 因此切線斜率不存在，必須輸出 nan
                cout << "nan" << "\n";
            } else {
                cout << "Zemo Wins" << "\n";
                // 同理，斜率不存在
                cout << "nan" << "\n";
            }
        }
    }

    return 0;
}
