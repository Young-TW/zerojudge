#include <iostream>
using namespace std;

int b[3][2][2] = {
    {{4, 2}, {1, 3}},  // b1
    {{1, 2}, {4, 3}},  // b2
    {{4, 3}, {1, 2}}   // b3
};

int get_T(int h, int I, int J) {
    while (h > 3) {
        if (J == 0) return 1;
        if (J == h - 1) return 2;
        if (I == 0) {
            I = 1;
            continue;
        }
        if (I == h - 1) {
            I = h - 2;
            continue;
        }
        --I; --J;
        h -= 2;
    }
    static const int table[3][3] = {
        {0, 0, 1},
        {0, 1, 0},
        {0, 0, 1}
    };
    return table[I][J];
}

int get_A1(int h, int I, int J) {
    int J_flip = h - 1 - J;
    int term1 = h * ((I + J_flip + (h + 1) / 2) % h);
    int term2 = (I + 2 * J_flip + 1) % h;
    return term1 + term2 + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int m, r, c;
        cin >> m >> r >> c;
        int h = m / 2;
        --r; --c;
        int I = r / 2, J = c / 2;
        int dr = r % 2, dc = c % 2;
        int A1_val = get_A1(h, I, J);
        int A2_val = (A1_val - 1) * 4;
        int type = get_T(h, I, J);
        int B_val = b[type][dr][dc];
        cout << A2_val + B_val << '\n';
    }
    return 0;
}
