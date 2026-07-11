#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

using int128_t = __int128;

template <typename T>
T gcd(T a, T b) {
    while (b) {
        T t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void print_int128(int128_t x) {
    if (x == 0) {
        cout << '0';
        return;
    }
    string s = "";
    while (x > 0) {
        s += char('0' + (int)(x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long S, k;
    while (cin >> S >> k) {
        int128_t k2_plus_1 = (int128_t)k * k + 1;
        int128_t k1_sq = (int128_t)(k + 1) * (k + 1);
        
        int128_t g = (k % 2 == 1) ? 2 : 1;
        k2_plus_1 /= g;
        k1_sq /= g;
        
        int128_t D = gcd((int128_t)S, k1_sq);
        int128_t num = (int128_t)S / D * k2_plus_1;
        int128_t den = k1_sq / D;
        
        if (den == 1) {
            print_int128(num);
        } else {
            print_int128(num);
            cout << " / ";
            print_int128(den);
        }
        cout << "\n";
    }
    
    return 0;
}
