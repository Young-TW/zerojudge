#include <limits.h>

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int r, c, k, m;
    std::cin >> r >> c >> k >> m;
    std::vector<std::vector<int>> city(r + 2, std::vector<int>(c + 2));
    std::vector<std::vector<int>> carry(r + 2, std::vector<int>(c + 2));
    for (int i = 0; i < r + 2; i++) {
        for (int j = 0; j < c + 2; j++) {
            if (i == 0 || i == r + 1 || j == 0 || j == c + 1) {
                city[i][j] = -1;
            } else {
                std::cin >> city[i][j];
            }
        }
    }

    int peopleCount;
    for (int days = 0; days < m; days++) {
        for (int i = 1; i < r + 1; i++) {
            for (int j = 1; j < c + 1; j++) {
                carry[i][j] = 0;
            }
        }

        for (int i = 1; i < r + 1; i++) {
            for (int j = 1; j < c + 1; j++) {
                peopleCount = 0;
                if (city[i - 1][j] != -1) {
                    carry[i - 1][j] += city[i][j] / k;
                    peopleCount += city[i][j] / k;
                }

                if (city[i + 1][j] != -1) {
                    carry[i + 1][j] += city[i][j] / k;
                    peopleCount += city[i][j] / k;
                }

                if (city[i][j - 1] != -1) {
                    carry[i][j - 1] += city[i][j] / k;
                    peopleCount += city[i][j] / k;
                }

                if (city[i][j + 1] != -1) {
                    carry[i][j + 1] += city[i][j] / k;
                    peopleCount += city[i][j] / k;
                }

                city[i][j] -= peopleCount;
            }
        }

        for (int i = 1; i < r + 1; i++) {
            for (int j = 1; j < c + 1; j++) {
                city[i][j] += carry[i][j];
            }
        }
    }

    int max = INT_MIN, min = INT_MAX;
    for (const auto& i : city) {
        for (const auto& j : i) {
            if (max < j) max = j;
            if (j != -1 && min > j) min = j;
        }
    }

    std::cout << min << std::endl << max;
    return 0;
}