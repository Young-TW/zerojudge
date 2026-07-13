#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            int N;
            cin >> N;
            int matrix[10][10];
            
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    char c;
                    cin >> c;
                    matrix[i][j] = c - '0';
                }
            }

            int M;
            cin >> M;
            for (int k = 0; k < M; ++k) {
                string cmd;
                cin >> cmd;
                if (cmd == "row") {
                    int a, b;
                    cin >> a >> b;
                    --a; --b;
                    for (int j = 0; j < N; ++j) {
                        swap(matrix[a][j], matrix[b][j]);
                    }
                } else if (cmd == "col") {
                    int a, b;
                    cin >> a >> b;
                    --a; --b;
                    for (int i = 0; i < N; ++i) {
                        swap(matrix[i][a], matrix[i][b]);
                    }
                } else if (cmd == "inc") {
                    for (int i = 0; i < N; ++i) {
                        for (int j = 0; j < N; ++j) {
                            matrix[i][j] = (matrix[i][j] + 1) % 10;
                        }
                    }
                } else if (cmd == "dec") {
                    for (int i = 0; i < N; ++i) {
                        for (int j = 0; j < N; ++j) {
                            matrix[i][j] = (matrix[i][j] + 9) % 10;
                        }
                    }
                } else if (cmd == "transpose") {
                    for (int i = 0; i < N; ++i) {
                        for (int j = i + 1; j < N; ++j) {
                            swap(matrix[i][j], matrix[j][i]);
                        }
                    }
                }
            }

            cout << "Case #" << t << "\n";
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << matrix[i][j];
                }
                cout << "\n";
            }
            cout << "\n";
        }
    }
    return 0;
}
