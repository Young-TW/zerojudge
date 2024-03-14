#include <iostream>
#include <vector>

int main(){
    int r, c, m;
    int b[10][10];
    int mk[10];

    std::cin >> r >> c >> m;

    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            std::cin >> b[i][j];
        }
    }

    for (int k=0; k<m; k++) {
        std::cin >> mk[k];
    }

    return 0;
}

// 矩陣翻轉