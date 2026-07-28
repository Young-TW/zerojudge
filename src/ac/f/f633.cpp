#include <iostream>
#include <vector>
#include <array>

using namespace std;

class Cube {
public:
    array<array<int, 2>, 2> U, D, F, B, L, R;

    Cube() {
        U = {{{3, 3}, {3, 3}}};
        D = {{{4, 4}, {4, 4}}};
        F = {{{1, 1}, {1, 1}}};
        B = {{{6, 6}, {6, 6}}};
        L = {{{5, 5}, {5, 5}}};
        R = {{{2, 2}, {2, 2}}};
    }

    void rotateFaceCW(array<array<int, 2>, 2>& face) {
        int temp = face[0][0];
        face[0][0] = face[1][0];
        face[1][0] = face[1][1];
        face[1][1] = face[0][1];
        face[0][1] = temp;
    }

    void rotateFaceCCW(array<array<int, 2>, 2>& face) {
        int temp = face[0][0];
        face[0][0] = face[0][1];
        face[0][1] = face[1][1];
        face[1][1] = face[1][0];
        face[1][0] = temp;
    }

    void R_cw() {
        rotateFaceCW(R);
        array<int, 2> temp = {F[0][1], F[1][1]};
        F[0][1] = D[0][1];
        F[1][1] = D[1][1];
        D[0][1] = B[1][0];
        D[1][1] = B[0][0];
        B[1][0] = U[0][1];
        B[0][0] = U[1][1];
        U[0][1] = temp[0];
        U[1][1] = temp[1];
    }

    void U_cw() {
        rotateFaceCW(U);
        array<int, 2> temp = {F[0][0], F[0][1]};
        F[0][0] = R[0][0];
        F[0][1] = R[0][1];
        R[0][0] = B[0][0];
        R[0][1] = B[0][1];
        B[0][0] = L[0][0];
        B[0][1] = L[0][1];
        L[0][0] = temp[0];
        L[0][1] = temp[1];
    }

    void L_cw() {
        rotateFaceCW(L);
        array<int, 2> temp = {F[0][0], F[1][0]};
        F[0][0] = U[0][0];
        F[1][0] = U[1][0];
        U[0][0] = B[1][1];
        U[1][0] = B[0][1];
        B[1][1] = D[0][0];
        B[0][1] = D[1][0];
        D[0][0] = temp[0];
        D[1][0] = temp[1];
    }

    void D_cw() {
        rotateFaceCW(D);
        array<int, 2> temp = {F[1][0], F[1][1]};
        F[1][0] = L[1][0];
        F[1][1] = L[1][1];
        L[1][0] = B[1][0];
        L[1][1] = B[1][1];
        B[1][0] = R[1][0];
        B[1][1] = R[1][1];
        R[1][0] = temp[0];
        R[1][1] = temp[1];
    }

    void move(int cmd) {
        if (cmd == 1) R_cw();
        else if (cmd == 2) U_cw();
        else if (cmd == 3) L_cw();
        else if (cmd == 4) D_cw();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Cube cube;
    int cmd;
    while (cin >> cmd) {
        cube.move(cmd);
    }
    
    cout << cube.F[0][0] << " " << cube.F[0][1] << "\n";
    cout << cube.F[1][0] << " " << cube.F[1][1] << "\n";
    
    return 0;
}
