#include <iostream>
#include <vector>

int main() {
    int n, tempi, count=0;
    std::cin >> n;
    std::vector<int> f(n);
    std::vector<int> tracked(n);
    for (int i=0; i<n; i++) {
        std::cin >> f[i];
        tracked[i] = 0;
    }

    for (int i=0; i<n; i++) {
        if (tracked[i]) continue;
        tracked[i] = 1;
        tempi = i;
        while (i != f[tempi]) {
            tempi = f[tempi];
            tracked[tempi] = 1;
        }

        count++;
    }

    std::cout << count;
    return 0;
}