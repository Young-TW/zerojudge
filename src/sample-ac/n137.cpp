#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        string dummy;
        getline(cin, dummy);
        for (int i = 0; i < n; ++i) {
            string dept_line, content_line;
            getline(cin, dept_line);
            getline(cin, content_line);

            stringstream ss_dept(dept_line);
            stringstream ss_content(content_line);

            vector<pair<string, int>> reports;
            string dept;
            int content;
            while (ss_dept >> dept) {
                if (ss_content >> content) {
                    reports.push_back(make_pair(dept, content));
                }
            }

            sort(reports.begin(), reports.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
                if (a.first != b.first) return a.first < b.first;
                return a.second < b.second;
            });

            for (size_t j = 0; j < reports.size(); ++j) {
                cout << reports[j].first << " " << reports[j].second << "\n";
            }
        }
    }
    return 0;
}
