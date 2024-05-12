#include <climits>
#include <iostream>

int main() {
    int n, a1, a2, b1, b2, c1, c2, x1, x2, y1, y2;
    std::cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2 >> n;
    int ans = -INT_MAX;
    for (int i = 0; i <= n; i++) {
        x1 = i;
        x2 = n - i;
        y1 = a1 * x1 * x1 + b1 * x1 + c1;
        y2 = a2 * x2 * x2 + b2 * x2 + c2;
        ans = std::max(ans, y1 + y2);
    }

    std::cout << ans;
    return 0;
}