#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cout << "PERFECTION OUTPUT\n";
    int n;
    while (cin >> n && n != 0) {
        int sum = 0;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                if (i != n) {
                    sum += i;
                }
                int j = n / i;
                if (j != i && j != n) {
                    sum += j;
                }
            }
        }
        
        cout << setw(5) << n << "  ";
        if (sum == n) {
            cout << "PERFECT\n";
        } else if (sum < n) {
            cout << "DEFICIENT\n";
        } else {
            cout << "ABUNDANT\n";
        }
    }
    cout << "END OF OUTPUT\n";
    
    return 0;
}
