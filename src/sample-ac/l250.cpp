#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
using namespace std;

int main() {
    int L;
    while (cin >> L) {
        cin.ignore();
        vector<vector<string>> grid(L+1, vector<string>(L+1, ""));
        string line;
        while (getline(cin, line)) {
            stringstream ss(line);
            string name;
            if (!(ss >> name)) continue;
            if (name == "stop") break;
            string action;
            ss >> action;
            vector<int> coords;
            string token;
            while (ss >> token) {
                int num = 0;
                for (char c : token)
                    if (c >= '0' && c <= '9') num = num * 10 + (c - '0');
                coords.push_back(num);
            }
            int n = coords.size() / 2;
            if (action == "book") {
                if (n > 5) continue;
                bool ok = true;
                vector<pair<int,int>> s;
                for (int i = 0; i+1 < (int)coords.size(); i += 2) {
                    int x = coords[i], y = coords[i+1];
                    if (x < 1 || x > L || y < 1 || y > L) { ok = false; break; }
                    s.push_back({x, y});
                }
                if (!ok) continue;
                for (auto& p : s)
                    if (grid[p.first][p.second].empty()) grid[p.first][p.second] = name;
            } else if (action == "cancel" || action == "canccel") {
                if (n > 3) continue;
                bool ok = true;
                vector<pair<int,int>> s;
                for (int i = 0; i+1 < (int)coords.size(); i += 2) {
                    int x = coords[i], y = coords[i+1];
                    if (x < 1 || x > L || y < 1 || y > L || grid[x][y] != name) { ok = false; break; }
                    s.push_back({x, y});
                }
                if (!ok) continue;
                for (auto& p : s) grid[p.first][p.second] = "";
            }
        }
        for (int i = 1; i <= L; i++) {
            for (int j = 1; j <= L; j++) {
                if (j > 1) cout << " ";
                cout << (grid[i][j].empty() ? 'O' : 'X');
            }
            cout << "\n";
        }
    }
}
