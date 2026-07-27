#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long x1, y1, x2, y2, x3, y3, x4, y4;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4) {
        long long W = x2 - x1;               // width  (>=0)
        long long H = y2 - y1;               // height (>=0)

        long long dx = llabs(x3 - x4);
        long long dy = llabs(y3 - y4);

        long long hor, ver;

        if (W == 0) hor = dx;
        else        hor = min(dx, W - dx);

        if (H == 0) ver = dy;
        else        ver = min(dy, H - dy);

        cout << (hor + ver) << '\n';
    }
    return 0;
}
