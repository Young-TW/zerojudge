#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdio>

using namespace std;

// 計算多項式在 [0, limit] 的積分
// 多項式係數由最高次到最低次給予
// degree 為多項式次數
double integrate_poly(const vector<int>& coeffs, int degree, double limit) {
    double result = 0.0;
    int n = coeffs.size(); // n = degree + 1
    
    for (int i = 0; i < n; ++i) {
        int power = degree - i; // 當前項的次數
        double coef = static_cast<double>(coeffs[i]);
        
        // 積分公式: ∫ c*x^p dx = c * x^(p+1) / (p+1)
        // 代入上限 limit (下限為 0，所以只算上限)
        double term = coef * pow(limit, power + 1) / (power + 1);
        result += term;
    }
    
    return result;
}

// 自定義四捨五入函數，處理負數情況
double round_half_up(double value) {
    if (value >= 0) {
        return floor(value * 100.0 + 0.5) / 100.0;
    } else {
        return ceil(value * 100.0 - 0.5) / 100.0;
    }
}

int main() {
    // 優化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, m, k;
    while (cin >> n >> m >> k) {
        int deg_f, deg_g, deg_h;
        cin >> deg_f >> deg_g >> deg_h;

        vector<int> coeffs_f(deg_f + 1);
        for (int i = 0; i <= deg_f; ++i) cin >> coeffs_f[i];

        vector<int> coeffs_g(deg_g + 1);
        for (int i = 0; i <= deg_g; ++i) cin >> coeffs_g[i];

        vector<int> coeffs_h(deg_h + 1);
        for (int i = 0; i <= deg_h; ++i) cin >> coeffs_h[i];

        // 質量 = ∫∫∫ (f(x) + g(y) + h(z)) dx dy dz
        //      = ∫∫ [ f(x)*k + g(y)*k + ∫h(z)dz ] dx dy
        // 展開後等於：
        //      = k*m*∫f(x)dx + k*n*∫g(y)dy + n*m*∫h(z)dz
        // 其中積分區間皆為 [0, 對應邊長]

        double integral_f = integrate_poly(coeffs_f, deg_f, static_cast<double>(n));
        double integral_g = integrate_poly(coeffs_g, deg_g, static_cast<double>(m));
        double integral_h = integrate_poly(coeffs_h, deg_h, static_cast<double>(k));

        double total_mass = 0.0;
        total_mass += static_cast<double>(m) * static_cast<double>(k) * integral_f;
        total_mass += static_cast<double>(n) * static_cast<double>(k) * integral_g;
        total_mass += static_cast<double>(n) * static_cast<double>(m) * integral_h;

        double ans = round_half_up(total_mass);

        cout << fixed << setprecision(2) << ans << "\n";
    }

    return 0;
}
