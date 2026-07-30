#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h1, m1, h2, m2;
    while (cin >> h1 >> m1 >> h2 >> m2) {
        int t1 = h1 * 60 + m1;
        int t2 = h2 * 60 + m2;
        int diff = t2 - t1;
        if (diff < 0) diff += 24 * 60;  // 跨午夜的情況
        cout << diff / 60 << " " << diff % 60 << "\n";
    }
    return 0;
}
