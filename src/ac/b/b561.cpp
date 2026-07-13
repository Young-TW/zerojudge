#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    const double PI = acos(-1.0);
    
    int n1;
    while (cin >> n1) {
        long long sum1 = 0;
        for (int i = 0; i < n1; ++i) {
            int m;
            cin >> m;
            sum1 += m * m;
        }
        
        int n2;
        cin >> n2;
        long long sum2 = 0;
        for (int i = 0; i < n2; ++i) {
            int m;
            cin >> m;
            sum2 += m * m;
        }
        
        long long diff = (sum1 > sum2) ? (sum1 - sum2) : (sum2 - sum1);
        double area_diff = diff * PI / 4.0;
        cout << fixed << setprecision(2) << area_diff << "\n";
    }
    
    return 0;
}
