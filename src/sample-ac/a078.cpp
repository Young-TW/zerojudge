#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>

using namespace std;

struct Statement {
    int line_no;
    int type; // 0: END, 1: ACC, 2: OUT, 3: GO, 4: IF
    int var_idx;
    long long val;
    int target_line;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Statement> statements;
    string line;
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        int line_no;
        if (!(ss >> line_no)) continue;
        
        string body;
        getline(ss, body);
        
        size_t start = body.find_first_not_of(" ");
        if (start != string::npos) {
            body = body.substr(start);
        } else {
            body = "";
        }

        Statement stmt;
        stmt.line_no = line_no;
        stmt.type = -1;
        stmt.var_idx = -1;
        stmt.val = 0;
        stmt.target_line = -1;

        vector<string> tokens;
        stringstream bss(body);
        string token;
        while (bss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;

        if (tokens[0] == "END") {
            stmt.type = 0;
        } else if (tokens[0] == "GO") {
            stmt.type = 3;
            stmt.target_line = stoi(tokens[1]);
        } else if (tokens[0] == "IF") {
            stmt.type = 4;
            string cond = tokens[1];
            size_t eq_pos = cond.find('=');
            stmt.var_idx = cond[0] - 'A';
            stmt.val = stoll(cond.substr(eq_pos + 1));
            stmt.target_line = stoi(tokens[3]);
        } else {
            if (tokens[0].find('+') != string::npos) {
                stmt.type = 1;
                size_t plus_pos = tokens[0].find('+');
                stmt.var_idx = tokens[0][0] - 'A';
                stmt.val = stoll(tokens[0].substr(plus_pos + 1));
            } else if (tokens[0].find('?') != string::npos) {
                stmt.type = 2;
                stmt.var_idx = tokens[0][0] - 'A';
            }
        }
        
        if (stmt.type != -1) {
            statements.push_back(stmt);
        }
    }

    sort(statements.begin(), statements.end(), [](const Statement& a, const Statement& b) {
        return a.line_no < b.line_no;
    });

    int line_to_idx[3005];
    memset(line_to_idx, -1, sizeof(line_to_idx));
    for (size_t i = 0; i < statements.size(); ++i) {
        if (statements[i].line_no <= 3000) {
            line_to_idx[statements[i].line_no] = i;
        }
    }

    long long vars[26] = {0};
    int cur_idx = 0;
    long long steps = 0;
    const long long MAX_STEPS = 10000000LL;

    while (true) {
        if (steps > MAX_STEPS) {
            cout << -1 << endl;
            return 0;
        }
        
        if (cur_idx < 0 || cur_idx >= (int)statements.size()) {
            cout << -1 << endl;
            return 0;
        }

        Statement& stmt = statements[cur_idx];
        steps++;

        if (stmt.type == 0) { // END
            cout << steps << endl;
            return 0;
        } else if (stmt.type == 1) { // ACC
            vars[stmt.var_idx] += stmt.val;
            cur_idx++;
        } else if (stmt.type == 2) { // OUT
            cur_idx++;
        } else if (stmt.type == 3) { // GO
            cur_idx = line_to_idx[stmt.target_line];
        } else if (stmt.type == 4) { // IF
            if (vars[stmt.var_idx] == stmt.val) {
                cur_idx = line_to_idx[stmt.target_line];
            } else {
                cur_idx++;
            }
        }
    }

    return 0;
}
