#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

enum StmtType {
    GUILTY_SELF,
    NOT_GUILTY_SELF,
    GUILTY_OTHER,
    NOT_GUILTY_OTHER,
    TODAY
};

struct Statement {
    int speaker;
    StmtType type;
    int target;
};

bool parse_statement(const string& speaker_name, const string& content, const map<string,int>& name_to_idx, const vector<string>& days, Statement& stmt) {
    auto it = name_to_idx.find(speaker_name);
    if (it == name_to_idx.end()) return false;
    stmt.speaker = it->second;

    string s = content;
    bool has_period = false;
    if (!s.empty() && s.back() == '.') {
        s.pop_back();
        has_period = true;
    } else if (s.length() >= 3) {
        unsigned char c1 = s[s.length()-3];
        unsigned char c2 = s[s.length()-2];
        unsigned char c3 = s[s.length()-1];
        if (c1 == 0xEF && c2 == 0xBC && c3 == 0x8E) {
            s.erase(s.length()-3);
            has_period = true;
        }
    }
    if (!has_period && s.length() >= 2) {
        unsigned char c1 = s[s.length()-2];
        unsigned char c2 = s[s.length()-1];
        if ((c1 == 0xA1 && c2 == 0xB0) || (c1 == 0xA3 && c2 == 0xAE)) {
            s.erase(s.length()-2);
            has_period = true;
        }
    }
    if (!has_period) {
        return false;
    }

    if (s == "I am guilty") {
        stmt.type = GUILTY_SELF;
        return true;
    }
    if (s == "I am not guilty") {
        stmt.type = NOT_GUILTY_SELF;
        return true;
    }

    string not_guilty_suffix = " is not guilty";
    size_t pos = s.find(not_guilty_suffix);
    if (pos != string::npos && pos > 0) {
        string name = s.substr(0, pos);
        auto it_name = name_to_idx.find(name);
        if (it_name != name_to_idx.end()) {
            stmt.type = NOT_GUILTY_OTHER;
            stmt.target = it_name->second;
            return true;
        }
    }

    string guilty_suffix = " is guilty";
    pos = s.find(guilty_suffix);
    if (pos != string::npos && pos > 0) {
        string name = s.substr(0, pos);
        auto it_name = name_to_idx.find(name);
        if (it_name != name_to_idx.end()) {
            stmt.type = GUILTY_OTHER;
            stmt.target = it_name->second;
            return true;
        }
    }

    string today_prefix = "Today is ";
    if (s.find(today_prefix) == 0) {
        string day = s.substr(today_prefix.length());
        auto it_day = find(days.begin(), days.end(), day);
        if (it_day != days.end()) {
            stmt.type = TODAY;
            stmt.target = it_day - days.begin();
            return true;
        }
    }

    return false;
}

bool check_consistent(const vector<Statement>& stmts, int M, int N, int culprit, int today) {
    vector<int> type_fixed(M, -1);
    for (const auto& stmt : stmts) {
        bool is_true = false;
        switch (stmt.type) {
            case GUILTY_SELF:
                is_true = (stmt.speaker == culprit);
                break;
            case NOT_GUILTY_SELF:
                is_true = (stmt.speaker != culprit);
                break;
            case GUILTY_OTHER:
                is_true = (stmt.target == culprit);
                break;
            case NOT_GUILTY_OTHER:
                is_true = (stmt.target != culprit);
                break;
            case TODAY:
                is_true = (stmt.target == today);
                break;
        }
        int expected_type = is_true ? 0 : 1;
        int sp = stmt.speaker;
        if (type_fixed[sp] == -1) {
            type_fixed[sp] = expected_type;
        } else if (type_fixed[sp] != expected_type) {
            return false;
        }
    }
    int L_fixed = 0, T_fixed = 0;
    for (int i = 0; i < M; ++i) {
        if (type_fixed[i] == 1) L_fixed++;
        else if (type_fixed[i] == 0) T_fixed++;
    }
    return (L_fixed <= N && N <= M - T_fixed);
}

int main() {
    int M, N, P;
    while (cin >> M >> N >> P) {
        vector<string> names(M);
        map<string, int> name_to_idx;
        for (int i = 0; i < M; ++i) {
            cin >> names[i];
            name_to_idx[names[i]] = i;
        }
        cin.ignore();

        vector<Statement> stmts;
        vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        for (int i = 0; i < P; ++i) {
            string line;
            getline(cin, line);
            size_t colon_pos = line.find(':');
            if (colon_pos == string::npos) continue;
            string speaker = line.substr(0, colon_pos);
            string content = line.substr(colon_pos + 1);
            if (!content.empty() && content[0] == ' ') {
                content = content.substr(1);
            }
            Statement stmt;
            if (parse_statement(speaker, content, name_to_idx, days, stmt)) {
                stmts.push_back(stmt);
            }
        }

        vector<bool> possible(M, false);
        for (int c = 0; c < M; ++c) {
            bool found = false;
            for (int d = 0; d < 7; ++d) {
                if (check_consistent(stmts, M, N, c, d)) {
                    found = true;
                    break;
                }
            }
            if (found) possible[c] = true;
        }

        int possible_count = 0;
        int last_idx = -1;
        for (int i = 0; i < M; ++i) {
            if (possible[i]) {
                possible_count++;
                last_idx = i;
            }
        }
        if (possible_count == 0) {
            cout << "Impossible" << endl;
        } else if (possible_count == 1) {
            cout << names[last_idx] << endl;
        } else {
            cout << "Cannot Determine" << endl;
        }
    }
    return 0;
}
