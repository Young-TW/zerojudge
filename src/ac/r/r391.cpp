#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

const long long MOD = 1000000007LL;

int M, N;                                   // rows, columns
vector<vector<string>> grid;                // original contents
vector<vector<int>> state;                  // 0 = unvisited, 1 = visiting, 2 = done
vector<vector<bool>> errorCell;             // true -> ERROR
vector<vector<long long>> valueCell;        // computed value (mod MOD)

// forward declaration
pair<bool, long long> dfs(int r, int c);

// ------------------------------------------------------------
// helpers
bool is_digit_str(const string &s) {
    return s.size() == 1 && isdigit(s[0]);
}

// operand evaluation: digit or reference
pair<bool, long long> eval_operand(const string &op) {
    if (is_digit_str(op)) {
        return {true, (op[0] - '0') % MOD};
    } else {
        // reference like "C12"
        int col = op[0] - 'A';
        int row = stoi(op.substr(1)) - 1;   // to 0‑based
        return dfs(row, col);
    }
}

// ------------------------------------------------------------
// recursive evaluator
pair<bool, long long> dfs(int r, int c) {
    if (state[r][c] == 2) {
        if (errorCell[r][c]) return {false, 0};
        return {true, valueCell[r][c]};
    }
    if (state[r][c] == 1) {                 // cycle
        errorCell[r][c] = true;
        state[r][c] = 2;
        return {false, 0};
    }

    state[r][c] = 1;                         // mark as visiting

    const string &s = grid[r][c];
    if (s[0] != '=') {                       // plain digit
        long long v = (s[0] - '0') % MOD;
        valueCell[r][c] = v;
        errorCell[r][c] = false;
        state[r][c] = 2;
        return {true, v};
    }

    // formula
    string expr = s.substr(1);               // drop '='
    size_t plusPos = expr.find('+');
    string left = expr.substr(0, plusPos);
    string right = expr.substr(plusPos + 1);

    auto p1 = eval_operand(left);
    auto p2 = eval_operand(right);

    if (!p1.first || !p2.first) {
        errorCell[r][c] = true;
        state[r][c] = 2;
        return {false, 0};
    }

    long long res = (p1.second + p2.second) % MOD;
    valueCell[r][c] = res;
    errorCell[r][c] = false;
    state[r][c] = 2;
    return {true, res};
}

// ------------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> M >> N) {
        grid.assign(M, vector<string>(N));
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                cin >> grid[i][j];

        state.assign(M, vector<int>(N, 0));
        errorCell.assign(M, vector<bool>(N, false));
        valueCell.assign(M, vector<long long>(N, 0));

        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                dfs(i, j);

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (j) cout << ' ';
                if (errorCell[i][j]) cout << "ERROR";
                else cout << valueCell[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
