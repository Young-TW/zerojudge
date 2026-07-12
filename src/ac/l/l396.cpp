#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    int x = -1, y = -1;
    for (int i = 1; i <= T; ++i) {
        for (int j = 1; j <= T; ++j) {
            char c;
            cin >> c;
            if (c == 'x') {
                x = j;
                y = i;
            }
        }
    }

    cin.ignore();

    string line;
    int total = 0, success = 0;

    while (getline(cin, line)) {
        stringstream ss(line);
        string token;
        vector<string> cmd;
        int steps = -1;

        while (ss >> token) {
            bool is_num = true;
            for (char c : token) {
                if (!isdigit(c)) {
                    is_num = false;
                    break;
                }
            }
            if (is_num) {
                steps = stoi(token);
            } else {
                cmd.push_back(token);
            }
        }

        if (steps == -1) continue;

        int dx = 0, dy = 0;
        if (cmd.size() == 1) {
            if (cmd[0] == "up") dy = -1;
            else if (cmd[0] == "down") dy = 1;
            else if (cmd[0] == "left") dx = -1;
            else if (cmd[0] == "right") dx = 1;
        } else if (cmd.size() == 3) {
            if (cmd[0] == "left" && cmd[1] == "up" && cmd[2] == "oblique") { dx = -1; dy = -1; }
            else if (cmd[0] == "right" && cmd[1] == "up" && cmd[2] == "oblique") { dx = 1; dy = -1; }
            else if (cmd[0] == "left" && cmd[1] == "down" && cmd[2] == "oblique") { dx = -1; dy = 1; }
            else if (cmd[0] == "right" && cmd[1] == "down" && cmd[2] == "oblique") { dx = 1; dy = 1; }
        }

        int new_x = x + dx * steps;
        int new_y = y + dy * steps;
        total++;

        if (new_x >= 1 && new_x <= T && new_y >= 1 && new_y <= T) {
            x = new_x;
            y = new_y;
            success++;
            cout << "x" << x << " y" << y << "\n";
        } else {
            cout << "-1\n";
        }
    }

    cout << "最終坐標為x" << x << " y" << y << "\n";
    cout << total << "/" << success << "/" << (total - success) << "/";
    if (total == 0) {
        cout << "0%\n";
    } else {
        int p10 = success * 1000 / total;
        if (p10 % 10 == 0) {
            cout << p10 / 10 << "%\n";
        } else {
            cout << p10 / 10 << "." << p10 % 10 << "%\n";
        }
    }

    return 0;
}
