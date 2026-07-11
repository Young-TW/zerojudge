#include <iostream>
#include <string>
#include <vector>

using namespace std;

void trim(string& s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    while (cin >> t) {
        cin.ignore();
        vector<string> path;
        for (int i = 0; i < t; ++i) {
            string cmd;
            getline(cin, cmd);
            trim(cmd);
            if (cmd == "Where's my asphalt?") {
                if (path.empty()) {
                    cout << "\\\n";
                } else {
                    cout << "\\";
                    for (size_t j = 0; j < path.size(); ++j) {
                        cout << path[j] << "\\";
                    }
                    cout << "\n";
                }
            } else if (cmd == "Fly away.") {
                string loc;
                getline(cin, loc);
                trim(loc);
                if (!loc.empty() && loc[0] == '\\') {
                    path.clear();
                    loc = loc.substr(1);
                }
                size_t start = 0;
                while (start <= loc.length()) {
                    size_t end = loc.find('\\', start);
                    string token;
                    if (end == string::npos) {
                        token = loc.substr(start);
                        start = loc.length() + 1;
                    } else {
                        token = loc.substr(start, end - start);
                        start = end + 1;
                    }
                    if (token.empty()) continue;
                    if (token == "_") {
                        if (!path.empty()) {
                            path.pop_back();
                        }
                    } else {
                        path.push_back(token);
                    }
                }
            }
        }
    }
    return 0;
}
