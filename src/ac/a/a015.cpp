#include <iostream>

int main() {
    int x, y;
    int m[100][100];
    while (std::cin >> x >> y) {
        for (int i=0; i<x; i++) {
            for (int j=0; j<y; j++) {
                std::cin >> m[i][j];
            }
        }

        for (int i=0; i<y; i++) {
            for (int j=0; j<x; j++) {
                std::cout << m[j][i] << " ";
            }

            std::cout << std::endl;
        }
    }

    return 0;
}