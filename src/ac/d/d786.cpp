#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        int n;
        while (cin >> n) {
            long long sum = 0;
            for (int i = 0; i < n; ++i) {
                int x;
                cin >> x;
                sum += x;
            }
            cout << fixed << setprecision(2) << static_cast<double>(sum) / n << "\n";
        }
    }
    
    return 0;
}
