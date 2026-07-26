#include <bits/stdc++.h>
using namespace std;

bool triangle(long long a, long long b, long long c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

// check quadrilateral possibility by trying every possible cut
bool quadrilateral(long long a, long long b, long long c) {
    long long sticks[3] = {a, b, c};
    for (int i = 0; i < 3; ++i) {
        long long L = sticks[i];
        if (L <= 1) continue;                 // cannot be cut
        long long other1 = sticks[(i + 1) % 3];
        long long other2 = sticks[(i + 2) % 3];
        for (long long x = 1; x <= L - 1; ++x) {
            long long y = L - x;
            long long sides[4] = {x, y, other1, other2};
            long long sum = x + y + other1 + other2;
            long long mx = *max_element(sides, sides + 4);
            if (2 * mx < sum) return true;    // longest < sum of the rest
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        long long a, b, c;
        cin >> a >> b >> c;
        if (triangle(a, b, c)) {
            cout << 3 << '\n';
        } else if (quadrilateral(a, b, c)) {
            cout << 4 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
    return 0;
}
