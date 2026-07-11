#include <iostream>
#include <vector>

using namespace std;

void print_line(const vector<int>& v) {
    vector<int> blocks;
    int cnt = 0;
    for (int x : v) {
        if (x == 1) {
            cnt++;
        } else {
            if (cnt > 0) {
                blocks.push_back(cnt);
                cnt = 0;
            }
        }
    }
    if (cnt > 0) {
        blocks.push_back(cnt);
    }
    if (blocks.empty()) {
        cout << 0 << "\n";
    } else {
        for (size_t i = 0; i < blocks.size(); ++i) {
            if (i > 0) cout << " ";
            cout << blocks[i];
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        vector<vector<int>> matrix(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> matrix[i][j];
            }
        }
        
        for (int j = 0; j < N; ++j) {
            vector<int> col(N);
            for (int i = 0; i < N; ++i) {
                col[i] = matrix[i][j];
            }
            print_line(col);
        }
        
        for (int i = 0; i < N; ++i) {
            print_line(matrix[i]);
        }
    }
    return 0;
}
