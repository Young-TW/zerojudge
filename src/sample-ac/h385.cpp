#include <iostream>
#include <algorithm>

using namespace std;

long long gcd(long long a, long long b) {
    if (a == 0) return b;
    if (b == 0) return a;
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long v1, d1, v2, d2;
    int case_num = 1;
    while (cin >> v1 >> d1 >> v2 >> d2) {
        if (v1 == 0 && d1 == 0 && v2 == 0 && d2 == 0) break;
        
        cout << "Case #" << case_num << ": ";
        if (d1 * v2 < d2 * v1) {
            cout << "You owe me a beer!\n";
        } else {
            cout << "No beer for the captain.\n";
        }
        
        long long num = d1 * v2 + d2 * v1;
        long long den = 2 * v1 * v2;
        
        long long g = gcd(num, den);
        num /= g;
        den /= g;
        
        cout << "Avg. arrival time:";
        if (den == 1) {
            cout << " " << num << "\n";
        } else {
            cout << " " << num << "/" << den << "\n";
        }
        case_num++;
    }
    
    return 0;
}
