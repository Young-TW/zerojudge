#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b, c, d, L;
    while (cin >> a >> b >> c >> d >> L) {
        if (a == 0 && b == 0 && c == 0 && d == 0 && L == 0) {
            break;
        }
        
        int count = 0;
        for (long long x = 0; x <= L; ++x) {
            long long fx = a * x * x + b * x + c;
            if (fx % d == 0) {
                count++;
            }
        }
        
        cout << count << "\n";
    }
    
    return 0;
}
