#include <bits/stdc++.h>

int pl(int n) {
    if (n < 0) return -n;
    return n;
}

int main() {
    int n, lx, ly, x, y, maxx=0, minn=INT_MAX;
    std::cin >> n;
    int d;
    for (int i=0; i<n; i++) {
        std::cin >> x >> y;
        if (i == 0) {
            lx = x;
            ly = y;
            continue;
        }

        d = pl(x-lx)+pl(y-ly);
        lx = x;
        ly = y;
        maxx = std::max(maxx,d);
        minn = std::min(minn,d);
    }

    std::cout << maxx << " " << minn << std::endl;
    return 0;
}