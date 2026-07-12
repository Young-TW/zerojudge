#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            long long a, b, c;
            cin >> a >> b >> c;
            string type;
            
            if (a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a) {
                type = "Invalid";
            } else if (a == b && b == c) {
                type = "Equilateral";
            } else if (a == b || b == c || a == c) {
                type = "Isosceles";
            } else {
                type = "Scalene";
            }
            
            cout << "Case " << i << ": " << type << "\n";
        }
    }
    
    return 0;
}
