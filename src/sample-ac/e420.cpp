#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    vector<set<string>> clothes;
    map<string, int> color_count;
    set<string> current_clothes;

    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line == "#") {
            break;
        }
        if (line == "@") {
            clothes.push_back(current_clothes);
            current_clothes.clear();
        } else {
            current_clothes.insert(line);
            color_count[line]++;
        }
    }
    if (!current_clothes.empty()) {
        clothes.push_back(current_clothes);
    }

    long long ways = 1;
    for (const auto &s : clothes) {
        ways *= s.size();
    }

    int max_count = 0;
    for (const auto &p : color_count) {
        if (p.second > max_count) {
            max_count = p.second;
        }
    }

    vector<string> most_colors;
    for (const auto &p : color_count) {
        if (p.second == max_count) {
            most_colors.push_back(p.first);
        }
    }

    vector<string> perfect;
    if (!clothes.empty()) {
        for (const auto &color : clothes[0]) {
            bool in_all = true;
            for (const auto &s : clothes) {
                if (s.find(color) == s.end()) {
                    in_all = false;
                    break;
                }
            }
            if (in_all) {
                perfect.push_back(color);
            }
        }
    }

    cout << ways << "\n";
    for (size_t i = 0; i < most_colors.size(); ++i) {
        if (i > 0) cout << ",";
        cout << most_colors[i];
    }
    cout << "\n";
    for (size_t i = 0; i < perfect.size(); ++i) {
        if (i > 0) cout << ",";
        cout << perfect[i];
    }
    cout << "\n";

    return 0;
}
