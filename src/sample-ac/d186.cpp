#include <iostream>
#include <cmath>

using namespace std;

int get_sqrt(int n) {
    if (n <= 0) return 0;
    int x = static_cast<int>(sqrt(static_cast<double>(n)));
    while (x * x > n) {
        x--;
    }
    while ((x + 1) * (x + 1) <= n) {
        x++;
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b;
    while (cin >> a >> b && (a || b)) {
        int upper = get_sqrt(b);
        int lower = get_sqrt(a - 1);
        cout << upper - lower << "\n";
    }
    
    return 0;
}
