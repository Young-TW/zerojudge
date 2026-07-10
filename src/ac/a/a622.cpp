#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string line;
    vector<string> names;
    size_t maxlen = 0;
    while (getline(cin, line)) {
        if (line == "END") break;
        names.push_back(line);
        if (line.size() > maxlen) maxlen = line.size();
    }
    int n = (int)names.size();
    string out;
    for (size_t i = 0; i < maxlen; i++) {
        string row;
        for (int k = 0; k < n; k++) {
            if (k > 0) row += "  ";
            row += (i < names[k].size()) ? string(1, names[k][i]) : " ";
        }
        while (!row.empty() && row.back() == ' ') row.pop_back();
        out += row;
        out += '\n';
    }
    cout << out;
    return 0;
}
