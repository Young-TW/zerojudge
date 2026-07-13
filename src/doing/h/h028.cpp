#include <iostream>
int n, l, highest, num;
int X[100005], H[100005], le[100005];

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
    std::cin >> n >> l;
    X[0] = H[0] = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> X[i];
        le[i] = i - 1;
    }
    for (int i = 1; i <= n; i++) std::cin >> H[i];
    for (int i = 1; i <= n; i++) {
        if ((X[i] - H[i] >= X[le[i]]) || (X[i] + H[i] <= X[i + 1])) {
            num++;
            le[i + 1] = le[i];
            highest = std::max(highest, H[i]);
            while (1) {
                if (le[i + 1] > 0 && X[le[i + 1]] + H[le[i + 1]] <= X[i + 1]) {
                    num++;
                    highest = std::max(highest, H[le[i + 1]]);
                    le[i + 1] = le[le[i + 1]];
                } else {
                    break;
                }
            }
        }
    }

    if (num == 0) {
        std::cout << 0 << std::endl;
        std::cout << 0 << std::endl;
    } else {
        std::cout << num << std::endl;
        std::cout << highest << std::endl;
    }
    return 0;
}