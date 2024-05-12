#include <iostream>
#include <vector>

int main() {
    int n, m, tt = 0, temp;
    std::cin >> n >> m;
    std::vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> temp;
            ans[i] = std::max(ans[i], temp);
        }

        tt += ans[i];
    }

    std::cout << tt << std::endl;
    bool judge = 1;
    for (int i = 0; i < n; i++) {
        if (tt % ans[i] == 0) {
            if (!judge) std::cout << ' ';
            std::cout << ans[i];
            judge = 0;
        }
    }

    if (judge) std::cout << "-1";
    return 0;
}