#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p, l;
    cin >> n >> p >> l;

    vector<vector<int>> balu(n, vector<int>(n));
    vector<vector<int>> alan(n, vector<int>(n));

    unordered_set<int> balu_set;
    unordered_set<int> alan_set;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> balu[i][j];
            balu_set.insert(balu[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> alan[i][j];
            alan_set.insert(alan[i][j]);
        }
    }

    vector<int> order(l);
    for (int i = 0; i < l; ++i) {
        cin >> order[i];
    }

    vector<vector<bool>> balu_marked(n, vector<bool>(n, false));
    vector<vector<bool>> alan_marked(n, vector<bool>(n, false));

    vector<int> balu_row(n, 0);
    vector<int> balu_col(n, 0);
    int balu_diag1 = 0;
    int balu_diag2 = 0;

    vector<int> alan_row(n, 0);
    vector<int> alan_col(n, 0);
    int alan_diag1 = 0;
    int alan_diag2 = 0;

    int last_num = 0;
    int balu_lines = 0;
    int alan_lines = 0;

    for (int num : order) {
        last_num = num;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (balu[i][j] == num) {
                    balu_marked[i][j] = true;
                    balu_row[i]++;
                    balu_col[j]++;
                    if (i == j) balu_diag1++;
                    if (i + j == n - 1) balu_diag2++;
                }
                if (alan[i][j] == num) {
                    alan_marked[i][j] = true;
                    alan_row[i]++;
                    alan_col[j]++;
                    if (i == j) alan_diag1++;
                    if (i + j == n - 1) alan_diag2++;
                }
            }
        }

        int new_balu_lines = 0;
        for (int i = 0; i < n; ++i) {
            if (balu_row[i] == n) new_balu_lines++;
            if (balu_col[i] == n) new_balu_lines++;
        }
        if (balu_diag1 == n) new_balu_lines++;
        if (balu_diag2 == n) new_balu_lines++;

        int new_alan_lines = 0;
        for (int i = 0; i < n; ++i) {
            if (alan_row[i] == n) new_alan_lines++;
            if (alan_col[i] == n) new_alan_lines++;
        }
        if (alan_diag1 == n) new_alan_lines++;
        if (alan_diag2 == n) new_alan_lines++;

        balu_lines = new_balu_lines;
        alan_lines = new_alan_lines;

        if (balu_lines >= p || alan_lines >= p) {
            break;
        }
    }

    cout << last_num << " " << balu_lines << " " << alan_lines << "\n";

    if (balu_lines > alan_lines) {
        cout << "The winner is Baluteshih\n";
    } else if (alan_lines > balu_lines) {
        cout << "The winner is Alan\n";
    } else {
        cout << "Draw\n";
    }

    return 0;
}
