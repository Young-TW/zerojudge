#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int A[6][6];
    int base3x3[3][3] = {
        {6, 1, 8},
        {7, 5, 3},
        {2, 9, 4}
    };
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            int val = (base3x3[i][j] - 1) * 4;
            A[i * 2][j * 2] = val;
            A[i * 2][j * 2 + 1] = val;
            A[i * 2 + 1][j * 2] = val;
            A[i * 2 + 1][j * 2 + 1] = val;
        }
    }
    
    int B[6][6];
    int B1[2][2] = {{4, 2}, {1, 3}};
    int B2[2][2] = {{1, 2}, {4, 3}};
    int pattern[3][3] = {
        {1, 1, 2},
        {1, 2, 1},
        {1, 1, 2}
    };
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            int (*curB)[2] = (pattern[i][j] == 1) ? B1 : B2;
            for(int x = 0; x < 2; ++x) {
                for(int y = 0; y < 2; ++y) {
                    B[i * 2 + x][j * 2 + y] = curB[x][y];
                }
            }
        }
    }
    
    int C[6][6];
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    
    cout << "A" << endl;
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6; ++j) {
            cout << setw(3) << A[i][j];
        }
        cout << endl;
    }
    
    cout << "B" << endl;
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6; ++j) {
            cout << setw(3) << B[i][j];
        }
        cout << endl;
    }
    
    cout << "magic6" << endl;
    for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 6; ++j) {
            cout << setw(3) << C[i][j];
        }
        cout << endl;
    }
    
    return 0;
}
