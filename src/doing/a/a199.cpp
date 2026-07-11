#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    double S;
    while (cin >> N >> S) {
        double A_prev, B_prev, Rate_prev;
        cin >> A_prev >> B_prev >> Rate_prev;
        double L = Rate_prev, R = Rate_prev;
        double W = S;
        for (int i = 2; i <= N; ++i) {
            double A_curr, B_curr, Rate_curr;
            cin >> A_curr >> B_curr >> Rate_curr;
            double g1 = (L * A_curr + B_curr) / (L * A_prev + B_prev);
            double g2 = (R * A_curr + B_curr) / (R * A_prev + B_prev);
            double max_g = max(g1, g2);
            double factor = max(1.0, max_g);
            W *= factor;
            L = min(L, Rate_curr);
            R = max(R, Rate_curr);
            A_prev = A_curr;
            B_prev = B_curr;
        }
        cout << fixed << setprecision(3) << W << '\n';
    }
    return 0;
}
