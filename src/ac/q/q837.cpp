#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int m, n, k;
    while (cin >> m >> n >> k) {
        vector<string> wheels(m);
        for (int i = 0; i < m; ++i) {
            cin >> wheels[i];
        }

        vector<int> offsets(m, 0);
        int total_score = 0;

        for (int round = 0; round < k; ++round) {
            vector<int> moves(m);
            for (int i = 0; i < m; ++i) {
                cin >> moves[i];
                offsets[i] = (offsets[i] + moves[i]) % n;
                if (offsets[i] < 0) {
                    offsets[i] += n;
                }
            }

            int round_score = 0;
            for (int pos = 0; pos < n; ++pos) {
                vector<int> count(26, 0);
                for (int i = 0; i < m; ++i) {
                    int idx = (pos - offsets[i] + n) % n;
                    char c = wheels[i][idx];
                    count[c - 'a']++;
                }
                int max_count = *max_element(count.begin(), count.end());
                round_score += max_count;
            }
            total_score += round_score;
        }
        cout << total_score << endl;
    }
    return 0;
}
