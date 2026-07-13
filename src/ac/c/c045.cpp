#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }

    if (lines.empty()) return 0;

    size_t max_len = 0;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].length() > max_len) {
            max_len = lines[i].length();
        }
    }

    for (size_t i = 0; i < max_len; ++i) {
        for (int j = lines.size() - 1; j >= 0; --j) {
            if (i < lines[j].length()) {
                cout << lines[j][i];
            } else {
                cout << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}
