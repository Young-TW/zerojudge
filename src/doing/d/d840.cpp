#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

struct Statement {
    string speaker;
    string type;
    string content;
};

vector<string> names;
vector<Statement> statements;
int M, N, P;
map<string, int> name_to_index;
vector<int> liars;
vector<bool> is_liar;
vector<bool> possible_culprit;

bool check_consistency(int culprit_index, int today) {
    int lie_count = 0;
    for (const auto& stmt : statements) {
        bool is_true = false;
        if (stmt.type == "I am guilty.") {
            is_true = (name_to_index[stmt.speaker] == culprit_index);
        } else if (stmt.type == "I am not guilty.") {
            is_true = (name_to_index[stmt.speaker] != culprit_index);
        } else if (stmt.type.find(" is guilty.") != string::npos) {
            string name = stmt.type.substr(0, stmt.type.find(" is guilty."));
            is_true = (name_to_index[name] == culprit_index);
        } else if (stmt.type.find(" is not guilty.") != string::npos) {
            string name = stmt.type.substr(0, stmt.type.find(" is not guilty."));
            is_true = (name_to_index[name] != culprit_index);
        } else if (stmt.type.find("Today is ") != string::npos) {
            string day = stmt.type.substr(9);
            is_true = (day == (today == 0 ? "Monday" :
                              today == 1 ? "Tuesday" :
                              today == 2 ? "Wednesday" :
                              today == 3 ? "Thursday" :
                              today == 4 ? "Friday" :
                              today == 5 ? "Saturday" : "Sunday"));
        }

        bool speaker_is_liar = is_liar[name_to_index[stmt.speaker]];
        if ((is_true && speaker_is_liar) || (!is_true && !speaker_is_liar)) {
            lie_count++;
            if (lie_count > N) return false;
        }
    }
    return lie_count == N;
}

int main() {
    while (cin >> M >> N >> P) {
        names.resize(M);
        name_to_index.clear();
        for (int i = 0; i < M; ++i) {
            cin >> names[i];
            name_to_index[names[i]] = i;
        }

        statements.clear();
        cin.ignore();
        for (int i = 0; i < P; ++i) {
            string line;
            getline(cin, line);
            size_t colon_pos = line.find(": ");
            string speaker = line.substr(0, colon_pos);
            string content = line.substr(colon_pos + 2);

            Statement stmt;
            stmt.speaker = speaker;
            stmt.content = content;

            if (content == "I am guilty.") {
                stmt.type = "I am guilty.";
            } else if (content == "I am not guilty.") {
                stmt.type = "I am not guilty.";
            } else if (content.find(" is guilty.") != string::npos) {
                stmt.type = content;
            } else if (content.find(" is not guilty.") != string::npos) {
                stmt.type = content;
            } else if (content.find("Today is ") == 0) {
                stmt.type = content;
            } else {
                continue;
            }
            statements.push_back(stmt);
        }

        possible_culprit.assign(M, false);
        int possible_count = 0;
        string result;

        for (int culprit = 0; culprit < M; ++culprit) {
            bool found = false;
            for (int today = 0; today < 7; ++today) {
                is_liar.assign(M, false);
                vector<int> indices(M);
                for (int i = 0; i < M; ++i) indices[i] = i;
                sort(indices.begin(), indices.end(), [culprit](int a, int b) {
                    return a == culprit ? true : (b == culprit ? false : a < b);
                });

                bool valid = false;
                do {
                    int liar_count = 0;
                    for (int i = 0; i < N; ++i) {
                        is_liar[indices[i]] = true;
                        liar_count++;
                    }
                    if (check_consistency(culprit, today)) {
                        valid = true;
                        break;
                    }
                } while (next_permutation(indices.begin(), indices.end()));

                if (valid) {
                    found = true;
                    break;
                }
            }
            if (found) {
                possible_culprit[culprit] = true;
                possible_count++;
            }
        }

        if (possible_count == 0) {
            cout << "Impossible" << endl;
        } else if (possible_count == 1) {
            for (int i = 0; i < M; ++i) {
                if (possible_culprit[i]) {
                    cout << names[i] << endl;
                    break;
                }
            }
        } else {
            cout << "Cannot Determine" << endl;
        }
    }
    return 0;
}
