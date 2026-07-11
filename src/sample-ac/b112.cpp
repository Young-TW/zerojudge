#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        int g = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            g = gcd(g, x);
        }
        cout << g << "\n";
    }
    return 0;
}
