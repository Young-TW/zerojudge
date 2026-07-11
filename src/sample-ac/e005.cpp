#include <iostream>

using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long my_abs(long long x) {
    return x < 0 ? -x : x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long ax, ay, bx, by, cx, cy;
    while (cin >> ax >> ay >> bx >> by >> cx >> cy) {
        if (ax == 0 && ay == 0 && bx == 0 && by == 0 && cx == 0 && cy == 0) {
            break;
        }
        
        long long ans = gcd(my_abs(ax - bx), my_abs(ay - by)) +
                        gcd(my_abs(bx - cx), my_abs(by - cy)) +
                        gcd(my_abs(cx - ax), my_abs(cy - ay));
                        
        cout << ans << "\n";
    }
    
    return 0;
}
