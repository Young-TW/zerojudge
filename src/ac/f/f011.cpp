#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

// 計算多項式在 x 處的值
// 係數 c[0] 是 x^n 的係數，c[n] 是常數項
double eval_poly(const vector<int>& c, double x) {
    double res = 0.0;
    int n = c.size() - 1; // 次方數
    for (int i = 0; i <= n; ++i) {
        // c[i] * x^(n-i)
        double term = (double)c[i];
        int power = n - i;
        for (int p = 0; p < power; ++p) {
            term *= x;
        }
        res += term;
    }
    return res;
}

// 計算多項式導數在 x 處的值
// 原多項式: c[0]x^n + c[1]x^(n-1) + ... + c[n]
// 導數: n*c[0]x^(n-1) + (n-1)*c[1]x^(n-2) + ... + 1*c[n-1]
double eval_deriv(const vector<int>& c, double x) {
    double res = 0.0;
    int n = c.size() - 1; // 次方數
    if (n == 0) return 0.0; // 常數的導數為 0
    
    for (int i = 0; i < n; ++i) {
        // 第 i 項係數 c[i] 對應 x^(n-i)，導數後係數變為 (n-i)*c[i]，次方變為 n-i-1
        int coeff = (n - i) * c[i];
        int power = n - i - 1;
        double term = (double)coeff;
        for (int p = 0; p < power; ++p) {
            term *= x;
        }
        res += term;
    }
    return res;
}

void solve() {
    int n;
    if (!(cin >> n)) return;
    
    vector<int> c(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> c[i];
    }
    
    double a;
    cin >> a;
    
    // 計算切點座標 (a, b)
    double b = eval_poly(c, a);
    
    // 計算切線斜率 m = f'(a)
    double m = eval_deriv(c, a);
    
    const double EPS = 1e-9;
    
    if (fabs(m) < EPS) {
        // 斜率為 0，切線是水平線 y = b
        if (fabs(b) < EPS) {
            // 水平線且 y=0，與赤道重合
            cout << "It can sleep everywhere!" << endl;
        } else {
            // 水平線但 y!=0，與赤道平行無交點
            cout << "It cannot sleep!" << endl;
        }
    } else {
        // 斜率不為 0，求交點 s
        // 0 = m(s - a) + b  =>  m(s - a) = -b  =>  s - a = -b/m  =>  s = a - b/m
        double s = a - b / m;
        
        // 輸出格式要求四捨五入到小數第 3 位
        cout << fixed << setprecision(3) << "(" << s << ",0)" << endl;
    }
}

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    
    return 0;
}
