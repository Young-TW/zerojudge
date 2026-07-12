#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int S;
    int day = 1;
    while (cin >> S) {
        cin >> ws;
        vector<pair<int, int>> appts;
        for (int i = 0; i < S; ++i) {
            string line;
            getline(cin, line);
            istringstream iss(line);
            int h1, m1, h2, m2;
            char colon;
            iss >> h1 >> colon >> m1 >> h2 >> colon >> m2;
            appts.push_back({h1 * 60 + m1, h2 * 60 + m2});
        }

        sort(appts.begin(), appts.end());

        int max_nap = 0;
        int best_start = 10 * 60;
        int current_time = 10 * 60;

        for (int i = 0; i < S; ++i) {
            if (appts[i].first > current_time) {
                int nap = appts[i].first - current_time;
                if (nap > max_nap) {
                    max_nap = nap;
                    best_start = current_time;
                }
            }
            current_time = max(current_time, appts[i].second);
        }

        if (18 * 60 > current_time) {
            int nap = 18 * 60 - current_time;
            if (nap > max_nap) {
                max_nap = nap;
                best_start = current_time;
            }
        }

        cout << "Day #" << day << ": the longest nap starts at ";
        cout << setfill('0') << setw(2) << best_start / 60 << ":" << setw(2) << best_start % 60;
        cout << " and will last for ";
        if (max_nap >= 60) {
            cout << max_nap / 60 << " hours and " << max_nap % 60 << " minutes." << "\n";
        } else {
            cout << max_nap << " minutes." << "\n";
        }
        day++;
    }

    return 0;
}
