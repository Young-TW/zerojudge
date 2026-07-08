#include <iostream>
#include <vector>

struct Die {
    int top = 1, bottom = 6, front = 4, back = 3, left = 5, right = 2;

    void rollForward() {
        int t = top, b = bottom, f = front, bk = back;
        top = bk;
        front = t;
        bottom = f;
        back = b;
    }

    void rollRight() {
        int t = top, b = bottom, l = left, r = right;
        top = l;
        right = t;
        bottom = r;
        left = b;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<Die> dice(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        if (b == -1) {
            dice[a].rollForward();
        } else if (b == -2) {
            dice[a].rollRight();
        } else {
            std::swap(dice[a], dice[b]);
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << dice[i].top;
        if (i < n) std::cout << ' ';
    }
    std::cout << '\n';

    return 0;
}
