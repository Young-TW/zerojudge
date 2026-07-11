#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <utility>

using namespace std;

bool is_num(const string& s) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '-' || s[0] == '+') {
        if (s.size() == 1) return false;
        start = 1;
    }
    for (int i = start; i < s.size(); ++i) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int R, C;
vector<vector<string>> grid;
vector<vector<int>> state;
vector<vector<long long>> val;
vector<vector<bool>> is_err;

pair<bool, long long> get_cell(int r, int c);

pair<bool, long long> eval_operand(const string& s) {
    if (is_num(s)) {
        try {
            return {true, stoll(s)};
        } catch (...) {
            return {false, 0};
        }
    } else {
        if (s.empty()) return {false, 0};
        int col = 0;
        int i = 0;
        while (i < s.size() && isalpha(s[i])) {
            col = col * 26 + (toupper(s[i]) - 'A');
            i++;
        }
        if (i == 0 || i == s.size()) return {false, 0};
        for (int j = i; j < s.size(); ++j) {
            if (!isdigit(s[j])) return {false, 0};
        }
        try {
            int row = stoll(s.substr(i)) - 1;
            return get_cell(row, col);
        } catch (...) {
            return {false, 0};
        }
    }
}

pair<bool, long long> get_cell(int r, int c) {
    if (r < 0 || r >= R || c < 0 || c >= C) {
        return {false, 0};
    }
    if (state[r][c] == 2) {
        if (is_err[r][c]) return {false, 0};
        return {true, val[r][c]};
    }
    if (state[r][c] == 1) {
        return {false, 0};
    }
    
    state[r][c] = 1;
    
    const string& token = grid[r][c];
    if (token[0] == '=') {
        char op = 0;
        int op_pos = -1;
        for (int i = 1; i < token.size(); ++i) {
            if ((token[i] == '+' || token[i] == '-' || token[i] == '*' || token[i] == '/') &&
                (isdigit(token[i-1]) || isalpha(token[i-1]))) {
                op = token[i];
                op_pos = i;
                break;
            }
        }
        
        if (op_pos == -1) {
            string operand = token.substr(1);
            auto v1 = eval_operand(operand);
            if (!v1.first) {
                is_err[r][c] = true;
                state[r][c] = 2;
                return {false, 0};
            } else {
                val[r][c] = v1.second;
                is_err[r][c] = false;
                state[r][c] = 2;
                return {true, val[r][c]};
            }
        }
        
        string left = token.substr(1, op_pos - 1);
        string right = token.substr(op_pos + 1);
        
        auto v1 = eval_operand(left);
        auto v2 = eval_operand(right);
        
        if (!v1.first || !v2.first) {
            is_err[r][c] = true;
            state[r][c] = 2;
            return {false, 0};
        } else {
            long long res = 0;
            if (op == '+') res = v1.second + v2.second;
            else if (op == '-') res = v1.second - v2.second;
            else if (op == '*') res = v1.second * v2.second;
            else if (op == '/') {
                if (v2.second == 0) {
                    is_err[r][c] = true;
                    state[r][c] = 2;
                    return {false, 0};
                }
                res = v1.second / v2.second;
            }
            val[r][c] = res;
            is_err[r][c] = false;
            state[r][c] = 2;
            return {true, val[r][c]};
        }
    } else {
        if (is_num(token)) {
            try {
                val[r][c] = stoll(token);
                is_err[r][c] = false;
                state[r][c] = 2;
                return {true, val[r][c]};
            } catch (...) {
                is_err[r][c] = true;
                state[r][c] = 2;
                return {false, 0};
            }
        } else {
            is_err[r][c] = true;
            state[r][c] = 2;
            return {false, 0};
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while (cin >> R >> C) {
        grid.assign(R, vector<string>(C));
        state.assign(R, vector<int>(C, 0));
        val.assign(R, vector<long long>(C, 0));
        is_err.assign(R, vector<bool>(C, false));
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> grid[i][j];
            }
        }
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                get_cell(i, j);
            }
        }
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (j > 0) cout << " ";
                if (is_err[i][j]) {
                    cout << "ERROR";
                } else {
                    cout << val[i][j];
                }
            }
            cout << "\n";
        }
    }
    
    return 0;
}
